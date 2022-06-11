#pragma once
#include <vector>
#include "Question.h"
class Repository
{
	std::vector<Question> data;
	void loadData();
	void saveData();

public:
	Repository() { this->loadData(); }
	void add(Question s);
	void remove(int index);
	int search(int id);
	int size() { return this->data.size(); }
	std::vector<Question> get() { return this->data; }
	Question& operator[](int index) { if (index < 0 || index >= this->data.size()) throw std::exception("Invalid index!"); return this->data[index]; }
	~Repository() { this->saveData(); }
};

