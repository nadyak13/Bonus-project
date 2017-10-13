#include <string>
#include <memory>
#include <vector>

//class Payment; //???
class Client;
class Admin;
class Shop;
class Rule;
class Predicate;

class FileReader {
	std::string file;
public:
	FileReader(std::string file);
	//std::vector<std::shared_ptr<Payment
	std::vector<std::shared_ptr<Client>> clients();
	std::shared_ptr<Admin> admin();
	std::shared_ptr<Predicate> predicate(int, std::vector<std::vector<std::string>> &);
	std::vector<std::shared_ptr<Rule>> rules();

	//std::vector<std::shared_ptr<Shop>> shops();  //описать в cpp
	
};