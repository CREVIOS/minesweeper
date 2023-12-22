#ifndef LEVEL_H
#define LEVEL_H

#include <QDialog>
#include "customized.h"
namespace Ui {
class level;
}

class level : public QDialog
{
    Q_OBJECT

public:
    explicit level(QWidget *parent = nullptr);
    ~level();

private slots:
    void on_Easy_clicked();
    void on_meidum_clicked();
    void on_hard_clicked();
    void on_Custom_clicked();
    void showCustomLevelDialog();
    void handleCustomLevelAccepted();
    void on_Back_Button_clicked();

private:
    Ui::level *ui;
    customized *customLevelDialog;

};

#endif // LEVEL_H
