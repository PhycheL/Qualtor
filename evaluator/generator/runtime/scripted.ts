/** 只在框架自测时加载的本地剧本模型；仍通过真实 pi 的工具执行链。 */
import fs from "node:fs";
import { createAssistantMessageEventStream } from "@earendil-works/pi-ai";

export default function (pi: any) {
  const plan = JSON.parse(fs.readFileSync("/input/scenario.json", "utf8"));
  let index = 0;
  pi.registerProvider("qualtor-scripted", {
    baseUrl: "http://scripted.invalid", apiKey: "scripted-no-credential", api: "qualtor-scripted",
    models: [{ id: "script", name: "框架自测剧本", input: ["text"], reasoning: false,
      contextWindow: 131072, maxTokens: 8192, cost: { input: 0, output: 0, cacheRead: 0, cacheWrite: 0 } }],
    streamSimple(model: any) {
      const stream = createAssistantMessageEventStream();
      const step = plan[index++] || { text: "任务完成。" };
      if (step.stall) { setInterval(() => {}, 1000); return stream; }
      const content = step.tool ? [{ type: "toolCall", id: `script-${index}`, name: step.tool, arguments: step.args || {} }]
        : [{ type: "text", text: step.text || "任务完成。" }];
      const stopReason = step.error ? "error" : step.tool ? "toolUse" : "stop";
      const message = { role: "assistant", content, api: model.api, provider: model.provider, model: model.id,
        usage: { input: 10, output: 5, cacheRead: 2, cacheWrite: 1, totalTokens: 18,
          cost: { input: 0, output: 0, cacheRead: 0, cacheWrite: 0, total: 0 } }, stopReason,
        timestamp: Date.now(), ...(step.error ? { errorMessage: "scripted API failure" } : {}) };
      queueMicrotask(() => {
        stream.push({ type: "start", partial: message });
        if (step.error) stream.push({ type: "error", reason: "error", error: message });
        else stream.push({ type: "done", reason: stopReason, message });
      });
      return stream;
    },
  });
}
