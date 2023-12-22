#include "treasure.h"
#include "ui_treasure.h"
#include <QPainter.h>
Treasure::Treasure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Treasure)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
    QPixmap bkgnd("/Users/user/Desktop/GitHub/minesweeper/res/treasure.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

Treasure::~Treasure()
{
    delete ui;
}
