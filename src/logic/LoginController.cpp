#include "LoginController.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"

LoginController::LoginController(std::string file1, std::string file2) : 
        reader_cl(std::shared_ptr<FileReader>(new FileReader(file1))),
        reader_admin(std::shared_ptr<FileReader>(new FileReader(file2))),
        writer_admin(std::shared_ptr<FileWriter>(new FileWriter(file2))),
        writer_cl(std::shared_ptr<FileWriter>(new FileWriter(file1))) {}


std::shared_ptr<Client> LoginController::get_client(std::string login) {
    std::vector<std::shared_ptr<Client>> clients = reader_cl->clients();
    for (std::shared_ptr<Client> client : clients) {
        if (client->get_login() == login) {
            return client;
        }
    }
    return nullptr;
}

std::vector<std::string> LoginController::get_all_logins() {
    std::vector<std::shared_ptr<Client>> clients = reader_cl->clients();
    std::vector<std::string> list;
    for (std::shared_ptr<Client> client : clients) {
        list.push_back(client->get_login());
    }
    return  list;
}

std::shared_ptr<Admin> LoginController::get_admin(std::string login, std::string password) {
    std::shared_ptr<Admin> admin = reader_admin->admin();
    if (admin != nullptr) {
        if (login == admin->get_login() && password == admin->get_password()) {
            return admin;
        }
    }
    return nullptr;
}

void LoginController::change_password(std::string new_password, std::shared_ptr<Admin> admin) {
    admin->set_password(new_password);
    writer_admin->admin(admin);
}

bool LoginController::check_login(std::string new_login) {
    std::vector<std::shared_ptr<Client>> cl = reader_cl->clients();
    for (std::shared_ptr<Client> client : cl) {
        if (client->get_login() == new_login) {
            return false;
        }
    }
    return true; 
}

int LoginController::create_free_account() {
    std::vector<std::shared_ptr<Client>> cl = reader_cl->clients();
    int new_account;
    int tmp = 0;
    while (true) {
        tmp = 0;
        new_account = (rand() % 1000000);
        if (new_account < 100000) {
            continue;
        }
        for (std::shared_ptr<Client> client : cl) {
            if (client->get_account() == new_account) {
                tmp = 0;
                break;
            }
            tmp = 1;
        }
        if (tmp == 1) {
            return new_account;
        }
    }
}

void LoginController::add_client(std::shared_ptr<Client> new_client) {
    writer_cl->client_add(new_client);
}

void LoginController::change_client(std::shared_ptr<Client> client) {
    writer_cl->client_change(client);
}