#include "menu.h"
#include "ui_menu.h"
#include "modewindow.h"
#include "about.h"
#include "highscore.h"
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
}

void menu::on_newgame_Button_clicked()
{
    QWidget *swindow = new Modewindow(this);
    swindow ->show();
    hide();
}

void menu::on_Quit_Button_clicked()
{
    QCoreApplication::quit();
}

void menu::on_About_Button_clicked()
{
    QWidget *swindow = new about(this);
    swindow ->show();
    hide();
}

void menu::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}


menu::~menu()
{
    delete ui;
}

void menu::on_about_Button_clicked()
{
    QWidget *swindow = new highscore(this);
    swindow ->show();
    hide();
    qDebug()<<"It's working\n";
}

