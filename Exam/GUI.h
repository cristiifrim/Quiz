#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Observer.h"
#include "Service.h"
#include "Participant.h"
#include "ParticipantsRepo.h"

class GUI : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    GUI(Service& srv, Participant& p, QWidget *parent = Q_NULLPTR);
    void addAnswer();
    void checkAnswer();

private:
    Ui::GUIClass ui;
    Participant& type;
    Service& serv;
    std::vector<int> answered;
    void update() override;
    void connectSignalsAndSlots();
};
