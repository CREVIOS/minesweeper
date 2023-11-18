#include "about.h"
#include "ui_about.h" //user interface definition for the about class

about::about(QWidget *parent) : //constructor for the about class
    QDialog(parent), //QDialog is a class in the Qt framework used to create dialog windows
    ui(new Ui::about)
{
    ui->setupUi(this); // set up the UI components for a dialog or window.
}

about::~about() //destructor, is automatically called when an object of a class is being destroyed
{
    delete ui;
}

void about::on_Back_Button_clicked() //This slot function is triggered when a button with the object name "Back_Button" is clicked. This is likely the "Back" button in the "About" dialog.
{
    this->hide();
    QWidget *parent = this->parentWidget(); //This line gets the parent widget of the "About" dialog, which is likely the main application window.
    parent->show();
}

