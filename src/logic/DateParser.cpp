#include <vector>
#include <stdexcept>
#include "DateParser.hpp"
#include "Date.hpp"
#include "Splitter.hpp"

Date DateParser::parse(const std::string &s) {
    Splitter splitter('.');
    std::vector<std::string> splitted = splitter.split(s);
    if (splitted.size() != 3) {
        throw std::invalid_argument("Wrong number of positions");
    }
    size_t count;
    int day = std::stoi(splitted[0], &count);
    if (splitted[0].length() != count) {
        throw std::invalid_argument("Not only digits");
    }
    if (splitted[0].length() != 2) {
        throw(std::invalid_argument("Incorrect format of day"));
    }
    if (!(day <= 31 && day >= 1)){
        throw(std::invalid_argument("Incorrect value of day"));
    }
    int month = std::stoi(splitted[1], &count);
    if (splitted[1].length() != count) {
        throw std::invalid_argument("Not only digits");
    }
    if (splitted[1].length() != 2) {
        throw(std::invalid_argument("Incorrect format of month"));
    }
    if (!(month <= 12 && month >= 1)){
        throw(std::invalid_argument("Incorrect value of month"));
    }
    int year = std::stoi(splitted[2], &count);
    if (splitted[2].length() != count) {
        throw std::invalid_argument("Not only digits");
    }
    return Date(day, month, year);
}
