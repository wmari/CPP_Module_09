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

bool isValidDate(unsigned int year, unsigned int month, unsigned int day)
{
	if (month <= 12 && month >= 1)
	{
		unsigned int maxday = daysInMonth(year, month);
		if (day >= 1 && day <= maxday)
			return true;
	}
	return false;
}

bool isValidLineDB(std::string line)
{
	if (line.find(',') == std::string::npos)
		return false;
	std::string datePart = line.substr(0, line.find(','));
	std::string valuePart = line.substr(line.find(',') + 1);
	std::string::const_iterator it = valuePart.begin();
	if (valuePart.empty())
		return false;
	int nbPoint = 0;
	while (it != valuePart.end())
	{
		if (*it == '.')
			nbPoint++;
		if ((!std::isdigit(*it) && *it != '.')|| nbPoint > 1)
			return false;
		it++;
	}
	if (datePart.length() != 10)
		return false;
	if (datePart[4] != '-' || datePart[7] != '-')
		return false;
	
	for (size_t i = 0; i < datePart.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(datePart[i]))
			return false;
	}
	return true;
}

bool isValidLineInput(std::string line)
{
	if (line.find(" | ") == std::string::npos)
		return false;
	std::string datePart = line.substr(0, line.find(" | "));
	std::string valuePart = line.substr(line.find(" | ") + 3);

	std::string::const_iterator it = valuePart.begin();
	if (valuePart.empty())
		return false;
	int nbPoint = 0;
	while (it != valuePart.end())
	{
		if (*it == '.' && it == valuePart.begin())
			return false;
		if (*it == '.' && it != valuePart.begin())
			nbPoint++;
		if (*it == '-' && it != valuePart.begin())
			return false;
		else if (*it == '-')
		{
			it++;
			continue;
		}
		if ((!std::isdigit(*it) && *it != '.')|| nbPoint > 1)
			return false;
		it++;
	}

	if (datePart.length() != 10)
		return false;
	if (datePart[4] != '-' || datePart[7] != '-')
		return false;
	
	for (size_t i = 0; i < datePart.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(datePart[i]))
			return false;
	}
	return true;
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
		if (!isValidLineDB(line))
			continue;
		unsigned int date;
		float value;
		std::stringstream ss(line);
		unsigned int year;
		unsigned int month;
		unsigned int day;
		char del1, del2, del3;

		ss >> year >> del1 >> month >> del2 >> day >> del3 >> value;
		date = (year * 10000) + (month * 100) + day;
		if (isValidDate(year, month, day))
			_db[date] = value;
	}
	inputFile.close();
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

unsigned int BitcoinExchange::findClosest(unsigned int date)
{
	if (this->_db.empty())
		std::cout << "Error: database is empty" << std::endl;
	else
	{
		std::map<unsigned int, float>::const_iterator lower = this->_db.lower_bound(date);
		if (lower == this->_db.begin() && lower->first > date)
			throw std::invalid_argument("Error: no matching date in database");
		if (lower == this->_db.begin())
			return lower->first;
		if (lower == this->_db.end())
			return this->_db.rbegin()->first;
		if (lower->first > date)
		{
			std::map<unsigned int, float>::iterator temp, truelow;
			temp = this->_db.begin();
			while (temp != lower)
			{
				truelow = temp;
				temp++;
			}
			return truelow->first;
		}
		else
			return lower->first;
	}
	return (0);
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
	int i = 0;
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (i == 0)
		{
			i = 1;
			continue;
		}
		try 
		{
			if (!isValidLineInput(line))
				throw std::invalid_argument("Error: bad input => " + line);
			else
			{
				unsigned int date;
				float value;
				std::stringstream ss(line);
				std::string strdate = line.substr(0,line.find('|'));
				unsigned int year;
				unsigned int month;
				unsigned int day;
				char del1, del2, del3;

				ss >> year >> del1 >> month >> del2 >> day >> del3 >> value;
				date = (year * 10000) + (month * 100) + day;
				if (!isValidDate(year, month, day))
					throw std::invalid_argument("Error: date invalide => " + strdate);
				else if (value > 1000)
					throw TooLargeNumberException();
				else if (value < 0)
					throw NotPositiveNumberException();
				else
				{
					unsigned int closestdate = findClosest(date);
					std::cout << strdate << "=> " << value << " = " << value * _db[closestdate] << std::endl;
				}
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	inputFile.close();
}

bool BitcoinExchange::dbEmpty()
{
	return (this->_db.empty());
}