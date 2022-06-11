#include "Service.h"
#include <algorithm>

void Service::add(int id, const std::string& text, const std::string& correctAnswer, int score)
{
	if(text.empty())
		throw std::exception("Failed!\nEmpty question!");
	if (this->repo.search(id) != -1)
		throw std::exception("Failed!\nQuestion already in repo!");

	Question s{ id, text, correctAnswer, score };
	this->repo.add(s);
	this->notify();
}

bool Service::answer(int id, const std::string& ans)
{
	int index = this->repo.search(id);
	return this->repo[index].getCorrectAnswer() == ans;
}

int Service::getScore(int id)
{
	int index = this->repo.search(id);
	return this->repo[index].getScore();
}


std::vector<Question> Service::getByID()
{
	std::vector<Question> data = this->repo.get();
	std::sort(data.begin(), data.end(), [](Question a, Question b) {
		return a.getID() < b.getID();
		});
	return data;
}

std::vector<Question> Service::getByScore()
{
	std::vector<Question> data = this->repo.get();
	std::sort(data.begin(), data.end(), [](Question a, Question b) {
		return a.getScore() > b.getScore();
		});
	return data;
}
