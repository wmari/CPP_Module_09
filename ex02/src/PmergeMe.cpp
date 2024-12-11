#include "PmergeMe.hpp"

bool validstring(char *str)
{
	if (str[0] == '-')
		return false;
	int i = 0;
	while(std::isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return false;	
	long num = std::strtol(str, NULL, 0);
	if (num == 0 && str[0] != '0')
		return false;
	if (num > INT_MAX || errno == ERANGE)
		return false;
	return true;
}

bool validInput(int ac, char **av)
{
	if (ac < 2)
		return false;
	for (int i = 1; i < ac; i++)
	{
		if (!validstring(av[i]))
			return false;
		std::string str = av[i];
		for (int j = 1; j < i; j++)
		{
			if (!str.compare(av[j]))
				return false;
		}
	}
	return true;
}

std::deque<int> argv_to_deque(int ac, char **argv)
{
	std::deque<int> res;
	for (int i = 1; i < ac; i++)
		res.push_back(std::atoi(argv[i]));
	return res;
}

std::vector<int> argv_to_vector(int ac, char **argv)
{
	std::vector<int> res;
	for (int i = 1; i < ac; i++)
		res.push_back(std::atoi(argv[i]));
	return res;
}