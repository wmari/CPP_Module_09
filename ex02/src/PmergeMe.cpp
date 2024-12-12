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

std::vector<std::vector<int> > making_pairs_vect(std::vector<int> vector, size_t taille)
{
	std::vector<std::vector<int> > workplace;
	std::vector<int>::iterator it = vector.begin();
	size_t i = 0;
	std::vector<int> temp;
	while (it != vector.end())
	{
		if (i < taille)
		{
			temp.push_back(*it);
			i++;
		}
		if (i == taille)
		{
			workplace.push_back(temp);
			i = 0;
			temp.clear();
		}
		it++;
	}
	if (!temp.empty())
	{
		workplace.push_back(temp);
		temp.clear();
	}
	return workplace;
}

std::vector<std::vector<int> > shuffle_workplace(std::vector<std::vector<int> > workplace, size_t taille)
{
	std::vector<std::vector<int> >::iterator it = workplace.begin();
	while (it != workplace.end())
	{
		if (it->size() != taille)
		{
			it++;
			continue;
		}
		if (it->at((it->size() - 1)/ 2) > it->at(it->size() - 1))
		{
			size_t mid = it->size() / 2;
			std::rotate(it->begin(), it->begin() + mid, it->end());
		}
		it++;
	}
	return workplace;
}

std::vector<std::vector<int> >getting_pend_vect(std::vector<std::vector<int> > work, size_t taille)
{
	std::vector<std::vector<int> >pend;
	std::vector<std::vector<int> >::iterator it = work.begin();
	int i = 0;
	while (it != work.end())
	{
		if (i < 2 || i % 2 == 1)
		{
			i++;
			it++;
			continue;
		}
		if (it->size() == taille)
			pend.push_back(*it);
		i++;
		it++;
	}
	return (pend);
}

std::vector<std::vector<int> >delete_work_vect(std::vector<std::vector<int> > work)
{
	std::vector<std::vector<int> >newvec;
	std::vector<std::vector<int> >::iterator it = work.begin();
	int i = 0;
	while (it != work.end())
	{
		if (i < 2 || i % 2 == 1)
		{
			newvec.push_back(*it);
		}
		i++;
		it++;
	}
	return (newvec);

}

std::vector<int> insert_vect(std::vector<int> vec, size_t taille)
{
	std::vector<std::vector<int> > work = making_pairs_vect(vec, taille);
	std::vector<std::vector<int> > pend = getting_pend_vect(work, taille);
	work = delete_work_vect(work);
	std::vector<int> leftover;
	leftover = *work.rbegin();

	// std::cout << "jacobsthal = " << (std::pow(2, nbrec + 1) + std::pow(-1, nbrec)) / 3 << std::endl;

	
	
	std::vector<int>::iterator it4 = vec.begin();
	std::cout << "vec =";
	while (it4 != vec.end())
	{
		std::cout << *it4 << " ";
		it4++;
	}
	std::cout << std::endl;
	std::vector<std::vector<int> >::iterator it2 = work.begin();
	std::cout << "work:" << std::endl;
	while (it2 != work.end())
	{
		std::vector<int>::iterator it3 = it2->begin();
		while (it3 != it2->end())
		{
			std::cout << *it3 << " ";
			it3++;
		}
		std::cout << std::endl;
		it2++;
	}
	it2 = pend.begin();
	std::cout << "pend:" << std::endl;
	while (it2 != pend.end())
	{
		std::vector<int>::iterator it3 = it2->begin();
		while (it3 != it2->end())
		{
			std::cout << *it3 << " ";
			it3++;
		}
		std::cout << std::endl;
		it2++;
	}
	return vec;
}

std::vector<int> sort_vect(std::vector<int> vector, size_t nbrec)
{
	size_t taille = std::pow(2, nbrec);
	std::vector<std::vector<int> > workplace = making_pairs_vect(vector, taille);
	workplace = shuffle_workplace(workplace, taille);
	vector.clear();
	for (size_t i = 0; i < workplace.size(); i++)
	{
		for (size_t j = 0; j < workplace[i].size(); j++)
			vector.push_back(workplace[i][j]);
	}
	
	// std::vector<int>::iterator it = vector.begin();
	// while (it != vector.end())
	// {
	// 	std::cout << *it << " ";
	// 	it++;
	// }
	// std::cout << std::endl;
	if (2 * taille < vector.size())
	{
		vector = sort_vect(vector, nbrec + 1);
	}
	std::cout << "rising nbrec=" << nbrec << std::endl;
	vector = insert_vect(vector, taille);
	return vector;
}