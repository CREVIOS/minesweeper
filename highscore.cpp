#include "highscore.h"
#include "ui_highscore.h"

highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
}

highscore::~highscore()
{
    delete ui;
}

void highscore::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}
