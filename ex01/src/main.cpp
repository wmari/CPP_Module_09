#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error" << std::endl;
		return (0);
	}
	std::string input = argv[1];
	RPN TI;
	TI.calculate(input);
	return (0);
}