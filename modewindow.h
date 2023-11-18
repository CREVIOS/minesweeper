#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QDialog>

namespace Ui {
class Modewindow;
}

class Modewindow : public QDialog
{
    Q_OBJECT

public:
    explicit Modewindow(QWidget *parent = nullptr);
    ~Modewindow();

private slots:
    void on_Story_Button_clicked();

    void on_Normal_Button_clicked();

    void on_Back_Button_clicked();

private:
    Ui::Modewindow *ui;
};

#endif // MODEWINDOW_H
