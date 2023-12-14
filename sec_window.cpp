#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include<qmenubar.h>
#include "sec_window.h"
#include "ui_sec_window.h"
#include "mainwindow.h"
#include "game_model.h"
#include <QStatusBar>

const int blockSize = 20;
const int offsetX = 55;//boundary
const int offsetY = 30;// block game boundary
const int spaceY = 60;//timer,menu space

sec_window::sec_window(int rows, int columns, int mines, GameLevel level_s, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sec_window)
{
    ui->setupUi(this);
    setWindowTitle("MineSweeper with Treasure Hunt");
    //customLevelDialog = nullptr;
    timeLabel = new QLabel(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    //(ui->Button_Custom, SIGNAL(triggered()), this, SLOT(showCustomLevelDialog()));

    game = new GameModel;
    game->createGame(rows,columns,mines, level_s);
    Timer();
}

//void sec_window::showCustomLevelDialog()
//{
//    if (!customLevelDialog) {
//        customLevelDialog = new customized(this);
//        connect(customLevelDialog, &customized::accepted, this, &sec_window::handleCustomLevelAccepted);
//    }

//    customLevelDialog->show();
//}

//void sec_window::handleCustomLevelAccepted()
//{
//    int rows = customLevelDialog->getRows();
//    int columns = customLevelDialog->getColumns();
//    int mines = customLevelDialog->getMines();

//    game->createGame(rows, columns, mines, CUSTOM);  // Use CUSTOM level
//    Timer();
//    update();  // Refresh the display
//}

void sec_window::updateTimer()
{
    if (game->gameState != OVER && game->gameState != WIN)
    {
        timeLabel->setText("Time: " + QString::number(++game->timerSeconds) + " s");
    }
}

void sec_window::Timer(){
    setFixedSize(game->mCol * blockSize  + offsetX * 2, game->mRow * blockSize + offsetY * 2 + spaceY);
    timeLabel->setGeometry(game->mCol * blockSize + offsetX * 2 - 80, spaceY / 2, 80, 20);
    timeLabel->setText("Time: " + QString::number(game->timerSeconds) + " s");
    timer->start(1000);
}

void sec_window::paintEvent(QPaintEvent *event)
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

void sec_window::mousePressEvent(QMouseEvent *event)
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

sec_window::~sec_window()
{
    delete ui;
}

void sec_window::back()
{
     this->hide();
     QWidget *parent = this->parentWidget();
     parent->show();
}

//void sec_window::restart()
//{
//       //game->restartGame();
//}

//void sec_window::on_Button_Easy_clicked()
//{
//        qDebug() << "easy";
//        game->createGame(10, 10, 10, EASY);
//        Timer();
//}

//void sec_window::on_Button_Medium_clicked()
//{
//        qDebug() << "medium";
//        game->createGame(15, 15, 40, MEDIUM);
//        Timer();
//}

//void sec_window::on_Button_Hard_clicked()
//{
//        qDebug() << "hard";
//        game->createGame(25, 25, 80, HARD);
//        Timer();
//}

void sec_window::on_Button_Back_clicked()
{
        back();
}


void sec_window::on_Restart_Button_clicked()
{
        int rows,columns,mines;
        rows=game->mRow;
        columns=game->mCol;
        mines=game->totalMineNumber;
        game->createGame(rows,columns,mines,game->gameLevel);  // Or use appropriate parameters for the game restart
        Timer();
        update();
}




//void sec_window::on_Button_Custom_clicked()
//{
//        customLevelDialog = new customized(this);
//        if (customLevelDialog->exec() == QDialog::Accepted)
//        {
//        int rows = customLevelDialog->getRows();
//        int columns = customLevelDialog->getColumns();
//        int mines = customLevelDialog->getMines();

//        game->createGame(rows, columns, mines, CUSTOM);  // Use CUSTOM level
//        Timer();
//        update();  // Refresh the display
//        }
//        delete customLevelDialog;
//}

