#include "Token.hpp"

void Token::add_char(char c) {
    s += c;
}
void Token::clear_token() {
    s = "";
}

std::string Token::get_token() const {
    return s;
}