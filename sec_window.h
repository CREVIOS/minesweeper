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
}

class sec_window : public QDialog
{
    Q_OBJECT

public:
    explicit sec_window(QWidget *parent = nullptr);
    ~sec_window();
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private slots:

    void back();
//    void restart();
    void Timer();
    void updateTimer();
    void on_Button_Easy_clicked();
    void on_Button_Medium_clicked();
    void on_Button_Hard_clicked();

    void on_Button_Back_clicked();
    void on_Restart_Button_clicked();
//    void on_Button_Custom_clicked();

    void showCustomLevelDialog();
    void handleCustomLevelAccepted();
    void on_Button_Custom_clicked();

private:
    Ui::sec_window *ui;
    GameModel *game;
    QTimer *timer;
    QLabel *timeLabel;
    QLabel *infoLabel;
    customized *customLevelDialog;
//    bool easy =true;
//    bool medium =false;
//    bool hard =false;

};

#endif // SEC_WINDOW_H
