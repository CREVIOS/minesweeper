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


    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();



    void on_easybutton_clicked();

    void on_mediumbutton_clicked();

    void on_hardbutton_clicked();

private:
    Ui::MainWindow *ui;
    qint64 levels=0;
};
#endif // MAINWINDOW_H
