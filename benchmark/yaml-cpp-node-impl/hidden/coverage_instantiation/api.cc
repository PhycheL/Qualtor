#include "yaml-cpp/yaml.h"
// 不执行，只补充公开模板 API 的实例化；Node 的非模板成员在依赖/参考测试中实例化。
void instantiate_yaml_api(YAML::Node& n, const YAML::Node& cn) {
  YAML::Node key("key"), copied(n), scalar(3); char text[]="value"; char* ptr=text;
  n=ptr; n=text; n=std::string("value"); n=3; n=copied;
  (void)n.as<int>(); (void)n.as<int>(5); (void)n.as<std::string>();
  (void)n.as<std::string>(std::string("fallback"));
  (void)n[ptr]; (void)cn[ptr]; (void)n[text]; (void)cn[text];
  (void)n[std::string("key")]; (void)cn[std::string("key")];
  (void)n[0]; (void)cn[0]; (void)n[key]; (void)cn[key];
  n.remove("key"); n.remove(key); n.force_insert("key",3);
  n.push_back(3); n.push_back(copied); n.reset(copied);
  (void)n.begin(); (void)n.end(); (void)cn.begin(); (void)cn.end();
  (void)n.IsDefined(); (void)n.Mark(); (void)n.Type(); (void)n.Scalar();
  (void)n.Tag(); n.SetTag("tag"); (void)n.Style(); n.SetStyle(YAML::EmitterStyle::Flow);
  (void)n.size(); (void)n.is(copied); (void)(n==copied);
}
