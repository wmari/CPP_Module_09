#include "PmergeMe.hpp"
#define MAX_PRINT 20

int main(int argc, char **argv)
{
	if (!validInput(argc, argv))
	{
		std::cout << "Error" << std::endl;
		return (0);
	}
	std::vector<int> vect = argv_to_vector(argc, argv);
	std::deque<int> dequ = argv_to_deque(argc, argv);
	std::cout << "Before:";
	std::vector<int>::iterator it = vect.begin();
	int i = 0;
	while (it != vect.end() && i < MAX_PRINT)
	{
		std::cout <<" " << *it;
		i++;
		it++;
	}
	if (it != vect.end())
		std::cout << " [...]";
	std::cout << std::endl;
	// clock_t time;
	
	
	return (0);
}