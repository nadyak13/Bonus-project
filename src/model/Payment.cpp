#include "Payment.hpp"


Payment::Payment(Date date, Time time, std::shared_ptr<Client> client, std::string shop, double amount) :
		date(date),
        time(time),
        client(client),
        shop(shop),
        amount(amount) {}
        
Date Payment::get_date() const {
	return date;
}

Time Payment::get_time() const {
    return time;
}

std::shared_ptr<Client> Payment::get_client() const {
    return client;
}

std::string Payment::get_shop() const {
    return shop;
}

double Payment::get_amount() const {
    return amount;
}