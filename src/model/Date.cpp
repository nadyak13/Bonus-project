#include "Date.hpp"

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}


int Date::get_day() const {
    return day;
}

int Date::get_month() const {
    return month;
}

int Date::get_year() const {    
    return year;
}

bool Date::operator< (const Date &other) const {
    if (year < other.year) {
        return true;
        
    }
    if (year > other.year) {
        return false;
    }
    if (month < other.month) {
        return true;
    }
    if (month > other.month) {
        return false;
    }
    if (day < other.day) {
        return true;
    }
    if (day > other.day) {
        return false;
    }
    return false;
}

bool Date::operator> (const Date &other) const {
    return other < *this;
}

bool Date::operator<= (const Date &other) const {
    return !(*this > other);
}

bool Date::operator>= (const Date &other) const {
    return !(*this < other);
}

bool Date::operator== (const Date &other) const {
    return !(*this > other || *this < other);
}

bool Date::operator!= (const Date &other) const {
    return !(*this == other);
}

