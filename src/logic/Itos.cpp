#include "Itos.hpp"

std::string Itos::itos(int number) {
	std::string s;
	while (number != 0) {
		int temp = number % 10;
		s += temp + '0';
		number = number / 10;
	}
	std::reverse(s.begin(), s.end());
	return s;
}

