#include <string>
#include <memory>
#include <vector> //??????

class Client;
class Admin;
class Shop;
class FileReader;
class Rule;
class Predicate;

class FileWriter {
public:
    FileWriter(std::string file);
    void client_change(std::shared_ptr<Client>);
    void client_add(std::shared_ptr<Client>);
    void shop_add(std::shared_ptr<Shop>);
    void admin(std::shared_ptr<Admin>);
    void rule_add(std::shared_ptr<Rule>);
    void write_predicate(std::shared_ptr<Predicate>);
    void delete_rules();
private:
    std::string file;
    std::shared_ptr<FileReader> reader;
};
