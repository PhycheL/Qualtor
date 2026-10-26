import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import test from "node:test";
import { createEditTool } from "../pi/packages/coding-agent/dist/core/tools/edit.js";
import { createWriteTool } from "../pi/packages/coding-agent/dist/core/tools/write.js";
import { allowedPatterns, writeTestFile } from "../generator/runtime/guard.ts";

const limit = 64 * 1024 * 1024;
const allowed = allowedPatterns(["tests/*.cc", "tests/*.h"]);
function workspace(t, spare) {
  const root = fs.realpathSync(fs.mkdtempSync(path.join(os.tmpdir(), "qualtor-quota-")));
  t.after(() => fs.rmSync(root, { recursive: true, force: true }));
  fs.mkdirSync(path.join(root, "tests"));
  const fd = fs.openSync(path.join(root, "tests/filler.h"), "w");
  fs.ftruncateSync(fd, limit - spare);
  fs.closeSync(fd);
  const writeFile = (file, content) => writeTestFile(file, content, allowed, root);
  const edit = createEditTool(root, { operations: {
    writeFile, readFile: async (file) => fs.readFileSync(file), access: async (file) => fs.accessSync(file),
  } });
  const write = createWriteTool(root, { operations: { writeFile, mkdir: async (dir) => fs.mkdirSync(dir, { recursive: true }) } });
  return { root, edit, write };
}

test("实际 pi edits[] 超额时拒绝且原文件不变", async (t) => {
  const { root, edit } = workspace(t, 1);
  const file = path.join(root, "tests/a.cc");
  fs.writeFileSync(file, "Q");
  await assert.rejects(edit.execute("edit", { path: file, edits: [{ oldText: "Q", newText: "0123456789" }] }), /64 MiB/);
  assert.equal(fs.readFileSync(file, "utf8"), "Q");
});

test("按最终 UTF-8、BOM 和 CRLF 大小计费，批量缩小编辑仍可执行", async (t) => {
  const original = "\ufeffA\r\nB\r\n";
  const { root, edit } = workspace(t, Buffer.byteLength(original));
  const file = path.join(root, "tests/a.cc");
  fs.writeFileSync(file, original);
  await assert.rejects(edit.execute("over", { path: file, edits: [
    { oldText: "A", newText: "" }, { oldText: "B", newText: "中" },
  ] }), /64 MiB/);
  assert.equal(fs.readFileSync(file, "utf8"), original);
  await edit.execute("shrink", { path: file, edits: [{ oldText: "A", newText: "" }, { oldText: "B", newText: "" }] });
  assert.equal(fs.readFileSync(file, "utf8"), "\ufeff\r\n\r\n");
});

test("不同文件并发写入共用剩余配额", async (t) => {
  const { root, write } = workspace(t, 2);
  const results = await Promise.allSettled(["a", "b"].map((name) =>
    write.execute(name, { path: `tests/${name}.cc`, content: "xy" })));
  assert.equal(results.filter((r) => r.status === "fulfilled").length, 1);
  assert.match(results.find((r) => r.status === "rejected").reason.message, /64 MiB/);
  const total = fs.readdirSync(path.join(root, "tests")).reduce((n, name) => n + fs.statSync(path.join(root, "tests", name)).size, 0);
  assert.equal(total, limit);
});

test("覆盖文件先扣除旧大小，超额写入保持原文件", async (t) => {
  const { root, write } = workspace(t, 3);
  const file = path.join(root, "tests/a.cc");
  fs.writeFileSync(file, "abc");
  await write.execute("same", { path: file, content: "中" });
  await assert.rejects(write.execute("over", { path: file, content: "中文" }), /64 MiB/);
  assert.equal(fs.readFileSync(file, "utf8"), "中");
});
