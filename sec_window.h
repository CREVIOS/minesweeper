#ifndef SEC_WINDOW_H
#define SEC_WINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QDialog>
#include"game_model.h"
#include "mainwindow.h"
#include "customized.h"


namespace Ui {
class sec_window;
class story_sec;
}

class sec_window : public QDialog
{
    Q_OBJECT

public:
    explicit sec_window(int rows, int columns, int mines, GameLevel level_s, QWidget *parent = nullptr);
    ~sec_window();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:

    void back();
    void Timer();
    void updateTimer();


    void on_Button_Back_clicked();
    void on_Restart_Button_clicked();

private:
    Ui::sec_window *ui;
    GameModel *game;
    QTimer *timer;
    QLabel *timeLabel;
    QLabel *infoLabel;
    customized *customLevelDialog;


};


class story_sec : public QDialog
{
    Q_OBJECT

public:
    explicit story_sec(int rows, int columns, int mines, GameLevel level_s, QWidget *parent = nullptr);
    ~story_sec();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:

    void back();
    void Timer();
    void updateTimer();
    void GameStart(int rows, int columns, int mines, GameLevel level_s);
    void on_Button_Back_clicked();
    void on_Restart_Button_clicked();

private:
    Ui::sec_window *ui;
    GameModel *game;
    QTimer *timer;
    QLabel *timeLabel;
    QLabel *infoLabel;
    customized *customLevelDialog;

};

#endif // SEC_WINDOW_H
