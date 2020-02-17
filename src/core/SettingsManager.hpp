/*
 * @name Settings Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages application settings
 */

#ifndef BRADOSIA_SETTINGS_MANAGER_H
#define BRADOSIA_SETTINGS_MANAGER_H

#define USE_RAPID_JSON 1
//#define USE_HJSON 1
#define SETTINGS_MANAGER_DEBUG 1

// C
#include <string.h> // memset

// C++
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 * License: MITs
 */
#if USE_RAPID_JSON
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h> // rapidjson::ParseResult
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#endif

/* hjson-cpp 1.4
 * License: MIT
 */
#if USE_HJSON
#include <hjson.h>
#endif

namespace bradosia {

/* According to:
 * https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 * This method is more performant than string stream and streambuf iterator
 */
std::string readFile(std::fstream &fileStream);

class SettingsManager {
  std::string settingsFileNameStr;
#if USE_RAPID_JSON
  // settings to look for
  rapidjson::Document master;
  std::unordered_map<std::string, std::function<void(rapidjson::Value &data)>>
      masterCallbackMap;
#endif

public:
  SettingsManager(){
      master.SetObject();
  };
  ~SettingsManager(){};
  void deployFile(std::string settingsFileString);

#if USE_RAPID_JSON
  /* Merges the plugin settings with the master
   */
  void merge(rapidjson::Value &data,
             std::unordered_map<std::string,
                                std::function<void(rapidjson::Value &data)>>);
#endif

#if USE_RAPID_JSON
  /* Recursive deploying of settings callbacks
   */
  bool deployDOM(rapidjson::Value &dstObject, rapidjson::Value &srcObject);
#endif
};

} // namespace bradosia

#endif
// BRADOSIA_SETTINGS_MANAGER_H
