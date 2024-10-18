#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Date
{
	private:
		unsigned int	_year;
		unsigned int	_month;
		unsigned int	_day;

	public:
		Date();
		Date(std::string input);
		Date(const Date &copy);

		Date &operator=(Date & copy);
		
		~Date();
};

class BitcoinExchange
{
	private:
		std::map<Date, float> _db;

		float	getValue(unsigned int year, unsigned int month, unsigned int day);
		bool	isValidDate(unsigned int year, unsigned int month, unsigned int day);
	
	public:
		BitcoinExchange();
		BitcoinExchange(std::string input);
		BitcoinExchange(BitcoinExchange &copy);

		BitcoinExchange &operator=(BitcoinExchange & copy);	
	
		~BitcoinExchange();
		
		void	printValue(std::string date);

};

#endif