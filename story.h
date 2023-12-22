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
    void on_Back_Button_clicked();
    void on_start_Button_clicked();

private:
    Ui::story *ui;
};

#endif // STORY_H
