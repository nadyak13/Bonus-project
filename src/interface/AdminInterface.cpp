#include "AdminInterface.hpp"
#include <stdexcept>
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "DateParser.hpp"
#include "TimeParser.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "RuleParser.hpp"
#include "Rule.hpp"
#include "Predicate.hpp"

void AdminInterface::menu() const {
    std::cout << "ACTIONS:                          ENTER: " << std::endl;
    std::cout << "show menu                         menu" << std::endl;
    std::cout << "login                             login" << std::endl;
    std::cout << "logout                            logout" << std::endl;
    std::cout << "change password                   change pw" << std::endl;
    std::cout << "add client                        client" << std::endl;
    std::cout << "show a list of client logins      show clients" << std::endl;
    std::cout << "show client information           show info" << std::endl;
    std::cout << "change client balance             balance" << std::endl;
    std::cout << "add rule                          rule" << std::endl;
    std::cout << "delete rules                      delete" << std::endl;
    std::cout << "exit                              exit" << std::endl;
}

void AdminInterface::main_admin() {
    menu();
    while (true) {
        std::cout << ">  ";
        std::string s;
        std::getline(std::cin, s);
        if (s == "menu") {
            menu();
        } else if (s == "login") {
            login();
        } else if (s == "logout") {
            logout();
        } else if (s == "change pw") {
            change_password();
        } else if (s == "client") {
            add_client();
        } else if (s == "rule") {
            add_rule();
        } else if (s == "balance") {
            change_client_balance();
        } else if (s == "show clients") {
            print_clients();
        } else if (s == "show info") {
            print_info_client();
        } else if (s == "delete") {
            delete_all_rules();
        } else if (s == "exit") {
            break;
        } else {
            std::cout << "Incorrect command! Try again!" << std::endl;
        }
    }
    return;
}

void AdminInterface::login() {
    std::cout << "Enter login: ";
    std::string login;
    std::getline(std::cin, login);
    std::cout << "Enter password: ";
    std::string password;
    std::getline(std::cin, password);
    std::shared_ptr<Admin> admin = login_controller.get_admin(login, password);
    if (admin == nullptr) {
        std::cout << "Login failed. " << std::endl;
        return;
    } else {
        this->admin = admin;
        std::cout << "Login complete!!! " << std::endl;
    }
}

void AdminInterface::logout() {
    admin = nullptr;
    std::cout << "Logout complete." << std::endl;
}

void AdminInterface::change_password() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    std::cout << "Enter new password: ";
    std::string pw;
    std::getline(std::cin, pw);
    login_controller.change_password(pw, this->admin);
}

void AdminInterface::change_client_balance() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    std::cout << "Enter client's login: ";
    std::string login;
    std::getline(std::cin, login);
    std::shared_ptr<Client> client = login_controller.get_client(login);
    if (client == nullptr) {
        std::cout << "There is no such login!" << std::endl;
        return;
    }
    double n;
    while (true) {
        std::cout << "Enter new balance: ";
        std::string balance;
        std::getline(std::cin, balance);
        size_t count;
        n = stod(balance, &count);
        if (count != balance.length()) {
            std::cout << "Incorrect number! Try again! " << std::endl;
            continue;
        }
        break;
    }
    client->set_balance(n);
    login_controller.change_client(client);
    std::cout << "Balance is changed! " << std::endl;
    return;
}

void AdminInterface::print_clients() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    std::vector<std::string> list = login_controller.get_all_logins();
    int n = 0;
    for (std::string cl : list) {
        n++;
        std::cout << n << ")  " << cl << std::endl;
    }
    return;
}

void AdminInterface::print_info_client() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    std::cout << "Enter client's login: " << std::endl;
    std::string login;
    std::getline(std::cin, login);
    std::shared_ptr<Client> client = login_controller.get_client(login);
    if (client == nullptr) {
        std::cout << "There is no such login! " << std::endl;
        return;
    }
    std::cout << "Information about  '" << login << "': " << std::endl;
    std::cout << "Name: " << client->get_name() << std::endl;
    std::cout << "Account number: " << client->get_account() << std::endl;
    std::cout << "Bonus balance: "; //<< client->get_bonus_balance() << std::endl; ;
    printf("%.2lf\n", client->get_bonus_balance());
    std::cout << "Balance: ";//<< client->get_balance() << std::endl;
    printf("%.2lf\n", client->get_balance());
    return;
}

void AdminInterface::delete_all_rules() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    rule_controller.delete_rules();
    std::cout << "All rules is deleted. " << std::endl;
}

void AdminInterface::delete_rule() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }

}

void AdminInterface::print_rules() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }

}

