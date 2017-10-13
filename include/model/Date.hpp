class Date {
public:
    Date(int, int, int);
    int get_day() const;
    int get_month() const;
    int get_year() const;
    bool operator> (const Date&) const;
    bool operator< (const Date&) const;
    bool operator>= (const Date&) const;
    bool operator<= (const Date&) const;
    bool operator== (const Date&) const;
    bool operator!= (const Date&) const;
private:
    int day;
    int month;
    int year;
};
