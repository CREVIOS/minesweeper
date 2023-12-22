#include "highscore.h"
#include "ui_highscore.h"

highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
}

void highscore::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}


highscore::~highscore()
{
    delete ui;
}
