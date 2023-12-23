#include "highscore.h"
#include "ui_highscore.h"

highscore::highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::highscore)
{
    ui->setupUi(this);

    std::string filePath = "/Users/asifsadek/Documents/GitHub/minesweeper";

        std::string filePath1 = filePath + "/Easy.txt";

         std::string filePath2 = filePath + "/Medium.txt";

         std::string filePath3 = filePath + "/Hard.txt";

    loadHighScores(filePath1, ui->easyScores);
    loadHighScores(filePath2, ui->mediumScores);
    loadHighScores(filePath3, ui->hardScores);
}

highscore::~highscore()
{
    delete ui;
}

void highscore::on_back_clicked()
{
    this->hide();
    QWidget *parent = this->parentWidget(); //This line gets the parent widget of the "About" dialog, which is likely the main application window.
    parent->show();
}
void highscore::loadHighScores(const std::string& fileName, QTextBrowser* textBrowser)
{
    std::ifstream file(fileName);
    if (!file.is_open()) {
        // Handle the case where the file cannot be opened
        std::cerr << "Error: Unable to open " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int score;
        iss >> score;
        textBrowser->append(QString::number(score) + " seconds");
    }

    file.close();
}
