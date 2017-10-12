#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "Client.hpp"
#include "Admin.hpp"


class FileReader;
class FileWriter;


class LoginController {
public:
    LoginController(std::string file1 = "clients.txt", std::string file2 = "admin.txt");
    std::shared_ptr<Client> get_client(std::string);
    std::shared_ptr<Admin> get_admin(std::string, std::string);
    void change_password(std::string, std::shared_ptr<Admin>);
    bool check_login(std::string);
    int create_free_account();
    void add_client(std::shared_ptr<Client>);
    void change_client(std::shared_ptr<Client>);
    std::vector<std::string> get_all_logins();
private:
    std::shared_ptr<FileReader> reader_cl;
    std::shared_ptr<FileReader> reader_admin;
    std::shared_ptr<FileWriter> writer_admin;
    std::shared_ptr<FileWriter> writer_cl;
};

