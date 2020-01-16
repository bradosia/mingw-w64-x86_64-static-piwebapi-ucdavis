#include <stdio.h>

// fjstudio icons

// c++
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

/*
 * piwebapi-ucdavis 1.0
 */
#include "piwebapi-ucdavis/amalgamated.h"

/*
 * UI
 */
#include "piwebapi-ucdavis/mainwindow.h"

int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(simpletreemodel);

  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();

  return 0;
}
