/*
 * @name Settings Manager
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Manages application settings
 */

#include "SettingsManager.hpp"

namespace bradosia {

std::string readFile(std::fstream& fileStream) {
  fileStream.seekg(0, std::ios::end);
  size_t size = fileStream.tellg();
  std::string contentStr(size, ' ');
  fileStream.seekg(0);
  fileStream.read(&contentStr[0], size);
  return contentStr;
}

} // namespace bradosia
