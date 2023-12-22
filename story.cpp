#include "story.h"
#include "ui_story.h"
#include <QApplication>
#include "sec_window.h"

story::story(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::story)
{
    ui->setupUi(this);
    setWindowTitle("Minesweeper with Treasure Hunt");
}

story::~story()
{
    delete ui;
}

void story::on_Back_Button_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void story::on_start_Button_clicked()
{
    int rows = 10;
    int columns = 10;
    int mines = 10;
    GameLevel level_s = EASY;

    // Assuming story_sec takes rows, columns, mines, level_s, and parent as parameters
    QWidget *swindow = new story_sec(rows, columns, mines, level_s, this);
    swindow->show();
    hide();
}
