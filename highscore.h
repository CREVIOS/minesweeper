#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <QDialog>
#include <QTextBrowser>

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
    void on_back_clicked();

private:
    Ui::highscore *ui;
    void loadHighScores(const std::string& fileName, QTextBrowser* textBrowser);
};

#endif // HIGHSCORE_H
