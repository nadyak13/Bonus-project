#include "ClientInterface.hpp"
#include <iostream>
#include <string>
#include "DateParser.hpp"
#include "TimeParser.hpp"

void ClientInterface::menu() const {
    std::cout << "ACTIONS:                  ENTER" << std::endl;
    std::cout << "show menu                 menu" << std::endl;
    std::cout << "login                     login" << std::endl;
    std::cout << "logout                    logout" << std::endl;
    std::cout << "information about you     info" << std::endl;
    std::cout << "make payment              payment" << std::endl;
    std::cout << "exit                      exit" << std::endl;
}

void ClientInterface::main_client() {
    menu();
    while (true) {
        std::cout << ">  " ;
        std::string s;
        std::getline(std::cin, s);
        if (s =="menu") {
            menu();
        } else if (s == "login") {
            login();
        } else if (s == "logout") {
            logout();
        } else if (s == "info") {
            info();
        } else if (s == "payment") {
            make_payment();
        } else if (s == "exit") {
            return;
        } else {
            std::cout << "Incorrect command! Try again!" << std::endl;
        }
    }
}

void ClientInterface::login() {
    std::cout << "Enter login: ";
    std::string login;
    std::getline(std::cin, login);
    std::shared_ptr<Client> client = login_controller.get_client(login);
    if (client != nullptr) {
        this->client = client;
        std::cout << "Login complete!!!" << std::endl;
    } else {
        std::cout << "Login failed." <<  std::endl;
    }
}

void ClientInterface::logout() {
    client = nullptr;
    std::cout << "Logout complete." << std::endl;
}

void ClientInterface::info() const {
    if (client == nullptr) {
        std::cout << "You aren't login." <<  std::endl;
        return;
    }
    std::cout << "Login: " << client->get_login() << std::endl;
    std::cout << "Name: " << client->get_name() << std::endl;
    std::cout << "Account number: " << client->get_account() << std::endl;
    std::cout << "Bonus balance: "; //<< client->get_bonus_balance() << std::endl; ;
    printf("%.2lf\n", client->get_bonus_balance());
    std::cout << "Balance: ";//<< client->get_balance() << std::endl;
    printf("%.2lf\n", client->get_balance());
};

Date ClientInterface::input_date(const std::string &str) {
    std::string s;
    while (true) {
        std::cout << str;
        std::getline(std::cin, s);
        try {
            return DateParser::parse(s);
        } catch (std::invalid_argument) {
            std::cout << "Incorrect date format! Please, try again!" << std::endl;
        }
    }
}

Time ClientInterface::input_time(const std::string &str) {
    std::string s;
    while (true) {
        std::cout << str;
        std::getline(std::cin, s);
        try {
            return TimeParser::parse(s);
        } catch (std::invalid_argument) {
            std::cout << "Incorrect time format! Please, try again!" << std::endl;
        }
    }
}

double ClientInterface::input_amount(const std::string &str) {
    std::string s;
    while (true) {
        std::cout << str;
        std::getline(std::cin, s);
        size_t count;
        try {
            double sum = std::stod(s, &count);
            if (s.length() != count) { 
                throw std::invalid_argument("Error: amount - not only digits");
            }
            return sum;
        } catch (std::invalid_argument) {
            std::cout << "Incorrect amount format! Please, try again!" << std::endl;
        }
    }
}

void ClientInterface::make_payment() {
    if (client == nullptr) {
        std::cout << "You aren't login! " << std::endl;
        return;
    }
    Date date = input_date("Enter date of payment in format - DD.MM.YYYY : ");
    Time time = input_time("Enter time of payment in format - HH:MM : ");
    std::string shop;
    std::cout << "Enter name of the shop: ";
    std::getline(std::cin, shop);
    double amount = input_amount("Enter amount of payment (real number with '.') : ");
    try {
        double bonus = payment_controller.make_payment(date, time, client, shop, amount);
        std::cout << bonus << " bonuses accrued." << std::endl;
        std::cout << "Payment was done!" << std::endl;   
    } catch(std::invalid_argument) {
        std::cout << "Your balance is less than payment amount! Payment can't be made. " << std::endl;
    }
}
