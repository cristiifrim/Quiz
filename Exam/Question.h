#pragma once
#include <string>
#include <iostream>
class Question
{
	int id;
	std::string text;
	std::string correctAnswer;
	int score;

public:
	Question() {}
	Question(int id, const std::string& text, const std::string& correct, int score) 
		: id{id}, text{text}, correctAnswer{correct}, score{score} {}
	int getID() const { return this->id; }
	std::string getText() const { return this->text; }
	std::string getCorrectAnswer() const { return this->correctAnswer; }
	int getScore() const { return this->score; }
	friend std::istream& operator>>(std::istream& in, Question& q);
	friend std::ostream& operator<<(std::ostream& in, Question& q);
};

