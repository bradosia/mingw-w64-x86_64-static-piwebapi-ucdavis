#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "piwebapi-ucdavis/amalgamated.h"
#include "piwebapi-ucdavis/treemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionEnergy_triggered();

    void on_actionDiscover_triggered();

    void on_actionWater_triggered();

    void on_actionWiFi_triggered();

    void on_actionTemperature_triggered();

private:
    Ui::MainWindow *ui;
    TreeModel *treeModel;
    QTreeView *treeView;
};
#endif // MAINWINDOW_H
