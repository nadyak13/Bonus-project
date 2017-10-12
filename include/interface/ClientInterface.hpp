#include <memory>
#include "LoginController.hpp"
#include "PaymentController.hpp"


class Date;
class Time;
class Client;


class ClientInterface {
public:
    void main_client();
    void menu() const;
    void login();
    void make_payment();
    void info() const;
    void logout();

    static Date input_date(const std::string &);
    static Time input_time(const std::string &);
    static double input_amount(const std::string &);
private:
    std::shared_ptr<Client> client;
    LoginController login_controller;
    PaymentController payment_controller;
};