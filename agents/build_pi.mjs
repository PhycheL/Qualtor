// 使用 pi 源码自带的内容寻址模型目录；普通 npm run build 会读取实时目录并改变源码。
import fs from "node:fs";
import crypto from "node:crypto";
import { spawnSync } from "node:child_process";
import path from "node:path";
import { fileURLToPath } from "node:url";

const root = path.dirname(fileURLToPath(import.meta.url));
const pi = path.join(root, "pi");
const catalog = path.join(root, ".cache/pi-models.json");
fs.mkdirSync(path.dirname(catalog), { recursive: true });
const { revision } = JSON.parse(fs.readFileSync(path.join(pi, "nix/model-catalog.json"), "utf8"));
if (!/^sha256-[a-f0-9]{64}$/.test(revision)) throw new Error("Invalid pinned model catalog");
const response = await fetch(`https://pi.dev/api/models/revisions/${revision}?types=chat,image,classifier`);
if (!response.ok) throw new Error(`Catalog HTTP ${response.status}`);
const bytes = Buffer.from(await response.arrayBuffer());
if (`sha256-${crypto.createHash("sha256").update(bytes).digest("hex")}` !== revision) {
  throw new Error("Pinned catalog SHA-256 mismatch");
}
fs.writeFileSync(catalog, bytes);
for (const command of [
  ["node", "packages/ai/scripts/hydrate-model-catalog.ts", catalog],
  ["npm", "run", "build:offline"],
]) {
  const result = spawnSync(command[0], command.slice(1), { cwd: pi, stdio: "inherit" });
  if (result.status !== 0) process.exit(result.status || 1);
}
