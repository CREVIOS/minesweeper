#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Start_Button_clicked();

    void on_Quit_Button_clicked();

    void on_About_Button_clicked();

private:

    bool easy =1;
    bool medium =0;
    bool hard =0;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
