#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include<qmenubar.h>
#include "sec_window.h"
#include "ui_sec_window.h"
#include "game_model.h"
#include <QStatusBar>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

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

    timeLabel = new QLabel(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    game = new GameModel;
    game->createGame(rows,columns,mines, level_s);
    Timer();
}

void sec_window::updateTimer()
{
    if(game->gameState==WIN){
        highscore();
    }
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
    result();
}

void sec_window::result(){

     if (game->gameState == OVER) {
        // Show a losing message
        QMessageBox::warning(this, "", "SORRY! You Lose!");
     }
     if(game->gameState == WIN){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(updateTimer())); // Disconnect the timer
        // Show a wining message
        QMessageBox::warning(this, "", "BRAVO! You Win!");
        highscore();

     }
     timer->stop();

}

void sec_window::highscore() {
      string filePath = "/Users/asifsadek/Documents/GitHub/minesweeper";
     if (game->gameLevel == EASY) {
        filePath = filePath + "/Easy.txt";
     } else if (game->gameLevel == MEDIUM) {
        filePath = filePath + "/Medium.txt";
     } else if(game->gameLevel == HARD){
        filePath = filePath + "/Hard.txt";
     }
     qDebug()<<filePath<<"\n";
     const int defaultScore = 1000000000;

     int time = game->timerSeconds;
     int array[5];

     // Read existing highscores from the file
     std::ifstream infile(filePath);
     if (infile.is_open()) {
        for (int i = 0; i < 5; ++i) {
            if (!(infile >> array[i])) {
                array[i] = defaultScore;
            }
        }
        infile.close();
     } else {
        // Handle the case where the file doesn't exist or can't be opened
        for (int i = 0; i < 5; ++i) {
            array[i] = defaultScore;
        }
     }

     // Check if the current time qualifies for the highscore
     for (int i = 0; i < 5; ++i) {
        if (time < array[i]) {
            // Shift lower scores down to make room for the new highscore
            for (int j = 4; j > i; --j) {
                array[j] = array[j - 1];
            }
            array[i] = time;
            break;
        }
     }

     // Write the updated highscores back to the file
     std::ofstream outfile(filePath, std::ios::trunc); // Use trunc to overwrite the file
     if (outfile.is_open()) {
        for (int i = 0; i < 5; ++i) {
            outfile << array[i] << "\n";
        }
        outfile.close();
     } else {
        // Handle the case where the file can't be opened for writing
        std::cerr << "Error: Unable to open " << filePath << " for writing\n";
     }
}


void sec_window::on_Button_Back_clicked()
{
     this->hide();
     QWidget *parent = this->parentWidget();
     parent->show();
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

sec_window::~sec_window()
{
        delete ui;
}

