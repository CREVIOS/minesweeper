#ifndef SEC_WINDOW_H
#define SEC_WINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QDialog>
#include"game_model.h"
#include "mainwindow.h"

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
    void on_pushButton_clicked();
    void back();
    void restart();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::sec_window *ui;
    GameModel *game;
    QTimer *timer;
    QLabel *timeLabel;
    QLabel *infoLabel;
    bool easy =true;
    bool medium =false;
    bool hard =false;

};

#endif // SEC_WINDOW_H
