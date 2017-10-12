#include <string>
#include <memory>

class Client {
public: 
    Client(std::string login, std::string name, int account, double bonus_balance, double balance);
    std::string get_login() const;
    std::string get_name() const;
    int get_account() const;
    double get_bonus_balance() const;
    double get_balance() const;
    void set_balance(double);
    void set_bonus_balance(double);
private:
	std::string login;
	std::string name;
	int account;
	double bonus_balance;
	double balance;
};
