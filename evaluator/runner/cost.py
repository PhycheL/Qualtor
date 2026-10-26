"""合并产品已经报告的生成成本。"""
def add_costs(current, previous):
    result = dict(current, tokens=dict(current["tokens"]))
    for cost in previous:
        for key, value in cost["tokens"].items():
            result["tokens"][key] = result["tokens"].get(key, 0) + value
        for key in ("model_calls", "repair_rounds", "seconds"):
            result[key] += cost[key]
        result["usd"] = result["usd"] + cost["usd"] if result["usd"] is not None and cost["usd"] is not None else None
    return result


