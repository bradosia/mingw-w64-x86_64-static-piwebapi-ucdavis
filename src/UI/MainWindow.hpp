/*
 * @name UC Davis PI Web API Browser
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Browser for UC Davis PI Web API data.
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

// main UI
#include "ui_main.h"

// universal includes
#include "universalInclude.hpp"

// local project
#include "Interface.hpp"
#include "../core/PluginManager.hpp"
#include "../core/Settings.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(){};

private:
  // ui
  Ui::main ui;
  std::shared_ptr<UCDPWAB::PluginInterface> UCDPWAB_plugin;

private slots:
  void on_actionEnergy_triggered();

  void on_actionDiscover_triggered();

  void on_actionWater_triggered();

  void on_actionWiFi_triggered();

  void on_actionTemperature_triggered();
};
#endif // MAIN_WINDOW_H
