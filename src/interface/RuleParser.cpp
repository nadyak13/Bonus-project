#include "RuleParser.hpp"
#include "DateParser.hpp"
#include "TimeParser.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include <stdexcept>
#include "Splitter.hpp"
#include "Rule.hpp"
#include "Predicate.hpp"
#include "FileWriter.hpp"

void RuleParser::gt() {
    if (!symb_read) {
        gc_space();
    }
    if ((c >= 'a' && c <= 'z') || c == '.' || c == ':' || c == '_' || (c >= '1' && c <= '9') || c == '0') {
        t.clear_token();
        while ((c >= 'a' && c <= 'z') || c == '.' || c == ':' || c == '_' || (c >= '1' && c <= '9') || c == '0') {
            t.add_char(c);
            gc();
            symb_read = true;
        }
        if (isspace(c)) symb_read = false;
        word = true;
        oper = false;
    } else if (c == '=' || c == '>' || c == '<') {
        t.clear_token();
        t.add_char(c);
        if (endd) {
            throw ParseException();
        }
        gc();
        symb_read = true;
        if (isspace(c)) symb_read = false;
        if (c == '>' || c == '=') {
            if (c == '>' && (t.get_token() == ">" || t.get_token() == "=")) {
                throw ParseException();
            }
            if (c == '=' && t.get_token() == "=") {
                throw ParseException();
            }
            symb_read = false;
            t.add_char(c);
        } //////////вставить проверку
        oper = true;
        word = false;
    } else {
        word = false;
        oper = false;

        symb_read = false;
        if (c == ',') {
            correctEnd = true;
            endd = true;
        }
    }
}

void RuleParser::gc() {
    c = s[0];
    if (c != ',' && !s.empty()) {
        endd = false;
    } else {
        endd = true;
        if (s.empty()) {
            correctEnd = false;
        }
        if (c == ',') {
            correctEnd = true;
        }
    }
    s.erase(0, 1);
}    
/*
void RuleParser::gc() {
    if (c = getchar() != ',' && c != EOF) {
        //std::cout << "gc : " << c << "]" << std::endl;
        endd = false;
    } else {
        endd = true;
        if (c == EOF) {
            correctEnd = false;
        }
        if (c == ',') {
            correctEnd = true;
        }
    }
}  
*/
void RuleParser::gc_space() {
    gc();
    while (isspace(c)) {
        gc();
    }
}

static int num = 0;

std::shared_ptr<Predicate> RuleParser::V() {
    if (!(oper || word)) {
        throw ParseException();
    }
    if (word) {
        if (t.get_token() == "date") {
            std::string what = t.get_token();
            gt();   
            if (!oper || endd) {
                throw ParseException();
            }
            std::string operation = t.get_token();
            gt();
            if (!word) {
                throw ParseException();
            } else {
                std::string value = t.get_token();
                try {
                    DateParser::parse(t.get_token());
                    if (operation == "=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new EqualPredicate(what, value, num));
                    } else if (operation == "<>") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new NotEqualPredicate(what, value, num));
                    } else if (operation == ">") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new GreaterPredicate(what, value, num));
                    } else if (operation == ">=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new GreaterEqualPredicate(what, value, num));
                    } else if (operation == "<") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new LessPredicate(what, value, num));
                    } else if (operation == "<=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new LessEqualPredicate(what, value, num));
                    }
                } catch (std::invalid_argument) {
                    throw ParseException();
                }
            }
        } else if (t.get_token() == "time") {
            std::string what = t.get_token();
            gt();
            if (!oper || endd) {
                throw ParseException();
            }
            std::string operation = t.get_token();
            gt();
            if (!word) {
                throw ParseException();
            } else {
                std::string value = t.get_token();
                try {
                    TimeParser::parse(t.get_token());
                    if (operation == "=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new EqualPredicate(what, value, num));
                    } else if (operation == "<>") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new NotEqualPredicate(what, value, num));
                    } else if (operation == ">") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new GreaterPredicate(what, value, num));
                    } else if (operation == ">=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new GreaterEqualPredicate(what, value, num));
                    } else if (operation == "<") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new LessPredicate(what, value, num));
                    } else if (operation == "<=") {
                        gt();
                        num++;
                        return std::shared_ptr<Predicate>(new LessEqualPredicate(what, value, num));
                    }
                } catch (std::invalid_argument) {
                    throw ParseException();
                }
            }
        } else if (t.get_token() == "shop") {
            std::string what = t.get_token();
            gt();
            if (!oper || endd) {
                throw ParseException();
            }
            std::string operation = t.get_token();
            gt();
            if (!word) {
                throw ParseException();
            }
            std::string value = t.get_token();
            if (operation == "=") {
                gt();
                num++;
                return std::shared_ptr<Predicate>(new EqualPredicate(what, value, num));
            } else if (operation == "<>") {
                gt();
                num++;
                return std::shared_ptr<Predicate>(new NotEqualPredicate(what, value, num));
            }
        } else if (t.get_token() == "amount") {
            std::string what = t.get_token();
            gt();
            if (!oper || endd) {
                throw ParseException();
            }
            std::string operation = t.get_token();
            gt();
            if (!word ) {
                throw ParseException();
            } else {
                std::string value = t.get_token();
                size_t pos;
                std::stod(t.get_token(), &pos);
                if (pos != t.get_token().length()) {
                    throw ParseException();
                }
                if (operation == "=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new EqualPredicate(what, value, num));
                } else if (operation == "<>") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new NotEqualPredicate(what, value, num));
                } else if (operation == ">") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new GreaterPredicate(what, value, num));
                } else if (operation == ">=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new GreaterEqualPredicate(what, value, num));
                } else if (operation == "<") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new LessPredicate(what, value, num));
                } else if (operation == "<=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new LessEqualPredicate(what, value, num));
                }
            }
        } else if (t.get_token() == "balance") {
            std::string what = t.get_token();
            gt();
            if (!oper || endd) {
                throw ParseException();
            }
            std::string operation = t.get_token();
            gt();
            if (!word ) {
                throw ParseException();
            } else {
                std::string value = t.get_token();
                size_t pos;
                std::stod(t.get_token(), &pos);
                if (pos != t.get_token().length()) {
                    throw ParseException();
                }
                if (operation == "=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new EqualPredicate(what, value, num));
                } else if (operation == "<>") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new NotEqualPredicate(what, value, num));
                } else if (operation == ">") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new GreaterPredicate(what, value, num));
                } else if (operation == ">=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new GreaterEqualPredicate(what, value, num));
                } else if (operation == "<") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new LessPredicate(what, value, num));
                } else if (operation == "<=") {
                    gt();
                    num++;
                    return std::shared_ptr<Predicate>(new LessEqualPredicate(what, value, num));
                }
            }
        } else {
            throw ParseException();
        }
    } else {
        if (oper) {
            throw ParseException();
        }
    }
    throw ParseException();
}


