#pragma once
#include <vector>
#include "Participant.h"

class ParticipantsRepo
{
	std::vector<Participant> data;
	void loadData();
public:
	ParticipantsRepo() { this->loadData(); }
	~ParticipantsRepo() { this->saveData(); }
	void add(Participant p) { this->data.push_back(p); }
	std::vector<Participant>& get() { return this->data; }
	void saveData();
};

