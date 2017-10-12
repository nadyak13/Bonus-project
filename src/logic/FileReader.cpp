#include "FileReader.hpp"
#include "Client.hpp"
#include "Admin.hpp"
#include "Splitter.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include "Rule.hpp"
#include "Predicate.hpp"
#include "Itos.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <stdlib.h>

FileReader::FileReader(std::string file) : file(file) {}

std::vector<std::shared_ptr<Client>> FileReader::clients() {
    std::vector<std::shared_ptr<Client>> result;
    std::ifstream fin(file);
    Splitter splitter(',');
    std::string s;
    while (std::getline(fin, s)) {
        std::vector<std::string> splitted = splitter.split(s);
        try {
            if (splitted.size() < 5) {
                throw std::invalid_argument("Incorrect client information");
            }
            result.push_back(std::shared_ptr<Client>(new Client(splitted[0], splitted[1], std::stoi(splitted[2]), std::stod(splitted[3]), std::stod(splitted[4]))));
        } catch (std::invalid_argument) {
            std::cerr << "Error reading client information";
            continue;
        }
    }
    return result;
}


std::shared_ptr<Predicate>  FileReader::predicate(int num_root, std::vector<std::vector<std::string>> &spl_nodes) {
    size_t num_left, num_right;
    std::string logic_type;
    Itos itos;
    size_t i = 0;
    while (i < spl_nodes.size()) {
        if (spl_nodes[i][0] == itos.itos(num_root) && (spl_nodes[i][1] == "&&" || spl_nodes[i][1] == "||"  || spl_nodes[i][1] == "->")) {
            num_left = std::stoi(spl_nodes[i][2]);
            num_right = std::stoi(spl_nodes[i][3]);
            logic_type = spl_nodes[i][1];
            break;
        } else if (spl_nodes[i][0] == itos.itos(num_root) && spl_nodes[i][1] == "!") {
            num_right = std::stoi(spl_nodes[i][2]);
            logic_type = spl_nodes[i][1];
            break;
        } else if (spl_nodes[i][0] == itos.itos(num_root)) {
            if (spl_nodes[i][1] == "==") {
                return std::shared_ptr<Predicate>(new EqualPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
            if (spl_nodes[i][1] == "!=") {
                return std::shared_ptr<Predicate>(new NotEqualPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
            if (spl_nodes[i][1] == ">") {
                return std::shared_ptr<Predicate>(new GreaterPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
            if (spl_nodes[i][1] == ">=") {
                return std::shared_ptr<Predicate>(new GreaterEqualPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
            if (spl_nodes[i][1] == "<=") {
                return std::shared_ptr<Predicate>(new LessEqualPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
            if (spl_nodes[i][1] == "<") {
                return std::shared_ptr<Predicate>(new LessPredicate(spl_nodes[i][2], spl_nodes[i][3], std::stoi(spl_nodes[i][0])));
            }
        }
        i++;
    }
    std::shared_ptr<Predicate> p1;
    if (logic_type != "!") {
        p1 = predicate(num_left, spl_nodes);
    }
    std::shared_ptr<Predicate> p2 = predicate(num_right, spl_nodes);
    if (logic_type == "&&") {
        return std::shared_ptr<Predicate>(new AndPredicate(p1, p2, num_root));
    } 
    if (logic_type == "||") {
        return std::shared_ptr<Predicate>(new OrPredicate(p1, p2, num_root));
    }
    if (logic_type == "!") {
        return std::shared_ptr<Predicate>(new NegationPredicate(p2, num_root));
    }
    if (logic_type == "->") {
        return std::shared_ptr<Predicate>(new FollowPredicate(p1, p2, num_root));
    }
    return nullptr;
}


std::vector<std::shared_ptr<Rule>> FileReader::rules() {
    std::string line;
    std::ifstream fin(file);
    std::vector<std::vector<std::string>> spl_nodes;
    std::vector<std::shared_ptr<Rule>> result;
    while (std::getline(fin, line)) {
        spl_nodes.erase(spl_nodes.begin(), spl_nodes.end());
        std::vector<std::string> nodes;
        std::string s;
        while (std::getline(fin, s) && s[0] != 'b') {
            nodes.push_back(s);
        }
        Splitter splitter(' ');
        std::vector<std::string> s_bonus = splitter.split(s);
        size_t pos;
        std::stod(s_bonus[1], &pos);
        Splitter splr(',');
        for (std::string s : nodes) {
            std::vector<std::string> tmp = splr.split(s);
            spl_nodes.push_back(tmp);
        }
        int count = spl_nodes.size();
        size_t num_root;
        Itos itos;
        int i = 0;
        int j = 0;
        while (i < count) {
            j = 0;
            bool flag = false;
            while (j < count) {
                if (spl_nodes[j][2] == itos.itos(i + 1) || spl_nodes[j][3] == itos.itos(i + 1)) {
                    flag = true;
                    break;
                }      
                j++;        
            }
            if (!flag) {
                num_root = i + 1;
                break;
            } 
            i++;
        }
        std::shared_ptr<Predicate> p = predicate(num_root, spl_nodes);
        result.push_back(std::shared_ptr<Rule>(new Rule(p, s_bonus[1])));
    }
    return result;
}

std::shared_ptr<Admin> FileReader::admin() {
    std::ifstream fin(file);
    std::string log, pw;
    try {
        if (!(std::getline(fin, log))) {
            throw std::invalid_argument("Incorrect admin information");
        }
        if (!(std::getline(fin, pw))) {
            throw std::invalid_argument("Incorrect admin information");
        }
        return std::shared_ptr<Admin>(new Admin(log, pw));
    } catch (std::invalid_argument) {
        std::cerr << "Error reading admin information";
        return nullptr;
    }
}
