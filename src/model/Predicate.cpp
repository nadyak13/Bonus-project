#include "Predicate.hpp"

void AndPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void OrPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void NegationPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void FollowPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void EqualPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void NotEqualPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void GreaterPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void GreaterEqualPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void LessPredicate::accept(Visitor &v) {
    v.visit(*this);
}

void LessEqualPredicate::accept(Visitor &v) {
    v.visit(*this);
}

AndPredicate::AndPredicate(std::shared_ptr<Predicate> left, std::shared_ptr<Predicate> right, int number) :
        left(left), right(right), number(number) {}

std::shared_ptr<Predicate> AndPredicate::get_left() const {
    return left;
}

std::shared_ptr<Predicate> AndPredicate::get_right() const {
    return right;
}

OrPredicate::OrPredicate(std::shared_ptr<Predicate> left, std::shared_ptr<Predicate> right, int number) :
        left(left), right(right),  number(number) {}

std::shared_ptr<Predicate> OrPredicate::get_left() const {
    return left;
}

std::shared_ptr<Predicate> OrPredicate::get_right() const {
    return right;
}

NegationPredicate::NegationPredicate(std::shared_ptr<Predicate> right, int number) : left(nullptr), right(right),  number(number) {}

std::shared_ptr<Predicate> NegationPredicate::get_left() const {
    return left;
}

std::shared_ptr<Predicate> NegationPredicate::get_right() const {
    return right;
}

FollowPredicate::FollowPredicate(std::shared_ptr<Predicate> left, std::shared_ptr<Predicate> right, int number) :
        left(left), right(right),  number(number) {}

std::shared_ptr<Predicate> FollowPredicate::get_left() const {
    return left;
}

std::shared_ptr<Predicate> FollowPredicate::get_right() const {
    return right;
}

EqualPredicate::EqualPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),  number(number) {}

std::string EqualPredicate::get_what() const {
    return what;
}

std::string EqualPredicate::get_value() const {
    return value;
}

NotEqualPredicate::NotEqualPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),  number(number) {}

std::string NotEqualPredicate::get_what() const {
    return what;
}

std::string NotEqualPredicate::get_value() const{
    return value;
}


GreaterPredicate::GreaterPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),number(number) {}

std::string GreaterPredicate::get_what() const {
    return what;
}

std::string GreaterPredicate::get_value() const{
    return value;
}



GreaterEqualPredicate::GreaterEqualPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),  number(number) {}

std::string GreaterEqualPredicate::get_what() const {
    return what;
}

std::string GreaterEqualPredicate::get_value() const{
    return value;
}


LessPredicate::LessPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),  number(number) {}

std::string LessPredicate::get_what() const {
    return what;
}

std::string LessPredicate::get_value() const{
    return value;
}


LessEqualPredicate::LessEqualPredicate(std::string s1, std::string s2, int number) :
        what(s1), value(s2),  number(number) {}

std::string LessEqualPredicate::get_what() const {
    return what;
}

std::string LessEqualPredicate::get_value() const{
    return value;
}

std::string BinaryPredicate::get_what() const {
    return "";
}

std::string BinaryPredicate::get_value() const {
    return "";
}

std::shared_ptr<Predicate> SubjectPredicate::get_left() const {
    return nullptr;
}

std::shared_ptr<Predicate> SubjectPredicate::get_right() const {
    return nullptr;
}

int AndPredicate::get_number() const {
    return number;
}

int OrPredicate::get_number() const {
    return number;
}

int NegationPredicate::get_number() const {
    return number;
}

int FollowPredicate::get_number() const {
    return number;
}

int EqualPredicate::get_number() const {
    return number;
}

int NotEqualPredicate::get_number() const {
    return number;
}

int GreaterPredicate::get_number() const {
    return number;
}

int GreaterEqualPredicate::get_number() const {
    return number;
}

int LessPredicate::get_number() const {
    return number;
}

int LessEqualPredicate::get_number() const {
    return number;
} 