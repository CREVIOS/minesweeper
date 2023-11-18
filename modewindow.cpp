#include "modewindow.h"
#include "ui_modewindow.h"
#include "sec_window.h"
#include "story.h"

Modewindow::Modewindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Modewindow)
{
    ui->setupUi(this);
}

Modewindow::~Modewindow()
{
    delete ui;
}

void Modewindow::on_Story_Button_clicked()
{
    QWidget *swindow = new story(this);
    swindow ->show();
    hide();
}


void Modewindow::on_Normal_Button_clicked()
{
    QWidget *swindow = new sec_window(this);
    swindow ->show();
    hide();
}


void Modewindow::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}

