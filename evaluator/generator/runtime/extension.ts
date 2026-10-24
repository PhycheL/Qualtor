import fs from "node:fs";
import path from "node:path";
import net from "node:net";
import { Type } from "typebox";

const tools = ["read", "write", "edit", "grep", "find", "ls", "build_and_test"];
const root = "/workspace";

function request(data: object): Promise<any> {
  return new Promise((resolve, reject) => {
    const socket = net.createConnection("/control/build.sock");
    let text = "";
    socket.on("connect", () => socket.write(JSON.stringify(data) + "\n"));
    socket.on("data", (chunk) => { text += chunk.toString(); });
    socket.on("end", () => {
      try { resolve(JSON.parse(text)); } catch (error) { reject(error); }
    });
    socket.on("error", reject);
  });
}

// 逐级检查链接；对不存在的写入目标也检查最近的已有父目录。
export function checkedPath(input: unknown): string {
  if (typeof input !== "string" || input.includes("\0")) throw new Error("路径必须是普通字符串");
  const resolved = path.resolve(root, input);
  if (resolved !== root && !resolved.startsWith(root + "/")) throw new Error("只允许读取 /workspace 内的材料");
  let current = root;
  for (const part of path.relative(root, resolved).split(path.sep).filter(Boolean)) {
    current = path.join(current, part);
    try {
      if (fs.lstatSync(current).isSymbolicLink()) throw new Error("不允许通过符号链接访问文件");
    } catch (error: any) { if (error.code !== "ENOENT") throw error; }
  }
  return resolved;
}

export default function (pi: any) {
  const config = JSON.parse(fs.readFileSync("/input/runtime.json", "utf8"));
  const allowed = config.task.allowed_test_files.map((glob: string) => new RegExp("^" + glob.split("*").map(
    (part: string) => part.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")
  ).join(".*") + "$"));
  if (!config.scripted) {
    pi.registerProvider(config.model.provider, {
      baseUrl: config.model.base_url,
      apiKey: "${" + config.model.api_key_env + "}",
      api: config.model.api,
      models: [{ id: config.model.model, name: config.model.model, input: ["text"],
        reasoning: config.model.reasoning, contextWindow: config.model.context_window,
        maxTokens: config.model.max_tokens,
        cost: config.model.cost_per_million || { input: 0, output: 0, cacheRead: 0, cacheWrite: 0 },
        ...(config.model.thinking_level_map ? { thinkingLevelMap: config.model.thinking_level_map } : {}),
        ...(config.model.compat ? { compat: config.model.compat } : {}),
      }],
    });
  }
  pi.on("session_start", () => pi.setActiveTools(tools));
  pi.on("tool_call", async (event: any) => {
    try {
      if (!tools.includes(event.toolName)) throw new Error("该工具未获授权");
      if (event.toolName === "build_and_test") return;
      const resolved = checkedPath(event.input.path ?? ".");
      if (["write", "edit"].includes(event.toolName)) {
        const rel = path.relative(root, resolved);
        if (!rel.startsWith("tests/") || !allowed.some((pattern: RegExp) => pattern.test(rel))) {
          throw new Error("只能修改 tests/ 下 allowed_test_files 允许的文件");
        }
      }
      event.input.path = resolved;
    } catch (error) {
      const reason = String(error);
      await request({ op: "denied", tool: event.toolName, input: event.input, reason });
      return { block: true, reason };
    }
  });
  pi.registerTool({
    name: "build_and_test", label: "编译并运行测试",
    description: "用固定 GCC / C++11 / GoogleTest 编译并运行 tests/。首次调用冻结首次产物；以后每次消耗一个修复轮次。只返回编译、测试结果和剩余轮次。",
    parameters: Type.Object({}), executionMode: "sequential",
    async execute(toolCallId: string, _params: object, _signal: unknown, onUpdate: any) {
      const timer = setInterval(() => onUpdate?.({ content: [{ type: "text", text: "编译或测试仍在运行。" }] }), 30000);
      try {
        const result = await request({ op: "build", tool_call_id: toolCallId });
        return { content: [{ type: "text", text: result.text }], details: result.details };
      } finally { clearInterval(timer); }
    },
  });
}
