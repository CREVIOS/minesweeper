#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"
#include <QPixmap>
#include <QPainter>
#include "game_model.h" //These header files likely define the classes used in the application.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) /*his is the constructor for the MainWindow class, which is called when an instance of the class is created.
                            It takes a QWidget* pointer named parent as an argument, representing the parent widget of the main window.*/
    , ui(new Ui::MainWindow) //user interface (UI) for the main window.
{
    ui->setupUi(this); //sets up the user interface for the main window,
    setWindowTitle("Minesweeper with Treasure Hunt");
    QPixmap bkgnd(":/img/image/bg.png");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, bkgnd);    ,scaled(w,h,Qt::KeepAspectRatio)
//    this->setPalette(palette);

//    int w=ui->label_2->width();
//    int h=ui->label_2->height();
    ui->label->setPixmap(bkgnd);
};

//void MainWindow::resizeEvent(QResizeEvent *evt)
//{
//    QPixmap bkgnd("/Users/user/Desktop/GitHub/minesweeper/image/bg.bmp");//Load pic
//    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);//set scale of pic to match the window
//    QPalette p = palette(); //copy current, not create new
//    p.setBrush(QPalette::Window, bkgnd);//set the pic to the background
//    setPalette(p);//show the background pic
//    QMainWindow::resizeEvent(evt); //call base implementation
//}


void MainWindow::on_Start_Button_clicked()
{
   QWidget *swindow = new menu(this);
    swindow ->show();
    hide();
}

MainWindow::~MainWindow() //destructor for the MainWindow class, which is called when an instance of the class is destroyed
{
    delete ui;
}

