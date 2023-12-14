#include "story.h"
#include "ui_story.h"
#include <QApplication>
#include "game_model.h"
#include "story.h"
#include "sec_window.h"
story::story(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::story)
{
    ui->setupUi(this);

    int rows = 10;
    int columns = 10;
    int mines =10;
    GameLevel level_s = EASY;
    QWidget *swindow = new story_sec(rows,columns,mines, level_s,this);
    swindow ->show();
    hide();

}

story::~story()
{
    delete ui;
}


