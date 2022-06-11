#pragma once
#include "Subject.h"
#include <string>
#include <vector>
#include "Repository.h"

class Service : public Subject 
{
	Repository& repo;

public:
	Service(Repository& repo) : repo{ repo } {}
	void add(int id, const std::string& text, const std::string& correctAnswer, int score);
	bool answer(int id, const std::string& ans);
	int getScore(int id);
	std::vector<Question> getByID();
	std::vector<Question> getByScore();
};

