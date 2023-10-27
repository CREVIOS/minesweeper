#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sec_window.h"
#include"game_model.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget()->setStyleSheet(
        "background-image:url(\"res/bgimage.jpg\"); background-position: center;" );
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_6_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::on_pushButton_5_clicked()
{
    QWidget *swindow = new sec_window(this);
    swindow ->show();
    hide();
}




void MainWindow::on_easybutton_clicked()
{
    levels=0;
}


void MainWindow::on_mediumbutton_clicked()
{
    levels=1;
}


void MainWindow::on_hardbutton_clicked()
{
    levels=2;
}

