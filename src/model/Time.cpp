#include "Time.hpp"

Time::Time(int hour, int minute) : hour(hour), minute(minute) {}


int Time::get_hour() const {
    return hour;
}

int Time::get_minute() const {
    return minute;
}

bool Time::operator<(const Time &other) const {
    if (hour < other.hour) {
        return true;
    }
    if (hour > other.hour) {
        return false;
    }
    if (minute < other.minute) {
        return true;
    }
    return false;
}

bool Time::operator>(const Time &other) const {
    return other < *this;
}

bool Time::operator<=(const Time &other) const {
    return !(*this > other);
}

bool Time::operator>=(const Time &other) const {
    return !(*this < other);
}

bool Time::operator==(const Time &other) const {
    return hour == other.hour && minute == other.minute;
}

bool Time::operator!=(const Time &other) const {
    return !(*this == other);
}

