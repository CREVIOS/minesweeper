#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include<qmenubar.h>
#include "sec_window.h"
#include "ui_sec_window.h"
#include "game_model.h"
#include "treasure.h"
#include <QStatusBar>

const int blockSize = 20;
const int offsetX = 55;//boundary
const int offsetY = 30;// block game boundary
const int spaceY = 60;//timer,menu space

story_sec::story_sec(int rows, int columns, int mines, GameLevel level_s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sec_window)
{
    ui->setupUi(this);
    setWindowTitle("MineSweeper with Treasure Hunt");
    timeLabel = new QLabel(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    game = new GameModel;
    game->createGame(rows,columns,mines, level_s);
    Timer();
}

void story_sec::updateTimer()
{
    if (game->gameState != OVER && game->gameState != WIN)
    {
        timeLabel->setText("Time: " + QString::number(++game->timerSeconds) + " s");
    }

    if(game->gameState == WIN && game->gameLevel==EASY ){

        GameStart(12,12,40,MEDIUM);
    }
    else if(game->gameState == WIN && game->gameLevel==MEDIUM ){

        GameStart(15,15,60,HARD);
    }
    else if(game->gameState == WIN && game->gameLevel==HARD ){
        result();
        QWidget *swindow = new Treasure(this);
        swindow ->show();
        hide();
    }
    else if(game->gameState == OVER){
        result();
        GameStart(9,9,10,EASY);
    }
}

void story_sec::result(){

    if (game->gameState == OVER) {
        // Show a losing message
        QMessageBox::warning(this, "", "SORRY! You Lose!");
    }
    if(game->gameState == WIN){
        // Show a wining message
        QMessageBox::warning(this, "", "BRAVO! You Win!");
    }
}

void story_sec::Timer(){
    setFixedSize(game->mCol * blockSize  + offsetX * 2, game->mRow * blockSize + offsetY * 2 + spaceY);
    timeLabel->setGeometry(game->mCol * blockSize + offsetX * 2 - 80, spaceY / 2, 80, 20);
    timeLabel->setText("Time: " + QString::number(game->timerSeconds) + " s");
    timer->start(1000);
}

void story_sec::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bmpBlocks(":/res/blocks.bmp");
    QPixmap bmpNumber(":/res/timenumber.bmp");
    int n = game->curMineNumber;
    int posX = (game->mCol * blockSize + offsetX * 2) / 2 - 50;

    if(n <= 0)
    {
        painter.drawPixmap(posX, spaceY / 2, bmpNumber, n * 20, 0, 20, 28);
    }
    while(n > 0)
    {
        painter.drawPixmap(posX - 20, spaceY / 2, bmpNumber, n % 10 * 20, 0, 20, 28);
        n /= 10;
        posX -= 20;
    }

    for(int i = 0; i < game->mRow; i++)
    {
        for(int j = 0; j < game->mCol; j++)
        {
            switch(game->gameMap[i][j].curState)
            {

            case UN_DIG:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY , bmpBlocks, blockSize * 10, 0, blockSize, blockSize);
                break;
            case DIGGED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * game->gameMap[i][j].valueFlag, 0, blockSize, blockSize);
                break;
            case MARKED:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                break;
            case BOMB:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 9, 0, blockSize, blockSize);
                break;
            case WRONG_BOMB:
                painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 12, 0, blockSize, blockSize);
                break;
            default:
                break;
            }
        }
    }
}

void story_sec::mousePressEvent(QMouseEvent *event)
{
    if(game->gameState != OVER && game->gameState != WIN)
    {
        QPointF position = event->position();
        int px = position.x() - offsetX;
        int py = position.y() - offsetY - spaceY;

        int row = py / blockSize;
        int col = px / blockSize;

        switch(event->button())
        {
        case Qt::LeftButton:
            game->digMine(row, col);
            update();
            break;
        case Qt::RightButton:
            game->markMine(row, col);
            update();
            break;
        default:
            break;
        }
    }
}

void story_sec::on_Button_Back_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();
}

void story_sec::GameStart(int rows, int columns, int mines, GameLevel level_s){

    game->createGame(rows,columns,mines, level_s);
    Timer();
    update();
}

void story_sec::on_Restart_Button_clicked()
{
    int rows,columns,mines;
    rows=game->mRow;
    columns=game->mCol;
    mines=game->totalMineNumber;
    game->createGame(rows,columns,mines,game->gameLevel);  // Or use appropriate parameters for the game restart
    Timer();
    update();
}

story_sec::~story_sec()
{
    delete ui;
}




