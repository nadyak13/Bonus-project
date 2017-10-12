#include "Splitter.hpp"
#include <iostream>

Splitter::Splitter(char delimiter) : delimiter(delimiter) {}

std::vector<std::string> Splitter::split(const std::string &s) const {
    std::vector<std::string> result;  
    size_t pos = 0;
    std::string token;  
    std::string str = s;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        result.push_back(token);
        str.erase(0, pos + 1); 
    }
    result.push_back(str);
    return result;
}
