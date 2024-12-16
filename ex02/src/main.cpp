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
}

void	print_ordered_deque(std::deque<int> vec)
{
	for (size_t i = 1; i < vec.size(); i++)
	{
		if (vec[i] < vec[i -1])
		{
			std::cout << "array is not sorted" << std::endl;
			return;
		}
	}
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
	std::cout << "Before:\t";
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
	clock_t dtimevect = clock();
	vect = sort_vect(argv_to_vector(argc, argv), 1);
	clock_t endtimevect = clock();
	double time_vect = static_cast<double>(endtimevect - dtimevect);
	double time_in_micro = (time_vect / CLOCKS_PER_SEC) * 1e3;
	it = vect.begin();
	i = 0;
	std::cout << "After:\t";
	while (it != vect.end() && i < MAX_PRINT)
	{
		std::cout <<" " << *it;
		i++;
		it++;
	}
	if (it != vect.end())
		std::cout << " [...]";
	std::cout << std::endl;
	print_ordered(vect);
	std::cout << "Time to process a range of\t" << vect.size() << " elements with std::vector :\t" << time_in_micro << "ms" <<std::endl;
	clock_t dqtime = clock();
	dequ = sort_dequ(argv_to_deque(argc, argv), 1);
	clock_t endtimedequ = clock();
	print_ordered_deque(dequ);
	double time_dequ = static_cast<double>(endtimedequ - dqtime);
	time_in_micro = (time_dequ / CLOCKS_PER_SEC) * 1e3;
	std::cout << "Time to process a range of\t" << vect.size() << " elements with std::deque :\t" << time_in_micro << "ms" <<std::endl;
	return (0);
}