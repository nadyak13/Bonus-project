#include "RuleController.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "DateParser.hpp"
#include "TimeParser.hpp"
#include "Date.hpp"
#include "Time.hpp"
#include <stdexcept>

RuleController::RuleController(std::string file) :
        writer_rule(std::shared_ptr<FileWriter>(new FileWriter(file))),
        reader_rule(std::shared_ptr<FileReader>(new FileReader(file))) {}

void RuleController::add_rule(std::shared_ptr<Rule> new_rule) {
    writer_rule->rule_add(new_rule);
}

std::vector<std::shared_ptr<Rule>> RuleController::get_rules() {
	std::vector<std::shared_ptr<Rule>> rules = reader_rule->rules();
	return rules;
}

void RuleController::delete_rules() {
	writer_rule->delete_rules();
}
