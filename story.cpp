#include "story.h"
#include "ui_story.h"
#include <QApplication>


story::story(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::story)
{
    ui->setupUi(this);
    QStackedWidget stackedWidget;

    QPushButton button1("Go to Page 2");
    QWidget page1(&stackedWidget);


    QPushButton button2("Go to Page 1");
    QWidget page2(&stackedWidget);

    stackedWidget.addWidget(&page1);
    stackedWidget.addWidget(&page2);
    QObject::connect(&button1, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentIndex(1);
    });

    QObject::connect(&button2, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentIndex(0);
    });
    /*QWidget mainWindow;
    QVBoxLayout mainLayout(&mainWindow);
    mainLayout.addWidget(&stackedWidget);

    // ..*/

}

story::~story()
{
    delete ui;
}


