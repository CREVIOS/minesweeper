#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QMessageBox>
#include<qmenubar.h>
#include "sec_window.h"
#include "ui_sec_window.h"
#include "mainwindow.h"
#include <QStatusBar>
const int blockSize = 20;
const int offsetX = 5;
const int offsetY = 5;
const int spaceY = 70;

sec_window::sec_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sec_window)
{
    ui->setupUi(this);
    setWindowTitle("MineSweeper");
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QString message = tr("A context menu is available by right-clicking");
//    QStatusBar::statusBar()->showMessage(message);

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
    timeLabel = new QLabel(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    game = new GameModel;
    game->createGame();
    setFixedSize(game->mCol * blockSize + offsetX * 2, game->mRow * blockSize + offsetY * 2 + spaceY);
    timeLabel->setGeometry(game->mCol * blockSize + offsetX * 2 - 80, spaceY / 2, 80, 20);
    timeLabel->setText("Time: " + QString::number(game->timerSeconds) + " s");
    timer->start(1000);
}

void sec_window::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap bmpBlocks(":/res/blocks.bmp");
    QPixmap bmpFaces(":/res/faces.bmp");
    QPixmap bmpFrame(":/res/frame.bmp");
    QPixmap bmpNumber(":/res/timenumber.bmp");

    switch(game->gameState)
    {
    case OVER:
        painter.drawPixmap((game->mCol * blockSize + offsetX * 2) / 2 - 12, spaceY / 2, bmpFaces, 0 * 24, 0, 24, 24); // 24是笑脸的边长,锚点在左上，因为工具栏占了些，所以看起来不再中间
        break;
    case PLAYING:
        painter.drawPixmap((game->mCol * blockSize + offsetX * 2) / 2 - 12, spaceY / 2, bmpFaces, 1 * 24, 0, 24, 24);
        break;
    case WIN:
        painter.drawPixmap((game->mCol * blockSize + offsetX * 2) / 2 - 12, spaceY / 2, bmpFaces, 2 * 24, 0, 24, 24);
        break;
    default:
        painter.drawPixmap((game->mCol * blockSize + offsetX * 2) / 2 - 12, spaceY / 2, bmpFaces, 1 * 24, 0, 24, 24);
        break;
    }

    // 绘制剩余雷数
    int n = game->curMineNumber;
    int posX = (game->mCol * blockSize + offsetX * 2) / 2 - 50; // 最后一位数字的横坐标
    if(n <= 0) // 如果雷数为0或者减到0以下，单独绘制
    {
        painter.drawPixmap(posX, spaceY / 2, bmpNumber, n * 20, 0, 20, 28); // 20是数字的宽，28是高
    }
    while(n > 0) // 如果是多位数
    {
        painter.drawPixmap(posX - 20, spaceY / 2, bmpNumber, n % 10 * 20, 0, 20, 28); // 每次从后面绘制一位
        n /= 10;
        posX -= 20;
    }

    // 绘制雷区
    for(int i = 0; i < game->mRow; i++)
    {
        for(int j = 0; j < game->mCol; j++)
        {
            switch(game->gameMap[i][j].curState)
            {
            // 根据不同的方块状态绘制，算出在bmp中的偏移量
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
                if(game->gameState == PLAYING || game->gameState == FAULT)
                {
                    // 如果还在游戏中就显示旗子
                    painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 11, 0, blockSize, blockSize);
                }
                else if(game->gameState == OVER)
                {
                    // 如果游戏已经结束，就显示标错了
                    painter.drawPixmap(j * blockSize + offsetX, i * blockSize + offsetY + spaceY, bmpBlocks, blockSize * 12, 0, blockSize, blockSize);
                }
                break;
            default:
                break;
            }
        }
    }
//    // 处理游戏状态
//    handleGameState(game);
}

sec_window::~sec_window()
{
    delete ui;
}

void sec_window::on_pushButton_clicked()
{
    back();
}

void sec_window::back()
{
    this->hide();
    QWidget *parent = this->parentWidget();
    parent->show();

}
void  sec_window::createMenus()
{

    QMainWindow win;
    QMenu * menuFile = new QMenu("&File",win.menuBar());

    QAction * newAction = new QAction("new", menuFile);
    QAction * exitAction = new QAction("exit", menuFile);

    menuFile->addActions(QList<QAction *>()<<newAction<<exitAction);
    win.menuBar()->addAction(menuFile->menuAction());
}
#ifndef QT_NO_CONTEXTMENU
void sec_window::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.addAction(backgo);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
void sec_window::restart()
{

}

