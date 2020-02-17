/*
 * @name Settings Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages application settings
 */

#include "SettingsManager.hpp"

namespace bradosia {

std::string readFile(std::fstream &fileStream) {
  fileStream.seekg(0, std::ios::end);
  size_t size = fileStream.tellg();
  std::string contentStr(size, ' ');
  fileStream.seekg(0);
  fileStream.read(&contentStr[0], size);
  return contentStr;
}

void SettingsManager::deployFile(std::string settingsFileString) {
  // Check if settings file exists
  {
    std::fstream inputFile;
    inputFile.open(settingsFileString, std::fstream::in);
    if (!inputFile) {
      printf("FATAL ERROR: Could not open input file: %s\n",
             settingsFileString.c_str());
      return;
    }
  }
  // open settings file
  std::fstream settingsFile;
  printf("Opening settings file: %s\n", settingsFileString.c_str());
  settingsFile.open(settingsFileString, std::fstream::in);
  if (settingsFile) {
    std::string contentStr = readFile(settingsFile);
#if SETTINGS_MANAGER_DEBUG
    std::cout << contentStr << std::endl;
#endif
#if USE_RAPID_JSON
    rapidjson::Document d;
    d.Parse<rapidjson::kParseCommentsFlag |
            rapidjson::kParseTrailingCommasFlag>(contentStr.c_str());
    if (d.IsObject()) {
      std::cout << "SETTINGS deployFile(" << settingsFileString
                << ") deployDOM()" << std::endl;
      deployDOM(d, master);
    } else {
      std::cout << "SETTINGS deployFile(" << settingsFileString
                << ") Parse() FAILED!" << std::endl;
    }
#elif USE_HJSON
    Hjson::Value d = Hjson::Unmarshal(contentStr);
    if (d.type() == Hjson::Value::MAP) {
      if (d["URI"] && d["URI"].type() == Hjson::Value::STRING) {
        inputURIString = d["URI"].to_string();
        printf("Input URI Set: %s\n", inputURIString.c_str());
      }
      if (d["output"] && d["output"].type() == Hjson::Value::STRING) {
        outputFileString = d["output"].to_string();
        printf("Output file Set: %s\n", outputFileString.c_str());
      }
      if (d["treeData"] && d["treeData"].type() == Hjson::Value::MAP) {
        printf("treeData FOUND!\n");
      }
    }
#endif
  } else {
    printf("No settings file used. Check settings file: %s\n",
           settingsFileString.c_str());
  }
}

#if USE_RAPID_JSON
void SettingsManager::merge(
    rapidjson::Value &plugin,
    std::unordered_map<std::string, std::function<void(rapidjson::Value &data)>>
        pluginCallbackMap) {
  // merge plugin settings with master
  if (plugin.IsObject()) {
    for (rapidjson::Value::MemberIterator itr = plugin.MemberBegin();
         itr != plugin.MemberEnd(); ++itr) {
      master.AddMember(itr->name, itr->value, master.GetAllocator());
    }
  }
#if SETTINGS_MANAGER_DEBUG
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  master.Accept(writer);
  std::cout << "Master:\n" << buffer.GetString() << std::endl;
#endif
  // merge plugin callbacks with master
  masterCallbackMap.insert(pluginCallbackMap.begin(), pluginCallbackMap.end());
#if SETTINGS_MANAGER_DEBUG
  std::cout << "Plugin Callback Map:\n";
  for (auto pairs : pluginCallbackMap) {
    std::cout << "first:" << pairs.first << std::endl;
  }
  std::cout << "Master Callback Map:\n";
  for (auto pairs : masterCallbackMap) {
    std::cout << "first:" << pairs.first << std::endl;
  }
#endif
}
#endif

#if USE_RAPID_JSON
bool SettingsManager::deployDOM(rapidjson::Value &settingsFileObject,
                                rapidjson::Value &masterObject) {
  for (auto masterIt = masterObject.MemberBegin();
       masterIt != masterObject.MemberEnd(); ++masterIt) {
    std::cout << "SETTINGS deployFile() deployDOM() find("
              << masterIt->name.GetString() << ")" << std::endl;
    auto dstIt = settingsFileObject.FindMember(masterIt->name);
    if (dstIt != settingsFileObject.MemberEnd()) {
      std::cout << "SETTINGS deployFile() deployDOM() find("
                << masterIt->name.GetString() << ") FOUND!" << std::endl;
      if (masterIt->value.IsObject() && dstIt->value.IsObject()) {
        if (!deployDOM(dstIt->value, masterIt->value))
          return false;
      } else if (masterIt->value.IsString()) {
        // find callback
        std::string callbackHandle = masterIt->value.GetString();
        auto findIt = masterCallbackMap.find(callbackHandle);
        if (findIt != masterCallbackMap.end()) {
          // call callback
          std::cout << "SETTINGS deployFile() deployDOM() find("
                    << masterIt->name.GetString() << ") Callback("
                    << callbackHandle << ")" << std::endl;
          (findIt->second)(dstIt->value);
        }
      }
    }
  }
  return true;
}
#endif

} // namespace bradosia
