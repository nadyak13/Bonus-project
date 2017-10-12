#include "Client.hpp"

Client::Client(std::string login, std::string name, int account, double bonus_balance, double balance) : 
        login(login), name(name), account(account), bonus_balance(bonus_balance), balance(balance) {}
        
std::string Client::get_login() const {
    return login;
}        

std::string Client::get_name() const {
	return name;
}

int Client::get_account() const {
    return account;
}

double Client::get_bonus_balance() const {
    return bonus_balance;
}

double Client::get_balance() const {
    return balance;
}

void Client::set_balance(double new_balance) {
	balance = new_balance;
	return;
}

void Client::set_bonus_balance(double new_balance) {
	bonus_balance = new_balance;
	return;
}