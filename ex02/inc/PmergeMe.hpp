#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <algorithm>
#include <cmath>

std::vector<int> sort_vect(std::vector<int> vector, size_t nbrec);
void sort_deque(std::deque<int> deque);
std::vector<int> argv_to_vector(int ac, char **argv);
std::deque<int> argv_to_deque(int ac, char **argv);
bool validInput(int ac, char **av);





#endif