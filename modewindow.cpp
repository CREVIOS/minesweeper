#include "modewindow.h"
#include "ui_modewindow.h"
#include "story.h"
#include "level.h"

Modewindow::Modewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modewindow)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
}

void Modewindow::on_Story_Button_clicked()
{
    QWidget *swindow = new story(this);
    swindow ->show();
    hide();
}

void Modewindow::on_Normal_Button_clicked()
{
    QWidget *swindow = new level(this);
    swindow ->show();
    hide();
}

void Modewindow::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}

Modewindow::~Modewindow()
{
    delete ui;
}
