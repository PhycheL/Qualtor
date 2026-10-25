// 门卫规则单元测试：node --test evaluator/generator/tests/guard.test.mjs（需要 Node 23.6 以上，原生运行 .ts）
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import test from "node:test";

import { allowedPatterns, checkToolCall, checkedPath } from "../runtime/guard.ts";

const roots = [];
test.after(() => { for (const root of roots) fs.rmSync(root, { recursive: true, force: true }); });

function workspace() {
  const root = fs.realpathSync(fs.mkdtempSync(path.join(os.tmpdir(), "qualtor-guard-")));
  roots.push(root);
  fs.mkdirSync(path.join(root, "tests"));
  fs.mkdirSync(path.join(root, "project/cpp/src"), { recursive: true });
  fs.writeFileSync(path.join(root, "project/cpp/src/GildedRose.cc"), "// source\n");
  fs.symlinkSync("/etc", path.join(root, "tests/escape"));
  fs.symlinkSync(path.join(root, "project"), path.join(root, "linked-project"));
  return root;
}

const allowed = allowedPatterns(["tests/*.cc", "tests/*.h"]);

test("工作区内的相对路径和绝对路径被规范化", () => {
  const root = workspace();
  assert.equal(checkedPath("project/cpp/src/GildedRose.cc", root), path.join(root, "project/cpp/src/GildedRose.cc"));
  assert.equal(checkedPath(path.join(root, "tests/new.cc"), root), path.join(root, "tests/new.cc"));
  assert.equal(checkedPath(".", root), root);
  assert.equal(checkedPath("project/../tests/a.cc", root), path.join(root, "tests/a.cc"));
});

test("越出工作区的路径被拒绝", () => {
  const root = workspace();
  for (const input of ["../input/runtime.json", "/etc/passwd", "/pi/package.json", "tests/../../outside",
                       root + "-sibling/file", "/"]) {
    assert.throws(() => checkedPath(input, root), /只允许读取/, input);
  }
});

test("“~”不会展开成主目录，仍在工作区内", () => {
  const root = workspace();
  assert.equal(checkedPath("~/secret", root), path.join(root, "~/secret"));
});

test("经过符号链接的路径被拒绝，包括链接本身和链接下的文件", () => {
  const root = workspace();
  for (const input of ["tests/escape", "tests/escape/passwd", "linked-project/cpp/src/GildedRose.cc"]) {
    assert.throws(() => checkedPath(input, root), /符号链接/, input);
  }
});

test("非字符串和含空字符的路径被拒绝", () => {
  const root = workspace();
  for (const input of [undefined, 3, ["tests/a.cc"], "tests/a\0.cc"]) {
    assert.throws(() => checkedPath(input, root), /普通字符串/);
  }
});

test("只能写 tests/ 下符合 allowed_test_files 的文件", () => {
  const root = workspace();
  assert.equal(checkToolCall("write", { path: "tests/gilded_rose_test.cc" }, allowed, root),
               path.join(root, "tests/gilded_rose_test.cc"));
  assert.equal(checkToolCall("edit", { path: "tests/helpers.h" }, allowed, root), path.join(root, "tests/helpers.h"));
  for (const input of ["project/cpp/src/GildedRose.cc", "tests/data.json", "TASK.md", "tests.cc", "tests"]) {
    for (const tool of ["write", "edit"]) {
      assert.throws(() => checkToolCall(tool, { path: input }, allowed, root), /只能修改/, `${tool} ${input}`);
    }
  }
});

test("读类工具可以读工作区内任何文件，路径缺省为工作区根", () => {
  const root = workspace();
  for (const tool of ["read", "grep", "find", "ls"]) {
    assert.equal(checkToolCall(tool, { path: "project/cpp/src/GildedRose.cc" }, allowed, root),
                 path.join(root, "project/cpp/src/GildedRose.cc"));
    assert.equal(checkToolCall(tool, {}, allowed, root), root);
    assert.throws(() => checkToolCall(tool, { path: "/private/record" }, allowed, root), /只允许读取/);
  }
});

test("未授权的工具被拒绝，build_and_test 不检查路径", () => {
  const root = workspace();
  for (const tool of ["bash", "mcp", "web_fetch", ""]) {
    assert.throws(() => checkToolCall(tool, { path: "tests/a.cc" }, allowed, root), /未获授权/, tool);
  }
  assert.equal(checkToolCall("build_and_test", {}, allowed, root), null);
});

test("通配符与评分器 fnmatch 一致：* 可跨越子目录，其余字符按字面匹配", () => {
  const [cc] = allowedPatterns(["tests/*.cc"]);
  assert.ok(cc.test("tests/a.cc"));
  assert.ok(cc.test("tests/sub/a.cc"));
  assert.ok(!cc.test("tests/a.ccx"));
  assert.ok(!cc.test("tests/a_cc"));
  assert.ok(!cc.test("other/tests/a.cc"));
});
