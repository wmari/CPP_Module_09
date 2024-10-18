#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(BitcoinExchange & copy)
{
	if (this != &copy)
		_db = copy._db;
	return ;
}

BitcoinExchange::BitcoinExchange(std::string input)
{
	std::ifstream inputFile(input);
	if (!inputFile)
	{
		std::cout << "Error: could not open file " << input << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::string date;
		float value;

		std::stringstream ss(line);
		std::getline(ss, date, ',');
		ss >> value;

		_db[Date(date)] = value;
	}
	return ;
}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange & copy)
{
	if (this != &copy)
	{
		_db = copy._db;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::printValue(std::string input)
{
	unsigned int year, month, day;
	char del1, del2, del3, del4;
	float value;
	std::stringstream ss(input);
	if (ss >> year >> del1 >> month >> del2 >> day >> del4 >> value)
	{
		if (!(del1 == del2 && del1 == del3) || !(del4 == '|') || !isValidDate(year, month, day))
		{
			if (!(del1 == del2 && del1 == del3) || !(del4 == '|'))
				std::cout << "Error: invalid line" << std::endl;
			else
				std::cout << "Error: bad input => " << year << "-" << month << "-" << day << std::endl;
		}
		else if (value < 0)
			std::cout << "Error: not a positive number." << std::endl;
		else if (value > 1000)
			std::cout << "Error: too large a number." << std::endl;
		else if (BitcoinExchange::getValue(year, month, day) == -1)
			std::cout << "Error: no date matching" << std::endl;
		else
			std::cout << year << "-" << month << "-" << day << " => " << value << " = " << value * this->getValue(year, month, day) << std::endl;
	}
	else
		std::cout << "Error: invalid line" << std::endl;
}

bool isLeapYear(unsigned int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int	daysInMonth(unsigned int year,unsigned int month)
{
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			return 31;
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return isLeapYear(year) ? 29 : 28;
		default:
			return 0;
	}
}

bool BitcoinExchange::isValidDate(unsigned int year, unsigned int month, unsigned int day)
{
	if (month <= 12 && month >= 1)
	{
		int maxday = daysInMonth(year, month);
		if (day >= 1 && day <= maxday)
			return true;
	}
	return false;
}

float BitcoinExchange::getValue(unsigned int year, unsigned int month, unsigned int day)
{
	
}