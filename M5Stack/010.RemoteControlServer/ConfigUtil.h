#include <M5Stack.h>

struct ConfigItem {
  String key;
  String value;
};

class ConfigUtil {
  public:
    const static int MAX_SIZE_CONFIG = 1000;
  
    ConfigUtil();
    void loadConfig(String path);
    int size();
    String getConfig(String key);

  private:
    int size_of_config;
    ConfigItem configs[MAX_SIZE_CONFIG];
};
