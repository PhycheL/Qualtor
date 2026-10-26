import fs from "node:fs";
import net from "node:net";
import { Type } from "typebox";
import { createEditToolDefinition, createWriteToolDefinition } from "@earendil-works/pi-coding-agent";
import { TOOLS, ROOT, allowedPatterns, checkToolCall, checkedPath, writeTestFile } from "./guard.ts";

function request(data: object): Promise<any> {
  return new Promise((resolve, reject) => {
    const socket = net.createConnection(process.env.QUALTOR_BUILD_SOCKET!);
    let text = "";
    socket.on("connect", () => socket.write(JSON.stringify(data) + "\n"));
    socket.on("data", (chunk) => { text += chunk.toString(); });
    socket.on("end", () => {
      try { resolve(JSON.parse(text)); } catch (error) { reject(error); }
    });
    socket.on("error", reject);
  });
}

export default function (pi: any) {
  const config = JSON.parse(fs.readFileSync(process.env.QUALTOR_RUNTIME_CONFIG!, "utf8"));
  const allowed = allowedPatterns(config.task.allowed_test_files);
  const writeFile = (file: string, content: string) => writeTestFile(file, content, allowed);
  pi.registerTool(createWriteToolDefinition(ROOT, { operations: {
    writeFile,
    mkdir: async (directory: string) => { fs.mkdirSync(checkedPath(directory), { recursive: true }); },
  } }));
  pi.registerTool(createEditToolDefinition(ROOT, { operations: {
    writeFile,
    readFile: async (file: string) => fs.readFileSync(checkedPath(file)),
    access: async (file: string) => { fs.accessSync(checkedPath(file), fs.constants.R_OK | fs.constants.W_OK); },
  } }));
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
  pi.on("session_start", () => pi.setActiveTools(TOOLS));
  pi.on("before_provider_request", async (event: any) => {
    // 只记录实际请求的模型和思考字段，绝不保存消息正文、headers 或凭证。
    const payload = event.payload || {};
    await request({ op: "model_request", model: payload.model,
                    reasoning_effort: payload.reasoning_effort ?? payload.reasoning?.effort ?? null,
                    thinking_type: payload.thinking?.type ?? null });
  });
  pi.on("tool_call", async (event: any) => {
    try {
      const resolved = checkToolCall(event.toolName, event.input, allowed);
      if (resolved !== null) event.input.path = resolved;
    } catch (error) {
      const reason = String(error);
      await request({ op: "denied", tool: event.toolName, input: event.input, reason });
      return { block: true, reason };
    }
  });
  pi.registerTool({
    name: "build_and_test", label: "编译并运行测试",
    description: "用固定 GCC / C++11 / GoogleTest 编译并运行 tests/。编译前保存本轮测试快照，首次快照另存为首次产物；首次编译不计修复，以后每次消耗一个修复轮次。只返回编译、测试结果和剩余轮次。",
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
