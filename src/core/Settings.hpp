/*
 * @name Settings Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages application settings
 */

#ifndef BRADOSIA_SETTINGS_MANAGER_H
#define BRADOSIA_SETTINGS_MANAGER_H

// C++
#include <string>
#include <fstream>

/* hjson-cpp 1.4
 * License: MIT
 */
#include <hjson.h>

namespace bradosia {

class SettingsManager {
  std::string settingsFileNameStr;

public:
  SettingsManager(){};
  ~SettingsManager(){};
  void getFile(std::string settingsFileString,
                       std::string &inputURIString,
                       std::string &outputFileString) {
    // Check if inputFile exists
    {
      std::fstream inputFile;
      inputFile.open(settingsFileString, std::fstream::in);
      if (!inputFile) {
        printf("FATAL ERROR: Could not open input file: %s\n",
               settingsFileString.c_str());
        return;
      }
    }
    std::fstream settingsFile;
    printf("Opening settings file: %s\n", settingsFileString.c_str());
    settingsFile.open(settingsFileString, std::fstream::in);
    if (settingsFile) {
      char *settingsFileChar;
      unsigned int fileSize;
      Hjson::Value d;

      settingsFile.seekg(0, std::ios::end); // set the pointer to the end
      fileSize = settingsFile.tellg();      // get the length of the file
      settingsFile.seekg(0, std::ios::beg);
      settingsFileChar = new char[fileSize + 1];
      memset(settingsFileChar, 0, sizeof(settingsFileChar[0]) * fileSize + 1);
      settingsFile.read(settingsFileChar, fileSize);

      d = Hjson::Unmarshal(settingsFileChar);
      if (d.IsObject()) {
        if (d.HasMember("URI") && d["URI"].IsString()) {
          inputURIString = d["URI"].GetString();
          printf("Input URI Set: %s\n", inputURIString.c_str());
        }
        if (d.HasMember("output") && d["output"].IsString()) {
          outputFileString = d["output"].GetString();
          printf("Output file Set: %s\n", outputFileString.c_str());
        }
      }
      delete settingsFileChar;
    } else {
      printf("No settings file used. Check settings file: %s\n",
             settingsFileString.c_str());
    }
    printf("");
  }
};

} // namespace bradosia

#endif
// BRADOSIA_SETTINGS_MANAGER_H
