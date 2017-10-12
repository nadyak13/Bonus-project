#include <string>

class Admin {
public:
	Admin(std::string, std::string);
	std::string get_login() const;
	std::string get_password() const;
	void set_password(std::string);
private:
	std::string login;
	std::string password;
};