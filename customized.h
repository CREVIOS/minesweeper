#ifndef CUSTOMIZED_H
#define CUSTOMIZED_H

#include <QDialog>

namespace Ui {
class customized;
}

class customized : public QDialog
{
    Q_OBJECT

public:
    explicit customized(QWidget *parent = nullptr);
    ~customized();
    int getRows() const;
    int getColumns() const;
    int getMines() const;

private slots:
    void on_Done_Button_clicked();

private:
    Ui::customized *ui;

};

#endif // CUSTOMIZED_H
