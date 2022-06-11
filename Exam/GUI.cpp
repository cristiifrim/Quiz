#include "GUI.h"
#include <sstream>
#include <qmessagebox.h>
#include <fstream>

GUI::GUI(Service& srv, Participant& type, QWidget *parent)
    : serv{ srv }, type{ type }, QMainWindow(parent)
{
    ui.setupUi(this);
    this->serv.addObserver(this);
    connectSignalsAndSlots();
    this->update();

    this->setWindowTitle("Presenter");

    if (this->type.getName() != "presenter") {
        this->setWindowTitle(QString::fromStdString(this->type.getName()));
        this->ui.idLabel->hide();
        this->ui.idEdit->hide();
        this->ui.scoreEdit->setReadOnly(true);
        this->ui.scoreEdit->setText(QString::fromStdString(std::to_string(this->type.getScore())));
        this->ui.textLabel->hide();
        this->ui.textEdit->hide();
        this->ui.pushButton->setText("Answer");
    }
}

void GUI::addAnswer()
{
    if (this->type.getName() == "presenter") {
        int id = this->ui.idEdit->text().toInt();
        int score = this->ui.scoreEdit->text().toInt();
        std::string text = this->ui.textEdit->text().toStdString();
        std::string ans = this->ui.answerEdit->text().toStdString();

        try {
            this->serv.add(id, text, ans, score);
            this->ui.answerEdit->clear();
            this->ui.idEdit->clear();
            this->ui.scoreEdit->clear();
            this->ui.textEdit->clear();
        }
        catch (std::exception& e) {
            QMessageBox box;
            box.setText(e.what());
            box.exec();
        }
    }
    else {
        std::string ans = this->ui.answerEdit->text().toStdString();
        for (auto it : this->ui.listWidget->selectedItems()) {
            std::string line = it->text().toStdString();
            std::stringstream ss{ line };
            std::string token;

            std::getline(ss, token, ':');
            std::getline(ss, token, ' ');

            std::stringstream ss2{ token };
            std::getline(ss, token, ',');

            int id = std::stoi(token);

            try {
                if (this->serv.answer(id, ans)) {
                    this->answered.push_back(id);
                    this->type.increaseScore(this->serv.getScore(id));
                    this->ui.scoreEdit->setText(QString::fromStdString(std::to_string(this->type.getScore())));
                    it->setBackground(Qt::green);
                    this->ui.pushButton->setDisabled(true);
                }
                else {
                    QMessageBox box;
                    box.setText("Wrong answer!");
                    box.exec();
                }
            }
            catch (std::exception& e) {
                QMessageBox box;
                box.setText(e.what());
                box.exec();
            }

        }
    }
}

void GUI::checkAnswer()
{
    int id = -1;
    for (auto it : this->ui.listWidget->selectedItems()) {
        std::string line = it->text().toStdString();
        std::stringstream ss{ line };
        std::string token;

        std::getline(ss, token, ':');
        std::getline(ss, token, ' ');

        std::stringstream ss2{ token };
        std::getline(ss, token, ',');

        id = std::stoi(token);
    }

    for (int i = 0; i < this->answered.size(); ++i) {
        if (answered[i] == id) {
            this->ui.pushButton->setDisabled(true);
            return;
        }
    }
    this->ui.pushButton->setDisabled(false);
}

void GUI::update()
{
    this->ui.listWidget->clear();
    if (type.getName() == "presenter") {
        for (auto it : this->serv.getByID()) {
            std::stringstream txt{};
            txt << "ID: " << it.getID() << ", Question: " << it.getText() << ", Answer : " << it.getCorrectAnswer() << ", Score : " << it.getScore();
            this->ui.listWidget->addItem(QString::fromStdString(txt.str()));
        }
    }
    else {
        for (auto it : this->serv.getByScore()) {
            std::stringstream txt{};
            txt << "ID: " << it.getID() << ", Question: " << it.getText() << ", Score : " << it.getScore();
            this->ui.listWidget->addItem(QString::fromStdString(txt.str()));
        }
    }
}

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this->ui.pushButton, &QAbstractButton::clicked, this, &GUI::addAnswer);
    QObject::connect(this->ui.listWidget, &QListWidget::itemClicked, this, &GUI::checkAnswer);
}
