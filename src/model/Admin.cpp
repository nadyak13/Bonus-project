#include "Admin.hpp"
#include <string>

Admin::Admin(std::string login, std::string password) : 
		login(login), password(password) {}

std::string Admin::get_login() const {
	return login;
}

std::string Admin::get_password() const { 
	return password;
} 

void Admin::set_password(std::string p) {
	password = p;
}