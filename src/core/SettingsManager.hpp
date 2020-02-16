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
#include <iostream>
#include <string>

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

public:
  SettingsManager(){};
  ~SettingsManager(){};

  void getFile(std::string settingsFileString, std::string &inputURIString,
               std::string &outputFileString) {
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
        if (d.HasMember("URI") && d["URI"].IsString()) {
          inputURIString = d["URI"].GetString();
          printf("Input URI Set: %s\n", inputURIString.c_str());
        }
        if (d.HasMember("output") && d["output"].IsString()) {
          outputFileString = d["output"].GetString();
          printf("Output file Set: %s\n", outputFileString.c_str());
        }
        if (d.HasMember("treeData") && d["treeData"].IsObject()) {
          printf("treeData FOUND!\n");
        }
      } else {
        printf("JSON PARSE FAILED!\n");
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
};

} // namespace bradosia

#endif
// BRADOSIA_SETTINGS_MANAGER_H
