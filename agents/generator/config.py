"""产品配置；只从交付目录或显式文件读取连接凭证。"""
import os
from pathlib import Path
import re
from urllib.parse import urlsplit
from generator.support import AGENTS, read_json, sha256_file

def read_dotenv(path):
    """读取单行字面值；不执行 shell、不插值，错误中不回显配置内容。"""
    try:
        lines = path.read_text(encoding="utf-8-sig").splitlines()
    except FileNotFoundError:
        raise ValueError("缺少agents 目录 .env，请复制 .env.example 后填写 API 地址和密钥") from None
    except (OSError, UnicodeError):
        raise ValueError("无法读取agents 目录 .env，请检查文件权限和 UTF-8 编码") from None
    values = {}
    for number, line in enumerate(lines, 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        match = re.fullmatch(r"(?:export\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)", line)
        if not match:
            raise ValueError(f".env 第 {number} 行格式错误，应为 KEY=VALUE")
        key, value = match.groups()
        if value.startswith(("'", '"')):
            end = value.find(value[0], 1)
            tail = value[end + 1:].strip() if end >= 0 else ""
            if end < 0 or (tail and not tail.startswith("#")):
                raise ValueError(f".env 第 {number} 行引号格式错误")
            value = value[1:end]
        else:
            value = "" if value.startswith("#") else re.split(r"\s+#", value, maxsplit=1)[0].rstrip()
        if "\0" in value or key in values:
            raise ValueError(f".env 第 {number} 行含空字符或重复字段")
        values[key] = value
    return values


def load_config(name, env_file=None):
    if not re.fullmatch(r"[a-zA-Z0-9_-]+", name):
        raise ValueError("配置名只能包含字母、数字、-、_")
    path = AGENTS / "configs" / name / "config.json"
    config = read_json(path)
    required = ("provider", "model", "thinking", "api", "base_url_env", "api_key_env")
    for key in required:
        if not isinstance(config.get(key), str) or not config[key].strip():
            raise ValueError(f"请填写 {path.relative_to(AGENTS)} 的 {key}")
    if set(config) - set(required) - {"reasoning", "context_window", "max_tokens", "cost_per_million", "compat", "thinking_level_map"}:
        raise ValueError("配置含未知字段；密钥和 API 地址仅从agents 目录 .env 读取")
    if config["thinking"] not in ("off", "minimal", "low", "medium", "high", "xhigh", "max"):
        raise ValueError("thinking 必须是 pi 支持的思考级别")
    for key in ("base_url_env", "api_key_env"):
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", config[key]):
            raise ValueError(f"{key} 必须是环境变量名")
    values = read_dotenv(Path(env_file).resolve() if env_file else AGENTS / ".env")
    for key in ("base_url_env", "api_key_env"):
        if not values.get(config[key], "").strip():
            raise ValueError(f"请在agents 目录 .env 中填写 {config[key]}")
    base = values[config["base_url_env"]]
    url = urlsplit(base)
    if url.scheme not in ("http", "https") or not url.hostname or url.username or url.password or url.query or url.fragment:
        raise ValueError("API 地址必须是 http(s) URL，且不包含凭证、查询参数或 fragment")
    # 只导出选中配置的两个字段，供宿主机 pi 按名称取值；不加载 .env 中的其他宿主机设置。
    os.environ.update({config[key]: values[config[key]] for key in ("base_url_env", "api_key_env")})
    config["base_url"] = base
    config.setdefault("reasoning", False)
    config.setdefault("context_window", 131072)
    config.setdefault("max_tokens", 8192)
    config.setdefault("cost_per_million", None)
    return config, {"name": name, "sha256": sha256_file(path), "settings": config}


