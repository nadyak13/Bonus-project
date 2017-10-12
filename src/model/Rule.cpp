#include <stdexcept>
#include <iostream>
#include "Rule.hpp"
#include "Payment.hpp"
#include "Predicate.hpp"

Rule::Rule(std::shared_ptr<Predicate> p, std::string count) : p(p), count(count) {}

std::shared_ptr<Predicate> Rule::get_predicate() const {
    return p;
}

std::string Rule::get_count() const {
    return count;
}