void AdminInterface::add_client() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin!" << std::endl;
        return;
    }
    std::cout << "Enter information about new client: " << std::endl;
    std::string login, name, s_balance;
    double bonus, balance;
    int account;
    
    while (true) {
        std::cout << "Enter login of new client: ";
        std::getline(std::cin, login);
        if (login_controller.check_login(login)) {
            std::cout << "OK. This login is free." << std::endl;
            break;
        }
        std::cout << "This login isn't free. Enter other login.  " << std::endl;
    }

    std::cout << "Enter name of new client: ";
    std::getline(std::cin, name);

    account = login_controller.create_free_account();
    std::cout << "Number account: " << account << std::endl;

    bonus = 0;

    while (true) {
        std::cout << "Enter balance of new client: ";
        std::getline(std::cin, s_balance);
        size_t count;
        try {
            balance = stod(s_balance, &count);
            if (s_balance.length() != count) {
                throw std::invalid_argument("ERROR: not only digits");
            }
            break;
        } catch (std::invalid_argument) {
            std::cout << "Incorrect number. Try again!" << std::endl;
        }
    }
    std::shared_ptr<Client> new_client(new Client(login, name, account, bonus, balance));
    login_controller.add_client(new_client);
    std::cout << "New client was added." << std::endl;
}

std::vector<std::string> AdminInterface::creation_subject_predicate_two() {
    DateParser d;
    TimeParser t;
    std::vector<std::string> res;
    std::cout << "Enter what parametr you want to check: " << std::endl;
    std::cout << "Variants:     date" << std::endl;
    std::cout << "              time" << std::endl;
    std::cout << "              amount" << std::endl;
    std::cout << "              balance" << std::endl;
    std::string s1;
    while (true) {
        getline(std::cin, s1);
        if (s1 != "date" && s1 != "time" && s1 != "amount" && s1 != "balance") {
            std::cout << "Incorrect variant! Try again! " << std::endl;
        } else {
            break;
        }
    }
    std::cout << "Enter value for comparison: " << std::endl;
    std::string s2;
    while (true) {
        getline(std::cin, s2);
        if (s1 == "date") {
            try {
                d.parse(s2);
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect date! Try again!" << std::endl;
            }
        } else if (s1 == "time") {
            try {
                t.parse(s2);
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect time! Try again!" << std::endl;
            }
        } else if (s1 == "amount") {
            try {
                size_t pos;
                stod(s2, &pos);
                if (pos != s2.length()) {
                    throw std::invalid_argument("not only digits");
                }
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect number! Try again!" << std::endl;
            }
        } else if (s1 == "balance") {
            try {
                size_t pos;
                stod(s2, &pos);
                if (pos != s2.length()) {
                    throw std::invalid_argument("not only digits");
                }
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect number! Try again!" << std::endl;
            }
        } 
    }
    res.push_back(s1);
    res.push_back(s2);
    std::cout << "-----^^^^^" << std::endl;
    return res;
}

std::vector<std::string> AdminInterface::creation_subject_predicate_one() {
    DateParser d;
    TimeParser t;
    std::vector<std::string> res;
    std::cout << "Enter what parametr you want to check: " << std::endl;
    std::cout << "Variants:     date" << std::endl;
    std::cout << "              time" << std::endl;
    std::cout << "              shop" << std::endl;
    std::cout << "              amount" << std::endl;
    std::cout << "              balance" << std::endl;
    std::string s1;
    while (true) {
        getline(std::cin, s1);
        if (s1 != "date" && s1 != "time" && s1 != "shop" && s1 != "amount" && s1 != "balance") {
            std::cout << "Incorrect variant! Try again! " << std::endl;
        } else {
            break;
        }
    }
    std::cout << "Enter value for comparison: " << std::endl;
    std::string s2;
    while (true) {
        getline(std::cin, s2);
        if (s1 == "date") {
            try {
                d.parse(s2);
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect date! Try again!" << std::endl;
            }
        } else if (s1 == "time") {
            try {
                t.parse(s2);
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect time! Try again!" << std::endl;
            }
        } else if (s1 == "amount") {
            try {
                size_t pos;
                stod(s2, &pos);
                if (pos != s2.length()) {
                    throw std::invalid_argument("not only digits");
                }
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect number! Try again!" << std::endl;
            }
        } else if (s1 == "balance") {
            try {
                size_t pos;
                stod(s2, &pos);
                if (pos != s2.length()) {
                    throw std::invalid_argument("not only digits");
                }
                break;
            } catch (std::invalid_argument) {
                std::cout << "Incorrect number! Try again!" << std::endl;
            }
        } 
    }
    res.push_back(s1);
    res.push_back(s2);
    std::cout << "-----^^^^^" << std::endl;
    return res;
}

static int n = 0;

void AdminInterface::print_rule_menu() {
    std::cout << "Choose type of predicate and enter its symbol: " << std::endl;
    std::cout << "1. And             &" << std::endl;
    std::cout << "2. Or              |" << std::endl;
    std::cout << "3. Negation        !" << std::endl;
    std::cout << "4. Follow          ->" << std::endl;
    std::cout << "5. Equal           =" << std::endl;
    std::cout << "6. NotEqual        !=" << std::endl; 
    std::cout << "7. Greater         >" << std::endl;
    std::cout << "8. GreaterEqual    >=" << std::endl;
    std::cout << "9. Less            <" << std::endl;
    std::cout << "10. LessEqual       <=" << std::endl;
    std::cout << "If you want to see variants of predicate: ENTER help" << std::endl;
}

