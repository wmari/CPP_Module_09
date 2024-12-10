#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _db;
		unsigned int _year;
		unsigned int _month;
		unsigned int _day;

		std::string findClosest(std::string input);
	
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &copy);

		BitcoinExchange &operator=(BitcoinExchange & copy);	
	
		~BitcoinExchange();
		
		void	printValue(std::string date);

};

bool isLeapYear(unsigned int year);
unsigned int	daysInMonth(unsigned int year,unsigned int month);
bool isValidDate(unsigned int year, unsigned int month, unsigned int day);

#endif