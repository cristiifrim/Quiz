#include "ParticipantsRepo.h"
#include <fstream>

void ParticipantsRepo::loadData()
{
	std::ifstream f("participants.txt");
	while (!f.eof()) {
		Participant s;
		f >> s;
		this->data.push_back(s);
	}
	f.close();
}

void ParticipantsRepo::saveData()
{
	std::ofstream f("participants.txt");
	for (int i = 0; i < this->data.size() - 1; ++i)
		f << this->data[i] << "\n";
	f << this->data[this->data.size() - 1];
	f.close();
}
