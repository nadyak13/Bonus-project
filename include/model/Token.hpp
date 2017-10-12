#include <string>

class Token {
private:
    std::string s;
public:
    void add_char(char);
    void clear_token();
    std::string get_token() const;
};