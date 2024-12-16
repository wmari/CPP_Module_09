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


// ALGORITHME WITH STD::VECTOR

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

std::vector<std::vector<int> > shuffle_workplace_vect(std::vector<std::vector<int> > workplace, size_t taille)
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

std::vector<std::vector<int> >delete_work_vect(std::vector<std::vector<int> > work, size_t taille)
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
	if (work.rbegin()->size() < taille && ((i - 1) % 2 != 1))
		newvec.push_back(*work.rbegin());
	return (newvec);
}

bool compare_vect(std::vector<int>lit, std::vector<int>rit)
{
	return (*lit.rbegin() < *rit.rbegin());
}

std::vector<std::vector<int> >insert_pend_to_work(std::vector<std::vector<int> >work, std::vector<std::vector<int> >pend, bool isodd)
{
	if (pend.empty())
		return work;
	std::vector<int> oddone;
	if (isodd)
	{
		oddone = pend.back();
		pend.pop_back();
	}

	// Insert in Jacobsthal order when possible
	size_t pre_jacobsthal = (std::pow(2, 2) + std::pow(-1, 1)) / 3;
	size_t inserted = 0;
	for (int k = 2;; k++)
	{
		size_t current_jacob = (std::pow(2, k + 1) + std::pow(-1, k))/ 3;
		size_t jacob_diff = current_jacob - pre_jacobsthal;
		int offset = 0;
		if (jacob_diff > pend.size())
			break;
		int nbr_time = jacob_diff;
		std::vector<std::vector<int> >::iterator pend_it = pend.begin() + (jacob_diff - 1);
		std::vector<std::vector<int> >::iterator upbound_it = work.begin() + current_jacob + inserted;
		while (nbr_time)
		{
			std::vector<std::vector<int> >::iterator place_it;
			place_it = std::upper_bound(work.begin(), upbound_it, *pend_it, compare_vect);
			std::vector<std::vector<int> >::iterator placed = work.insert(place_it, *pend_it);
			nbr_time--;
			pend_it = pend.erase(pend_it);
			std::advance(pend_it, -1);
			std::vector<std::vector<int> >::iterator nb_it = work.begin();
			size_t nb = 0;
			while (nb_it != placed)
			{
				nb++;
				nb_it++;
			}
			if (nb == current_jacob + inserted)
				offset++;
			upbound_it = work.begin() + (current_jacob + inserted - offset);
		}
		pre_jacobsthal = current_jacob;
		inserted += jacob_diff;
		offset = 0;
	}

	// When not enough member to do in Jacobsthal order
	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector<std::vector<int> >::iterator this_pend_it = pend.begin() + i;
		std::vector<std::vector<int> >::iterator this_bound_it = work.begin() + (work.size() - pend.size() + i);
		std::vector<std::vector<int> >::iterator place_it;
		place_it = std::upper_bound(work.begin(), this_bound_it, *this_pend_it, compare_vect);
		work.insert(place_it, *this_pend_it);
	}

	// insert the odd one
	if (isodd)
		work.insert(std::upper_bound(work.begin(), work.end(), oddone, compare_vect), oddone);

	return work;
	
}

std::vector<int> insert_vect(std::vector<int> vec, size_t taille)
{

	bool isodd = (vec.size() / taille) % 2;
	std::vector<std::vector<int> > work = making_pairs_vect(vec, taille);
	std::vector<std::vector<int> > pend = getting_pend_vect(work, taille);
	work = delete_work_vect(work, taille);
	std::vector<int> leftover;
	if (work.rbegin()->size() != taille)
	{
		leftover = work.back();
		work.pop_back();
	}
	work = insert_pend_to_work(work, pend, isodd);
	work.push_back(leftover);
	vec.clear();
	for (size_t i = 0; i < work.size(); i++)
	{
		for (size_t j = 0; j < work[i].size(); j++)
			vec.push_back(work[i][j]);
	}
	return vec;
}

std::vector<int> sort_vect(std::vector<int> vector, size_t nbrec)
{
	std::vector<int>::iterator it;
	size_t taille = std::pow(2, nbrec);
	std::vector<std::vector<int> > workplace = making_pairs_vect(vector, taille);
	workplace = shuffle_workplace_vect(workplace, taille);
	vector.clear();
	for (size_t i = 0; i < workplace.size(); i++)
	{
		for (size_t j = 0; j < workplace[i].size(); j++)
			vector.push_back(workplace[i][j]);
	}
	if (2 * taille < vector.size())
		vector = sort_vect(vector, nbrec + 1);	
	
	vector = insert_vect(vector, taille);
	if (nbrec == 1)
		vector = insert_vect(vector, 1);
	
	return vector;
}



// ALGORITHME WITH STD::DEQUE

