#pragma once

#include <string>

class Participant
{
	std::string name;
	int score;

public:
	Participant() = default;
	Participant(const std::string& name) : name{name}, score{0} {}
	std::string getName() const { return this->name; }
	int getScore() const { return this->score; }
	void increaseScore(int amount) { this->score += amount; }
	friend std::istream& operator>>(std::istream& in, Participant& q);
	friend std::ostream& operator<<(std::ostream& in, Participant& q);
};

