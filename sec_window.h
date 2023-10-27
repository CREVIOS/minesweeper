#ifndef SEC_WINDOW_H
#define SEC_WINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QDialog>
#include"game_model.h"
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
    void contextMenuEvent(QContextMenuEvent *event) override;
//    virtual void mousePressEvent(QMouseEvent *event);
private slots:
    void on_pushButton_clicked();
    void back();
    void restart();

private:
    Ui::sec_window *ui;
    GameModel *game;
    QTimer *timer;
    QLabel *timeLabel;
    QMenu *mainMenu;
    QLabel *infoLabel;
    void createActions();
    void createMenus();
    QActionGroup *alignmentGroup;
    QAction *backgo;
};

#endif // SEC_WINDOW_H
