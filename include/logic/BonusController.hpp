#include <string>
#include <memory>

class Date;
class Time;
class Shop;
class Client;
class Payment;
class RuleController;


class BonusController{
public:
    BonusController(std::string file = "rules.txt");
    double get_bonus(std::shared_ptr<Payment>, std::shared_ptr<Client>);
private:
	std::shared_ptr<RuleController> ruleCntrl;
};