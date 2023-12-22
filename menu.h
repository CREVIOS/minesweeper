#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();


private slots:

    void on_newgame_Button_clicked();

    void on_highscore_Button_clicked();

    void on_Quit_Button_clicked();

    void on_About_Button_clicked();

    void on_Back_Button_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
