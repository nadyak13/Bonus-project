#include <memory>
#include <vector>
#include "LoginController.hpp"
#include "RuleController.hpp"

class Admin;
class Predicate;

class AdminInterface {
public:
    void main_admin();
    void menu() const;
    void login();
    void logout();
    void change_password();
    void add_client();
    void change_client_balance();
    void print_clients();
    void print_info_client();
    std::vector<std::string> creation_subject_predicate_two();
    std::vector<std::string> creation_subject_predicate_one();
    void add_rule();
    void print_rule_menu();
    void add_rule_with_commands();
    std::shared_ptr<Predicate> create_predicate();
    void delete_all_rules();
    void delete_rule();
    void print_rules();
    //void delete_rule_bonus();
    //void write_list_rule();
private:
    std::shared_ptr<Admin> admin;
    LoginController login_controller;
    RuleController rule_controller;
};