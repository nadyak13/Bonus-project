#include "BonusController.hpp"
#include "RuleController.hpp"
#include "Payment.hpp"
#include "Rule.hpp"
#include "GetResultVisitor.hpp"
#include <vector>
#include <iostream>

BonusController::BonusController(std::string file) : ruleCntrl(std::shared_ptr<RuleController>(new RuleController(file))) {}

double BonusController::get_bonus(std::shared_ptr<Payment> pay, std::shared_ptr<Client> client) {
    std::vector<std::shared_ptr<Rule>> rules = ruleCntrl->get_rules();
    std::vector<double> possible_bonuses;
    for (std::shared_ptr<Rule> rule : rules) {
        GetResultVisitor resv;
        bool result = resv.evaluate(*rule->get_predicate(), pay, client);
        if (result) {
            possible_bonuses.push_back(stod(rule->get_count()));
        }
    }
    double max_bonus = 0;
    for (double bonus : possible_bonuses) {
        if (bonus > max_bonus) {
            max_bonus = bonus;
        }
    }
    return max_bonus * pay->get_amount() * 0.01;
}