std::deque<std::deque<int> > making_pairs_dequ(std::deque<int> deque, size_t taille)
{
	std::deque<std::deque<int> > workplace;
	std::deque<int>::iterator it = deque.begin();
	size_t i = 0;
	std::deque<int> temp;
	while (it != deque.end())
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

std::deque<std::deque<int> > shuffle_workplace_dequ(std::deque<std::deque<int> > workplace, size_t taille)
{
	std::deque<std::deque<int> >::iterator it = workplace.begin();
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

std::deque<std::deque<int> >getting_pend_dequ(std::deque<std::deque<int> > work, size_t taille)
{
	std::deque<std::deque<int> >pend;
	std::deque<std::deque<int> >::iterator it = work.begin();
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

std::deque<std::deque<int> >delete_work_dequ(std::deque<std::deque<int> > work, size_t taille)
{
	std::deque<std::deque<int> >newvec;
	std::deque<std::deque<int> >::iterator it = work.begin();
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
	if (work.rbegin()->size() < taille && ((i - 1) % 2 != 1))
		newvec.push_back(*work.rbegin());
	return (newvec);
}

bool compare_dequ(std::deque<int>lit, std::deque<int>rit)
{
	return (*lit.rbegin() < *rit.rbegin());
}

std::deque<std::deque<int> >insert_pend_to_work(std::deque<std::deque<int> >work, std::deque<std::deque<int> >pend, bool isodd)
{
	if (pend.empty())
		return work;
	std::deque<int> oddone;
	if (isodd)
	{
		oddone = pend.back();
		pend.pop_back();
	}

	// Insert in Jacobsthal order when possible
	size_t pre_jacobsthal = (std::pow(2, 2) + std::pow(-1, 1)) / 3;
	size_t inserted = 0;
	for (int k = 2;; k++)
	{
		size_t current_jacob = (std::pow(2, k + 1) + std::pow(-1, k))/ 3;
		size_t jacob_diff = current_jacob - pre_jacobsthal;
		int offset = 0;
		if (jacob_diff > pend.size())
			break;
		int nbr_time = jacob_diff;
		std::deque<std::deque<int> >::iterator pend_it = pend.begin() + (jacob_diff - 1);
		std::deque<std::deque<int> >::iterator upbound_it = work.begin() + current_jacob + inserted;
		while (nbr_time)
		{
			std::deque<std::deque<int> >::iterator place_it;
			place_it = std::upper_bound(work.begin(), upbound_it, *pend_it, compare_dequ);
			std::deque<std::deque<int> >::iterator placed = work.insert(place_it, *pend_it);
			nbr_time--;
			pend_it = pend.erase(pend_it);
			std::advance(pend_it, -1);
			std::deque<std::deque<int> >::iterator nb_it = work.begin();
			size_t nb = 0;
			while (nb_it != placed)
			{
				nb++;
				nb_it++;
			}
			if (nb == current_jacob + inserted)
				offset++;
			upbound_it = work.begin() + (current_jacob + inserted - offset);
		}
		pre_jacobsthal = current_jacob;
		inserted += jacob_diff;
		offset = 0;
	}

	// When not enough member to do in Jacobsthal order
	for (size_t i = 0; i < pend.size(); i++)
	{
		std::deque<std::deque<int> >::iterator this_pend_it = pend.begin() + i;
		std::deque<std::deque<int> >::iterator this_bound_it = work.begin() + (work.size() - pend.size() + i);
		std::deque<std::deque<int> >::iterator place_it;
		place_it = std::upper_bound(work.begin(), this_bound_it, *this_pend_it, compare_dequ);
		work.insert(place_it, *this_pend_it);
	}

	// insert the odd one
	if (isodd)
		work.insert(std::upper_bound(work.begin(), work.end(), oddone, compare_dequ), oddone);

	return work;
	
}

std::deque<int> insert_dequ(std::deque<int> vec, size_t taille)
{

	bool isodd = (vec.size() / taille) % 2;
	std::deque<std::deque<int> > work = making_pairs_dequ(vec, taille);
	std::deque<std::deque<int> > pend = getting_pend_dequ(work, taille);
	work = delete_work_dequ(work, taille);
	std::deque<int> leftover;
	if (work.rbegin()->size() != taille)
	{
		leftover = work.back();
		work.pop_back();
	}
	work = insert_pend_to_work(work, pend, isodd);
	work.push_back(leftover);
	vec.clear();
	for (size_t i = 0; i < work.size(); i++)
	{
		for (size_t j = 0; j < work[i].size(); j++)
			vec.push_back(work[i][j]);
	}
	return vec;
}

std::deque<int> sort_dequ(std::deque<int> deque, size_t nbrec)
{
	std::deque<int>::iterator it;
	size_t taille = std::pow(2, nbrec);
	std::deque<std::deque<int> > workplace = making_pairs_dequ(deque, taille);
	workplace = shuffle_workplace_dequ(workplace, taille);
	deque.clear();
	for (size_t i = 0; i < workplace.size(); i++)
	{
		for (size_t j = 0; j < workplace[i].size(); j++)
			deque.push_back(workplace[i][j]);
	}
	if (2 * taille < deque.size())
		deque = sort_dequ(deque, nbrec + 1);	
	
	deque = insert_dequ(deque, taille);
	if (nbrec == 1)
		deque = insert_dequ(deque, 1);
	
	return deque;
}