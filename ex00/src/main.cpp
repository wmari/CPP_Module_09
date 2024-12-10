#include "BitcoinExchange.hpp"

int main()
{
	// if (argc != 2)
	// 	std::cout << "Error: could not open file" << std::endl;
	
	BitcoinExchange btc;
	btc.printValue("input.txt");
	
	return (0);
}