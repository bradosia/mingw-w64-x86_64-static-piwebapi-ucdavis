#include "./ui_mainwindow.h"
#include "piwebapi-ucdavis/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QFile file(":menu/default.txt");
  file.open(QIODevice::ReadOnly);
  treeModel = new TreeModel(file.readAll());
  file.close();

  treeView = new QTreeView(this);
  setCentralWidget(treeView);
  treeView->setModel(treeModel);
  treeView->expandAll();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionEnergy_triggered() {
  /*std::string webID =
      "A0EbgZy4oKQ9kiBiZJTW7eugwC6-3Qzx_"
      "5RGrBZiQlqSuWw2sDVYNIPR1YODsG1RUyETgVVRJTC1BRlxDRUZTXFVDREFWSVNcQl"
      "VJTE"
      "RJTkdTXEFDQURFTUlDIFNVUkdFIEJVSUxESU5HXEVMRUNUUklDSVRZfERFTUFORA";
  std::filesystem::path streamHTTP =
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/";
  std::filesystem::path electricityHTTP = streamHTTP / webID / "recorded";
  rapidjson::Document resJSON_Doc =
      PWA_UCD::HTTPS_GET_JSON(electricityHTTP.string());

  if (resJSON_Doc.IsObject()) {
    for (rapidjson::Value::ConstMemberIterator itr = resJSON_Doc.MemberBegin();
         itr != resJSON_Doc.MemberEnd(); ++itr) {
      PWA_UCD::printJSON_iterator(itr, 0);
    }
  }*/
}

void MainWindow::on_actionDiscover_triggered() {
  /*std::string HTTP_request =
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/dataservers/"
      "F1DS9KoOKByvc0-uxyvoTV1UfQVVRJTC1QSS1Q/points";
  rapidjson::Document resJSON_Doc = PWA_UCD::HTTPS_GET_JSON(HTTP_request);

  if (resJSON_Doc.IsObject()) {
    for (rapidjson::Value::ConstMemberIterator itr = resJSON_Doc.MemberBegin();
         itr != resJSON_Doc.MemberEnd(); ++itr) {
      PWA_UCD::printJSON_iterator(itr, 0);
    }
  }*/
}

void MainWindow::on_actionWater_triggered() {
  /*std::string webID =
      "F1DSAAAAAAAAAAAAAAAAEiCt5wVUNELVBJLUlJUy5PVS5BRDMuVUNEQVZJUy5FRFU";
  std::filesystem::path streamHTTP =
      "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/";
  std::filesystem::path electricityHTTP = streamHTTP / webID / "recorded";
  rapidjson::Document resJSON_Doc =
      PWA_UCD::HTTPS_GET_JSON(electricityHTTP.string());

  if (resJSON_Doc.IsObject()) {
    for (rapidjson::Value::ConstMemberIterator itr = resJSON_Doc.MemberBegin();
         itr != resJSON_Doc.MemberEnd(); ++itr) {
      PWA_UCD::printJSON_iterator(itr, 0);
    }
  }*/
}

void MainWindow::on_actionWiFi_triggered() {
    std::string inputURIString, outputFileString;
  PWA_UCD::getSettingsFile(SETTINGS_FILE, inputURIString,outputFileString);
  rapidjson::Document resJSON_Doc =
      PWA_UCD::HTTPS_GET_JSON(inputURIString);
  std::ofstream ofs(outputFileString.c_str());
  if ( !ofs.is_open() )
      {
     printf("ERROR: output file not found: %s\n",outputFileString.c_str());
        return ;
      }

       rapidjson::OStreamWrapper osw { ofs };
       rapidjson::PrettyWriter< rapidjson::OStreamWrapper> writer2 { osw };
      resJSON_Doc.Accept( writer2 );

}

void MainWindow::on_actionTemperature_triggered()
{
    QFile file(":menu/default.txt");
    file.open(QIODevice::ReadOnly);
    treeModel->addData(file.readAll());
    file.close();
    treeView->reset();
}
