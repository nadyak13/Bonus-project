#include "TimeParser.hpp"
#include "Time.hpp"
#include "Splitter.hpp"
#include <vector>
#include <stdexcept>

Time TimeParser::parse(const std::string &s) {
    Splitter splitter(':');
    std::vector<std::string> splitted = splitter.split(s);
    if (splitted.size() != 2) {
        throw std::invalid_argument("Wrong number of positions");
    }
    size_t count;
    int hour = std::stoi(splitted[0], &count);
    if (splitted[0].length() != count) {
        throw std::invalid_argument("Not only digits");
    }
    if (splitted[0].length() != 2) {
        throw std::invalid_argument("Incorrect format of hour");
    }
    if (!(hour >= 0 && hour <= 23)) {
        throw std::invalid_argument("Incorrect value of hour");
    }
    int minute = std::stoi(splitted[1], &count);
    if (splitted[1].length() != count) {
        throw std::invalid_argument("Not only digits");
    }
    if (splitted[1].length() != 2) {
        throw std::invalid_argument("Incorrect format of minute");
    }
    if (!(minute >= 0 && minute <= 59)) {
        throw std::invalid_argument("Incorrect value of minute");
    }
    return Time(hour, minute);
}