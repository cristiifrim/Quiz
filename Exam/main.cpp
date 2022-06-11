#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Repository.h"
#include "Participant.h"
#include <fstream>
#include "ParticipantsRepo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{};
    ParticipantsRepo participants{};
    Service serv{ repo };
    Participant u{ "presenter" };
    for (int i = 0; i < participants.get().size(); ++i) {
        GUI* pw = new GUI{ serv, participants.get()[i]};
        pw->show();
    }
    GUI w{serv, u};
    w.show();
    return a.exec();
}
