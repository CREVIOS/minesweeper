#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "sec_window.h"
#include "modewindow.h"
#include "about.h"
#include "ui_about.h"
#include "game_model.h" //These header files likely define the classes used in the application.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) /*his is the constructor for the MainWindow class, which is called when an instance of the class is created.
                            It takes a QWidget* pointer named parent as an argument, representing the parent widget of the main window.*/
    , ui(new Ui::MainWindow) //user interface (UI) for the main window.
{
    ui->setupUi(this); //sets up the user interface for the main window,
    setWindowTitle("Minesweeper with Treasure Hunt");
}

MainWindow::~MainWindow() //destructor for the MainWindow class, which is called when an instance of the class is destroyed
{
    delete ui;
}

void MainWindow::on_Start_Button_clicked()
{
   QWidget *swindow = new Modewindow(this);
    swindow ->show();
    hide();
}

void MainWindow::on_Quit_Button_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_About_Button_clicked()
{
    QWidget *swindow = new about(this);
    swindow ->show();
    hide();
}

