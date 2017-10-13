#include "PaymentController.hpp"
#include "Client.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include <iostream>

PaymentController::PaymentController(std::string file1, std::string file2) :
        reader(std::shared_ptr<FileReader>(new FileReader(file1))),
        writer(std::shared_ptr<FileWriter>(new FileWriter(file1))),
        bonusCtrl(BonusController(file2)) {}

double PaymentController::make_payment(
        Date date,
        Time time,
        std::shared_ptr<Client> client,
        const std::string shop,
        double amount) {
    std::shared_ptr<Payment> pay(new Payment(date, time, client, shop, amount));
    if (client->get_balance() >= amount) {
        std::vector<std::shared_ptr<Client>> clients = reader->clients();
        client->set_balance(client->get_balance() - amount);
        double bonus = bonusCtrl.get_bonus(pay, client);
        client->set_bonus_balance(client->get_bonus_balance() + bonus);
        writer->client_change(client);
        return bonus; 
    } else {
        //std::cout << "balance " <<client->get_balance() << "  amount" << amount << std::endl;
        throw std::invalid_argument("No money");
    }
}
