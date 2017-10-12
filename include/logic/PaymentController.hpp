#include "Payment.hpp"
#include <memory>
#include <string>
#include "BonusController.hpp"

class Date;
class Time;
class Client;
class FileReader;
class FileWriter;


class PaymentController {
public:
    PaymentController(std::string file1 = "clients.txt", std::string file2 = "rules.txt");
    double make_payment(Date, Time, std::shared_ptr<Client>, std::string, double);

private:
    std::shared_ptr<FileReader> reader;
    std::shared_ptr<FileWriter> writer;
    BonusController bonusCtrl;
};