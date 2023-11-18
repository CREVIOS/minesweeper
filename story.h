#ifndef STORY_H
#define STORY_H

#include <QDialog>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class story;
}

class story : public QDialog
{
    Q_OBJECT

public:
    explicit story(QWidget *parent = nullptr);
    ~story();

private slots:

private:
    Ui::story *ui;
    QStackedWidget stackedWidget;
    QWidget page1;
    QWidget page2;

};

#endif // STORY_H
