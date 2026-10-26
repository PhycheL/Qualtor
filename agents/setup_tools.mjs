// 安装 pi 自带的搜索工具到产品缓存，生成阶段保持离线；记录实际二进制哈希。
import fs from "node:fs";
import path from "node:path";
import crypto from "node:crypto";
import { spawnSync } from "node:child_process";
import { ensureTool } from "./pi/packages/coding-agent/dist/utils/tools-manager.js";

const directory = path.join(process.env.PI_CODING_AGENT_DIR, "bin");
fs.mkdirSync(directory, { recursive: true });
const records = {};
for (const name of ["rg", "fd"]) {
  const target = path.join(directory, name);
  // 随目录复制的缓存可能属于另一操作系统/架构；失效时让 ensureTool 重新查找或下载。
  if (fs.existsSync(target)) {
    const cached = spawnSync(target, ["--version"], { encoding: "utf8", timeout: 10000 });
    if (cached.error || cached.status !== 0) {
      fs.rmSync(target);
      process.stderr.write(`Discarded incompatible ${name} cache; resolving for ${process.platform}/${process.arch}\n`);
    }
  }
  const found = await ensureTool(name, (event) => process.stderr.write(event.message + "\n"));
  if (!found) throw new Error(`Missing ${name}; install it on the host and rerun setup`);
  const resolved = path.isAbsolute(found) ? found : spawnSync("which", [found], { encoding: "utf8" }).stdout.trim();
  if (path.resolve(resolved) !== path.resolve(target)) fs.copyFileSync(resolved, target);
  fs.chmodSync(target, 0o755);
  const version = spawnSync(target, ["--version"], { encoding: "utf8", timeout: 10000 });
  if (version.error || version.status !== 0) throw new Error(`${name} cannot run on this host`);
  records[name] = { version: version.stdout.trim(), sha256: crypto.createHash("sha256").update(fs.readFileSync(target)).digest("hex") };
}
fs.writeFileSync(path.join(directory, "manifest.json"), JSON.stringify(records, null, 2) + "\n");
