#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <iostream>
#include <string>

class RPN
{
	private:
		std::stack<double> num;
		
	public:
		RPN();
		RPN(std::stack<double> number);
		RPN(const RPN &copy);

		RPN &operator=(const RPN &copy);

		void calculate(std::string input);

		~RPN();
};



#endif