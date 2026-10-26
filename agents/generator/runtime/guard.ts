// 门卫规则：只依赖 Node 标准库，便于脱离 pi 单独测试。类型标注均可被直接擦除（Node 原生运行 .ts）。
import fs from "node:fs";
import path from "node:path";

export const TOOLS = ["read", "write", "edit", "grep", "find", "ls", "build_and_test"];
export const ROOT = path.resolve(process.env.QUALTOR_WORKSPACE || process.cwd());
const MAX_TEST_BYTES = 64 * 1024 * 1024;

function testBytes(directory: string): number {
  if (!fs.existsSync(directory)) return 0;
  let total = 0;
  for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
    const file = path.join(directory, entry.name);
    if (entry.isSymbolicLink() || (!entry.isDirectory() && !entry.isFile())) throw new Error("测试目录只能含普通文件和目录");
    total += entry.isDirectory() ? testBytes(file) : fs.statSync(file).size;
  }
  return total;
}

// 逐级检查链接；对不存在的写入目标也检查最近的已有父目录。
export function checkedPath(input: unknown, root: string = ROOT): string {
  if (typeof input !== "string" || input.includes("\0")) throw new Error("路径必须是普通字符串");
  const resolved = path.resolve(root, input);
  if (resolved !== root && !resolved.startsWith(root + "/")) throw new Error("只允许读取当前工作区内的材料");
  let current = root;
  for (const part of path.relative(root, resolved).split(path.sep).filter(Boolean)) {
    current = path.join(current, part);
    try {
      if (fs.lstatSync(current).isSymbolicLink()) throw new Error("不允许通过符号链接访问文件");
    } catch (error: any) { if (error.code !== "ENOENT") throw error; }
  }
  return resolved;
}

// allowed_test_files 的通配符与评分器的 fnmatch 一致：* 匹配任意字符（含 /）。
export function allowedPatterns(globs: string[]): RegExp[] {
  return globs.map((glob) => new RegExp("^" + glob.split("*").map(
    (part) => part.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")
  ).join(".*") + "$"));
}

// 返回规范化后的路径（build_and_test 返回 null）；不允许时抛出异常，由调用方记录并拦截。
export function checkToolCall(toolName: string, input: any, allowed: RegExp[], root: string = ROOT): string | null {
  if (!TOOLS.includes(toolName)) throw new Error("该工具未获授权");
  if (toolName === "build_and_test") return null;
  const resolved = checkedPath(input?.path ?? ".", root);
  if (toolName === "write" || toolName === "edit") {
    const rel = path.relative(root, resolved);
    if (!rel.startsWith("tests/") || !allowed.some((pattern) => pattern.test(rel))) {
      throw new Error("只能修改 tests/ 下 allowed_test_files 允许的文件");
    }
  }
  return resolved;
}

// pi 完成 edits[]、换行和 BOM 处理后交给此写入函数最终内容。
// 检查与写入间没有 await；同一 Node 进程中不同文件的并发修改也不会同时占用剩余配额。
export async function writeTestFile(file: string, content: string, allowed: RegExp[], root: string = ROOT): Promise<void> {
  const resolved = checkToolCall("write", { path: file }, allowed, root)!;
  const previous = fs.existsSync(resolved) ? fs.statSync(resolved).size : 0;
  if (testBytes(path.join(root, "tests")) - previous + Buffer.byteLength(content, "utf8") > MAX_TEST_BYTES) {
    throw new Error("生成测试文件总量不能超过 64 MiB");
  }
  fs.writeFileSync(resolved, content, "utf8");
}
