#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font ( "Microsoft YaHei", 15, 80); //第一個屬性是字體（微軟雅黑），第二個是大小，第三個是加粗（權重是80）

//    int width = ui -> centralwidget -> width();
//    int tabCount = ui -> tabWidget -> count();
//    int tabWidth = width / tabCount;
//    this->setStyleSheet(QString("QTabBar::tab{width:%1px;height:50px;}").arg(tabWidth));

    ui -> Name -> setFont(font);
    ui -> Mac -> setFont(font);
    ui -> Status-> setFont(font);
    ui -> temperature -> setFont(font);
    ui -> humidity -> setFont(font);
    ui -> t_na -> setFont(font);
    ui -> h_na -> setFont(font);

}

MainWindow::~MainWindow()
{
    delete ui;
}