std::shared_ptr<Predicate> AdminInterface::create_predicate() {
    std::string s;
    while (true) {
        std::cout << ">  " ;
        getline(std::cin, s);
        if (s == "&") {
            std::cout << "Enter information for left predicate: " << std::endl;
            std::shared_ptr<Predicate> left = create_predicate();
            std::cout << "Enter information for right predicate: " << std::endl;
            std::shared_ptr<Predicate> right = create_predicate();
            return std::shared_ptr<Predicate>(new AndPredicate(left, right, ++n));
        } else if (s == "|") {
            std::cout << "Enter information for left predicate: " << std::endl;
            std::shared_ptr<Predicate> left = create_predicate();
            std::cout << "Enter information for right predicate: " << std::endl;
            std::shared_ptr<Predicate> right = create_predicate();
            return std::shared_ptr<Predicate>(new OrPredicate(left, right, ++n));
        } else if (s == "!") {
            std::cout << "Enter information for predicate for negation: " << std::endl;  //изменить фразу
            std::shared_ptr<Predicate> a = create_predicate();
            return std::shared_ptr<Predicate>(new NegationPredicate(a, ++n));
        } else if (s == "->") {
            std::cout << "Enter information for left predicate: " << std::endl;
            std::shared_ptr<Predicate> left = create_predicate();
            std::cout << "Enter information for right predicate: " << std::endl;
            std::shared_ptr<Predicate> right = create_predicate();
            return std::shared_ptr<Predicate>(new FollowPredicate(left, right, ++n));
        } else if (s == "=") {
            std::vector<std::string> res = creation_subject_predicate_one();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new EqualPredicate(s1, s2, ++n));
        } else if (s == "!=") {
            std::vector<std::string> res = creation_subject_predicate_one();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new NotEqualPredicate(s1, s2, ++n));
        } else if (s == ">") {
            std::vector<std::string> res = creation_subject_predicate_two();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new GreaterPredicate(s1, s2, ++n));
        } else if (s == ">=") {
            std::vector<std::string> res = creation_subject_predicate_two();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new GreaterEqualPredicate(s1, s2, ++n));
        } else if (s == "<") {
            std::vector<std::string> res = creation_subject_predicate_two();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new LessPredicate(s1, s2, ++n));
        } else if (s == "<=") {
            std::vector<std::string> res = creation_subject_predicate_two();
            std::string s1 = res[0];
            std::string s2 = res[1];
            return std::shared_ptr<Predicate>(new LessEqualPredicate(s1, s2, ++n));
        } else if (s == "help") {
            print_rule_menu();
        } else {
            std::cout << "Unknown comand! Try again!" << std::endl;
        }
    }
}

void AdminInterface::add_rule_with_commands() {
    std::cout << "Enter predicate for bonus: " << std::endl;
    print_rule_menu();
    std::shared_ptr<Predicate> p = create_predicate();
    std::cout << "Creating of preadicate is finished." << std::endl;
    std::string s_count;
    while(true) {
        std::cout << "Enter percent of bonus (real number with '.') : " << std::endl;
        getline(std::cin, s_count);
        size_t pos;
        try {
            stod(s_count, &pos);
            if (pos != s_count.length()) {
                throw std::invalid_argument("It isn't real number! ");
            }
            break;
        } catch(std::invalid_argument) {
            std::cout << "Incorrect format of real number! Try again!" << std::endl;
        }
    }
    std::shared_ptr<Rule> rule = std::shared_ptr<Rule>(new Rule(p, s_count));
    std::cout << "Rule is added." << std::endl;
    rule_controller.add_rule(rule);
}

void AdminInterface::add_rule() {
    if (admin == nullptr) {
        std::cout << "You aren't login as admin! " << std::endl;
        return;
    }
    std::cout << "ENTER 'commands' if you want to create a rule using commands" << std::endl;
    std::cout << "ENTER 'exit' if you want to cancel adding" << std::endl;
    std::cout << "or enter a rule that satisfies language: " << std::endl;
    std::string s;
    while (true) {
        std::cout << ">  ";
        getline(std::cin, s);
        if (s == "commands") {
            add_rule_with_commands();
            break;
        } else if (s == "exit") {
            break;
        } else {
            RuleParser rule_parser;
            std::shared_ptr<Rule> new_rule = rule_parser.parse(s);
            if (new_rule == nullptr) {
                std::cout << "Incorrect command. Try again." << std::endl;
                continue;
            } else {
                rule_controller.add_rule(new_rule);
                std::cout << "Rule is added. " << std::endl;
                break;
            }
        }
    }
}
