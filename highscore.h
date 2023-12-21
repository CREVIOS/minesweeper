#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <QDialog>

namespace Ui {
class highscore;
}

class highscore : public QDialog
{
    Q_OBJECT

public:
    explicit highscore(QWidget *parent = nullptr);
    ~highscore();

private slots:

void on_Back_Button_clicked();


private:
    Ui::highscore *ui;
};

#endif // HIGHSCORE_H
