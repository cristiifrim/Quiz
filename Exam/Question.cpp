#include "Question.h"
#include <sstream>
#include <vector>

std::istream& operator>>(std::istream& in, Question& q)
{
    std::string token, line;
    std::getline(in, line);
    std::stringstream ss{ line };
    std::vector<std::string> res;
    while (std::getline(ss, token, ','))
        res.push_back(token);
    if (res.size() != 4)
        return in;
    q.id = std::stoi(res[0]);
    q.text = res[1];
    q.correctAnswer = res[2];
    q.score = std::stoi(res[3]);
    return in;
}

std::ostream& operator<<(std::ostream& in, Question& q)
{
    in << q.id << "," << q.text << "," << q.correctAnswer << "," << q.score;
    return in;
}

