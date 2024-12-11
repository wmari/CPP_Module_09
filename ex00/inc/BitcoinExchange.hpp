#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<unsigned int, float> _db;

		unsigned int findClosest(unsigned int input);
	
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange &copy);

		BitcoinExchange &operator=(BitcoinExchange & copy);	
	
		~BitcoinExchange();
		
		void	printValue(std::string date);

		class NotPositiveNumberException : public std::exception
		{
			public :
				virtual const char *what() const throw()
				{
					return ("Error: not a positive number.");
				}
		};

		class TooLargeNumberException : public std::exception
		{
			public :
				virtual const char *what() const throw()
				{
					return ("Error: too large a number.");
				}
		};

};

bool isLeapYear(unsigned int year);
unsigned int	daysInMonth(unsigned int year,unsigned int month);
bool isValidDate(unsigned int year, unsigned int month, unsigned int day);

#endif