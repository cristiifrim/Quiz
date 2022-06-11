#include "Participant.h"
#include <vector>
#include <sstream>

std::istream& operator>>(std::istream& in, Participant& q)
{
    std::string token, line;
    std::getline(in, line);
    std::stringstream ss{ line };
    std::vector<std::string> res;
    while (std::getline(ss, token, ','))
        res.push_back(token);
    if (res.size() != 2)
        return in;
    q.name = res[0];
    q.score = std::stoi(res[1]);
    return in;
}

std::ostream& operator<<(std::ostream& in, Participant& q)
{
    in << q.name << "," << q.score;
    return in;
}

