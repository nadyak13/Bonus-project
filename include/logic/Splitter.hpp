#include <vector>
#include <string>

class Splitter {
public:
    Splitter(char);
    std::vector<std::string> split(const std::string &) const;
private:
    char delimiter;
};