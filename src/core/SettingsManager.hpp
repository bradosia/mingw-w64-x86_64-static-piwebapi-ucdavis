/*
 * @name Settings Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages application settings
 */

#ifndef BRADOSIA_SETTINGS_MANAGER_H
#define BRADOSIA_SETTINGS_MANAGER_H

// C
#include <string.h> // memset

// C++
#include <fstream>
#include <iostream>
#include <string>

/* hjson-cpp 1.4
 * License: MIT
 */
#include <hjson.h>

namespace bradosia {

/* According to:
 * https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 * This method is more performant than string stream and streambuf iterator
 */
std::string readFile(std::fstream& fileStream);

class SettingsManager {
  std::string settingsFileNameStr;

public:
  SettingsManager(){};
  ~SettingsManager(){};
  void getFile(std::string settingsFileString, std::string &inputURIString,
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
      //Hjson::Value d;
      std::string contentStr = readFile(settingsFile);
      std::cout << contentStr << std::endl;
      /*d = Hjson::Unmarshal(contentStr);
      if (d.type() == Hjson::Value::MAP) {
        if (d["URI"] && d["URI"].type() == Hjson::Value::STRING) {
          inputURIString = d["URI"].to_string();
          printf("Input URI Set: %s\n", inputURIString.c_str());
        }
        if (d["output"] && d["output"].type() == Hjson::Value::STRING) {
          outputFileString = d["output"].to_string();
          printf("Output file Set: %s\n", outputFileString.c_str());
        }
      }*/
    } else {
      printf("No settings file used. Check settings file: %s\n",
             settingsFileString.c_str());
    }
  }
};

} // namespace bradosia

#endif
// BRADOSIA_SETTINGS_MANAGER_H
