/*
 * @name UC Davis 3D Analyzer
 * @author Brad Lee & SiYi Meng
 * @version 1.01
 * @license GNU LGPL v3
 * @brief 3D map of UC Davis electricity usage
 *
 * QT and OCC integration:
 * Copyright (c) 2018 Shing Liu (eryar@163.com)
 * License: MIT
 * Source: https://github.com/eryar/occQt
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

#ifndef UCD_OSI_DATA_PLUGIN_H
#define UCD_OSI_DATA_PLUGIN_H

// Universal Include
#include "universalInclude.hpp"

#include "../../UI/Interface.hpp"
#include "MainWidget.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

class UCD_OSI_Data : public WidgetInterface {

public:
  UCD_OSI_Data(QWidget *parent = nullptr) {}
  ~UCD_OSI_Data(){};

  void init() { printf("GREETINGS FROM DLL\n"); }
  std::shared_ptr<QWidget> getWidget() {
    std::shared_ptr<QWidget> widget = std::dynamic_pointer_cast<QWidget>(std::make_shared<MainWidget>());
    return widget;
  }
};

/* Writes data from HTTP request into a string buffer
 * @param ptr data address
 */
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);
/* Makes an HTTPS GET request to the URI
 * @param URI The address
 */
rapidjson::Document HTTPS_GET_JSON(std::string URI);
void printJSON_value(const rapidjson::Value &a, unsigned int depth);
void printJSON_iterator(rapidjson::Value::ConstMemberIterator &itr,
                        unsigned int depth);
void getSettingsFile(std::string settingsFileString,
                     std::string &inputURIString,
                     std::string &outputFileString);

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT UCD_OSI_Data plugin;
UCD_OSI_Data plugin;

} // namespace UCDPWAB

#endif
// end UCD_OSI_DATA_MAIN_WIDGET_H