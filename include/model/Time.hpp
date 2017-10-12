class Time {
public:
    Time(int, int);
    int get_hour() const;
    int get_minute() const;
    bool operator> (const Time&) const;
    bool operator< (const Time&) const;
    bool operator>= (const Time&) const;
    bool operator<= (const Time&) const;
    bool operator== (const Time&) const;
    bool operator!= (const Time&) const;
private:
    int hour;
    int minute;
};
