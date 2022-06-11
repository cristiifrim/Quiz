#include "Repository.h"
#include <fstream>

void Repository::loadData()
{
	std::ifstream f("questions.txt");
	while (!f.eof()) {
		Question s;
		f >> s;
		this->data.push_back(s);
	}
	f.close();
}

void Repository::saveData()
{
	std::ofstream f("questions.txt");
	for (int i = 0; i < this->data.size() - 1; ++i)
		f << this->data[i] << "\n";
	f << this->data[this->data.size() - 1];
	f.close();
}

void Repository::add(Question s)
{
	this->data.push_back(s);
}

void Repository::remove(int index)
{
	this->data.erase(this->data.begin() + index);
}

int Repository::search(int id)
{
	for (int i = 0; i < this->data.size(); ++i)
		if (this->data[i].getID() == id)
			return i;
	return -1;
}


