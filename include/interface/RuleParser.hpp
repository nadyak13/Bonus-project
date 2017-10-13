#include <string>
#include <iostream>
#include <memory>
#include "Token.hpp"

class ParseException {
};

class Predicate;
class Rule;

class RuleParser {
private:
    Token t;
    char c;
    std::string s;
    bool endd;
    bool word;
    bool oper;
    bool symb_read;
    bool correctEnd;
    void gt();
    void gc();  
    void gc_space();
    void set_s(std::string);
    std::shared_ptr<Predicate> V();
    std::shared_ptr<Predicate> A();
    std::shared_ptr<Predicate> N();
    std::shared_ptr<Predicate> C();
    std::shared_ptr<Predicate> F();
    std::shared_ptr<Predicate> D();
public:
    std::shared_ptr<Rule> parse(std::string);
};
