#include <string>
#include <memory>
#include "Date.hpp" 
#include "Time.hpp"


class Client;

class Payment {
public:
    Payment(Date date, Time time, std::shared_ptr<Client> client, std::string shop, double amount);
    Date get_date() const;
    Time get_time() const;
    std::shared_ptr<Client> get_client() const;
    std::string get_shop() const;
    double get_amount() const;
private:
	Date date;
    Time time;
    std::shared_ptr<Client> client;
    std::string shop;
    double amount;
};
