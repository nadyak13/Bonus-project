#include <string>
#include <memory>

class Predicate;

class Rule {
public:
    Rule(std::shared_ptr<Predicate>, std::string);
    std::shared_ptr<Predicate> get_predicate() const;
    std::string get_count() const;
private:
    std::shared_ptr<Predicate> p;
    std::string count;
};
