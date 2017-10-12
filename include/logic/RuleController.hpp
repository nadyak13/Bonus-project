#include <string>
#include <memory>
#include <iostream>
#include <vector>

class FileReader;
class FileWriter;
class Rule;

class RuleController {
public:
    RuleController(std::string file = "rules.txt");
    void add_rule(std::shared_ptr<Rule>);
    std::vector<std::shared_ptr<Rule>> get_rules();
    void delete_rules();

private:
    std::shared_ptr<FileWriter> writer_rule;
    std::shared_ptr<FileReader> reader_rule;
};