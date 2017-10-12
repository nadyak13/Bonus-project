#include "FileWriter.hpp"
#include "Client.hpp"
#include "Admin.hpp"
#include "Rule.hpp"
#include "Predicate.hpp"
#include "GetTypeVisitor.hpp"
#include "GetResultVisitor.hpp"
#include "Splitter.hpp"
#include <iostream>
#include <fstream>
#include "FileReader.hpp"
#include <string>


FileWriter::FileWriter(std::string file) : file(file), reader(std::shared_ptr<FileReader>(new FileReader(file))) {}

void FileWriter::admin(std::shared_ptr<Admin> admin) {
    std::ofstream fout(file);
    fout << admin->get_login() << std::endl;
    fout << admin->get_password() << std::endl;
}

void FileWriter::client_change(std::shared_ptr<Client> new_client) {
    std::vector<std::shared_ptr<Client>> old = reader->clients();
    for (std::shared_ptr<Client> client : old) {
        if (client->get_login() == new_client->get_login()) {
            client->set_balance(new_client->get_balance());
            client->set_bonus_balance(new_client->get_bonus_balance());
            break;
        }
    }
    std::ofstream fout(file);
    for (std::shared_ptr<Client> client : old) {
        fout << client->get_login() << "," << client->get_name() << ",";
        fout << client->get_account() << "," << client->get_bonus_balance();
        fout << "," << client->get_balance() << std::endl;
    }
}

void FileWriter::client_add(std::shared_ptr<Client> new_client) {    
    std::ofstream fout;
    fout.open(file, std::fstream::app); //end record
    fout << new_client->get_login() << "," << new_client->get_name() << ",";
    fout << new_client->get_account() <<"," << new_client->get_bonus_balance();
    fout << "," << new_client->get_balance() << std::endl;   
}

void FileWriter::rule_add(std::shared_ptr<Rule> new_rule) {
    std::ofstream fout;
    fout.open(file, std::fstream::app);
    fout << "Bonus rule: " << std::endl;
    FileWriter::write_predicate(new_rule->get_predicate());
    fout << "bonus " << new_rule->get_count() << std::endl;
}

void FileWriter::write_predicate(std::shared_ptr<Predicate> p) {
    std::ofstream fout;
    GetTypeVisitor typev;
    p->accept(typev);
    fout.open(file, std::fstream::app);
    if (typev.type == "&&" || typev.type == "||" || typev.type == "->") {
        write_predicate(p->get_left());
    } 
    fout << p->get_number() << "," << typev.type << ",";
    if (typev.type == "&&" || typev.type == "||" || typev.type == "->") {
        fout << p->get_left()->get_number() << "," << p->get_right()->get_number() << std::endl;
    } else if (typev.type == "!") {
        fout << p->get_right()->get_number() << ",0" << std::endl;
    } else {
        fout << p->get_what() << "," << p->get_value() << std::endl;
    }
    if (typev.type == "&&" || typev.type == "||" || typev.type == "!" || typev.type == "->") {
        write_predicate(p->get_right());
    } 
}

void FileWriter::delete_rules() {
    std::ofstream fout(file);
}