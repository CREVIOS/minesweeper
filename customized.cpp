#include "customized.h"
#include "ui_customized.h"
#include <QMessageBox>

customized::customized(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customized)
{
    ui->setupUi(this);
}

customized::~customized()
{
    delete ui;
}

int customized::getRows() const
{
   return ui->spinRow->value();
}

int customized::getColumns() const
{
   return ui->spinColumn->value();
}

int customized::getMines() const
{
//   int r=getRows();
//   int c=getColumns();
//   int check=ui->spinMine->value();
//   while(check<=(int)(r*c*0.15)){
//       check=ui->spinMine->value();
//   }
   return ui->spinMine->value();
}

void customized::on_Done_Button_clicked()
{
   int rows = getRows();
   int columns = getColumns();
   int mines = getMines();

   // Ensure that the number of mines is within the allowed range
   if (mines >= rows * columns * 0.12) {
       // Continue with the accepted signal
       accept();
   } else {
       // Show a warning message
       QMessageBox::warning(this, "Warning", "Number of mines should be at least 12% of the total cells.");
   }
}

//void customized::on_Done_Button_clicked()
//{
//   close();
//}

