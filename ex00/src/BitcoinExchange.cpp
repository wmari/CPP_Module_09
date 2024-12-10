#include "BitcoinExchange.hpp"

bool isLeapYear(unsigned int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

unsigned int	daysInMonth(unsigned int year,unsigned int month)
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

bool isValidDate(std::string date)
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
	char del1, del2;

	std::stringstream ss;
	ss << date;
	ss >> year >> del1 >> month >> del2 >> day;
	if (month <= 12 && month >= 1)
	{
		unsigned int maxday = daysInMonth(year, month);
		if (day >= 1 && day <= maxday)
			return true;
	}
	return false;
}

BitcoinExchange::BitcoinExchange()
{
	std::ifstream inputFile("./data.csv");
	if (!inputFile)
	{
		std::cout << "Error: could not open file " << "data.csv" << std::endl;
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

		_db[date] = value;
	}
	return ;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange & copy)
{
	if (this != &copy)
		_db = copy._db;
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

std::string BitcoinExchange::findClosest(std::string date)
{
	auto low = _db.lower_bound(date);
}

void BitcoinExchange::printValue(std::string input)
{
	std::ifstream inputFile;
	inputFile.open(input.c_str());
	if (!inputFile.is_open())
	{
		std::cout << "Error: could not open file " << input << std::endl;
		return ;
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (line.find('|') == std::string::npos)
			std::cout << "date non valide" << std::endl;
		else
		{
			unsigned int year;
			unsigned int month;
			unsigned int day;
			char del1, del2;
		
			std::string date = line.substr(0,line.find('|'));
			std::stringstream ss;
			ss << date;
			ss >> year >> del1 >> month >> del2 >> day;
			std::cout << "year:" << year << "|month:" << month << "|day:" << day << std::endl;

			std::string charvalue = line.substr(line.find('|') + 1);
			std::stringstream dd;
			dd << charvalue;
			float value;
			dd >> value;
			std::cout << "value:" << value << std::endl;
			if (!isValidDate(date))
				std::cout << "date non valide" << std::endl;
			else if (value < 0 || value > 1000)
				std::cout << "valeur non valide" << std::endl;
			else
			{
				std::string closestdate = findClosest(date);
				std::cout << date << "=> " << value << " = " << value * _db[closestdate];
			}
		}
	}
}