#include "PmergeMe.hpp"
#define MAX_PRINT 20

void	print_ordered(std::vector<int> vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (vec[i] < vec[i -1])
		{
			std::cout << "array is not sorted" << std::endl;
			return;
		}
	}
	std::cout << "array is sorted" << std::endl;
}

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
	vect = sort_vect(argv_to_vector(argc, argv), 1);
	print_ordered(vect);
	return (0);
}