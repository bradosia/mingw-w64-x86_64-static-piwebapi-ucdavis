/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEnergy;
    QAction *actionWater;
    QAction *actionWiFi;
    QAction *actionFile;
    QAction *actionAbout;
    QAction *actionDiscover;
    QAction *actionTemperature;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QMenuBar *menubar;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionEnergy = new QAction(MainWindow);
        actionEnergy->setObjectName(QString::fromUtf8("actionEnergy"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/utility/003-light bulb.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionEnergy->setIcon(icon);
        actionWater = new QAction(MainWindow);
        actionWater->setObjectName(QString::fromUtf8("actionWater"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/utility/014-faucet.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionWater->setIcon(icon1);
        actionWiFi = new QAction(MainWindow);
        actionWiFi->setObjectName(QString::fromUtf8("actionWiFi"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/utility/009-modem.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionWiFi->setIcon(icon2);
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QString::fromUtf8("actionFile"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionDiscover = new QAction(MainWindow);
        actionDiscover->setObjectName(QString::fromUtf8("actionDiscover"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/utility/017-house.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDiscover->setIcon(icon3);
        actionTemperature = new QAction(MainWindow);
        actionTemperature->setObjectName(QString::fromUtf8("actionTemperature"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/utility/005-thermometer.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionTemperature->setIcon(icon4);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setAcceptDrops(false);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(-1, -1, 801, 411));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        toolBar->addAction(actionEnergy);
        toolBar->addAction(actionWater);
        toolBar->addAction(actionWiFi);
        toolBar->addAction(actionDiscover);
        toolBar->addAction(actionTemperature);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionEnergy->setText(QCoreApplication::translate("MainWindow", "Energy Usage", nullptr));
#if QT_CONFIG(tooltip)
        actionEnergy->setToolTip(QCoreApplication::translate("MainWindow", "Energy Usage", nullptr));
#endif // QT_CONFIG(tooltip)
        actionWater->setText(QCoreApplication::translate("MainWindow", "Water Usage", nullptr));
#if QT_CONFIG(tooltip)
        actionWater->setToolTip(QCoreApplication::translate("MainWindow", "Water Usage", nullptr));
#endif // QT_CONFIG(tooltip)
        actionWiFi->setText(QCoreApplication::translate("MainWindow", "WiFi", nullptr));
#if QT_CONFIG(tooltip)
        actionWiFi->setToolTip(QCoreApplication::translate("MainWindow", "WiFi", nullptr));
#endif // QT_CONFIG(tooltip)
        actionFile->setText(QCoreApplication::translate("MainWindow", "File", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionDiscover->setText(QCoreApplication::translate("MainWindow", "Discover", nullptr));
#if QT_CONFIG(tooltip)
        actionDiscover->setToolTip(QCoreApplication::translate("MainWindow", "Discover", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTemperature->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
#if QT_CONFIG(tooltip)
        actionTemperature->setToolTip(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
#endif // QT_CONFIG(tooltip)
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
