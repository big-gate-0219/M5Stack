#include "ConfigUtil.h"

ConfigUtil::ConfigUtil() {
  
}

void ConfigUtil::loadConfig(String path) {
  size_of_config = 0;
  
  String configText;
  // ファイルの読み込み
  File file = SPIFFS.open(path,"r");
  while (file.available()) {
    configText += file.readString();
  }
  file.close();

  // 行数の確認
  int from = 0;
  while (from != -1) {
    from = configText.indexOf("\n", from);
    if (from != -1 ) {
      from++;
      size_of_config++;
    }
  } 

  // 定義配列の作成
  from = 0;
  for (int i = 0; i < size_of_config; i++) {
    int to = configText.indexOf("\n", from);
    int delimIndex = configText.indexOf("=", from);
    String key = configText.substring(from, delimIndex);
    String value = configText.substring(delimIndex + 1, to);
    configs[i] = {key, value};
    from = to + 1;
  }
}

int ConfigUtil::size() {
  return size_of_config;
}

String ConfigUtil::getConfig(String key) {
  for (int i =0; i < size_of_config; i++) {
    if (configs[i].key == key) {
      return configs[i].value;
    }
  }
  return "";
}
