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
        highscore();
        // Show a wining message
        QMessageBox::warning(this, "", "BRAVO! You Win!");
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


//void sec_window::highscore()
//{
//        int time=game->timerSeconds;
//        int array[5]={1000000000,1000000000,1000000000,1000000000,1000000000};
//        std::fstream FileName;
//        if(game->gameLevel==EASY){
//            FileName.open("Easy.txt", std::ios::out | std::ios::in );
//        }
//        if(game->gameLevel==MEDIUM){
//            FileName.open("Medium.txt", std::ios::out | std::ios::in );
//        }
//        if(game->gameLevel==HARD){
//            FileName.open("Hard.txt", std::ios::out | std::ios::in );
//        }
//        if(game->gameLevel==CUSTOM){
//            FileName.open("Custom.txt", std::ios::out | std::ios::in );
//        }
//        int x=0;
//        while (x<5) {
//          if(FileName.eof())
//            break;
//          FileName>>array[x];
//          x++;
//        }

//        x=0;
//        while (x<5) {
//          if(array[x]>=time){
//            int y=4;
//            while(y>x){
//                array[y]=array[y-1];
//                y--;
//               }
//            array[y]=time;
//            break;}
//          x++;
//        }

//        x=0;
//        while (x<5) {
//          FileName<<array[x]<<" ";
//          x++;
//        }
//        FileName.close();

//}


void sec_window::highscore(){


        int arr[5];

        //int arrFromFile[5];
        ifstream ifs("Easy.txt");
//        if (!ifs.is_open())
//        cout << "File isn`t opened!";
//        else
//        {
        string line;
        string str = "";
        getline(ifs, line, '\n');
        int k= 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ' ')
            {
                arr[k++] = stoi(str);
                str = "";
            }
            else
                str += line[i];
        }
       // }
        ifs.close();
        ofstream of;
        of.open("Easy.txt");
        //        if (!of.is_open())
        //        cout << "File isn`t opened!";
        //        else
        //        {
        for (int i = 0; i < 5; i++)
        {
        of << arr[i] << " ";
        }
        // }
        of.close();
}
