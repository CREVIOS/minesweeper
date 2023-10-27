#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sec_window.h"
#include "game_model.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QWidget *swindow = new sec_window(this);
    swindow ->show();
    hide();
}


void MainWindow::on_pushButton_3_clicked()
{
    QCoreApplication::quit();
}