std::shared_ptr<Predicate> RuleParser::A() {
    if (!(oper || word)) {
        if (c == '(') {
            gt();
            std::shared_ptr<Predicate> r = F();
            if (c != ')' || endd)  {
                throw ParseException();
            }
            gt();
            return r;
        } else {
            throw ParseException();
        }
    } else {
        return V();
    }
}

std::shared_ptr<Predicate> RuleParser::N() {
    if (!(oper || word)) {
        if (c == '!') {
            gt();
            return std::shared_ptr<Predicate>(new NegationPredicate(N(), ++num));
        } else if ((c != '(') || endd) {
            throw ParseException();
        } else {
            return A();
        }
    } else {
        return A();
    }
}

std::shared_ptr<Predicate> RuleParser::C() {
    if (!(oper || word)) {
        if (!(c == '!' || c == '(' )) {
            throw ParseException();
        }
    }
    std::shared_ptr<Predicate> left = N();
    while (c == '&') {
        gt();
        if (!(oper || word)) {
            if (!(c == '!' || c == '(')) {
                throw ParseException();
            }
        }
        std::shared_ptr<Predicate> right = N();
        num++;
        left = std::shared_ptr<Predicate>(new AndPredicate(left, right, num));
    }
    return left;
}

std::shared_ptr<Predicate> RuleParser::D() {
    if (!(oper || word)) {
        if (!(c == '!' || c == '(')) {
            throw ParseException();
        }
    }
    std::shared_ptr<Predicate> left = C();
    while (c == '|') {
        gt();
        if (!(oper || word)) {
            if (!(c == '!' || c == '(')) {
                throw ParseException();
            }
        }
        std::shared_ptr<Predicate> right = C();
        num++;
        left = std::shared_ptr<Predicate>(new OrPredicate(left, right, num));
    }
    return left;
}

std::shared_ptr<Predicate> RuleParser::F() {
    if (!(oper || word)) {
        if (!(c == '!' || c == '(')) {
            throw ParseException();
        }
    }
    std::shared_ptr<Predicate> left = D();
    while (c == '-') {
        gt();
        if (!(oper || word)) {
            if (!(c == '!' || c == '(')) {
                throw ParseException();
            }
        }
        std::shared_ptr<Predicate> right = D();
        num++;
        left = std::shared_ptr<Predicate>(new FollowPredicate(left, right, num));
    }
    return left;
}

void RuleParser::set_s(std::string s) {
    RuleParser::s = s;
}

std::shared_ptr<Rule> RuleParser::parse(std::string s) {
    correctEnd = false;
    endd = false;
    symb_read = false;
    try {
        set_s(s);
        gt();
        if (t.get_token() != "add") {
            throw ParseException();
        }
        gt();
        if (t.get_token() != "rule:") {
            throw ParseException();
        }

        gt();
        if (t.get_token() != "if") {
            throw(ParseException());
        }
        gt();
        std::shared_ptr<Predicate> res = F();
        if (endd && correctEnd) { 
            gt();
            if (t.get_token() != "bonus") {
                throw ParseException();
            }
            gt();
            if (t.get_token() == "bonus") {
                throw ParseException();
            }
            size_t pos;
            stod(t.get_token(), &pos);
            if (t.get_token().length() != pos) {
                throw ParseException();
            }
            std::shared_ptr<Rule> new_rule = std::shared_ptr<Rule>(new Rule(res, t.get_token()));
            num = 0;
            return new_rule;
        } else {
            throw ParseException();
        }
    } catch (ParseException &) {
        num = 0;
        return nullptr;
    }
}    
