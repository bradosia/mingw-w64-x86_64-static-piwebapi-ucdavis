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

#ifndef UCD_OSI_DATA_MAIN_WIDGET_H
#define UCD_OSI_DATA_MAIN_WIDGET_H

// Universal Include
#include "universalInclude.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

class MainWidget : public QWidget {
  Q_OBJECT

public:
  MainWidget(){
      this->setObjectName("UC Davis PI Web API Browser Widget");
  };
  ~MainWidget(){};
};

} // namespace UCDPWAB

#endif
// end UCD_OSI_DATA_MAIN_WIDGET_H
