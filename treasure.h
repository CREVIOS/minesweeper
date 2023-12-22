#ifndef TREASURE_H
#define TREASURE_H

#include <QDialog>

namespace Ui {
class Treasure;
}

class Treasure : public QDialog
{
    Q_OBJECT

public:
    explicit Treasure(QWidget *parent = nullptr);
    ~Treasure();

private:
    Ui::Treasure *ui;
};

#endif // TREASURE_H
