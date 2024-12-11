#include "RPN.hpp"

RPN::RPN()
{
	return ;
}

RPN::RPN(std::stack<double> number)
{
	this->num = number;
	return ;
}

RPN::RPN(const RPN &copy)
{
	*this = copy;
	return ;
}

RPN &RPN::operator=(const RPN &copy)
{
	this->num = copy.num;
	return (*this);
}

RPN::~RPN()
{
	return;
}

void RPN::calculate(std::string input)
{
	double a, b;

	for (size_t i = 0; i < input.size(); i++)
	{
		switch (input[i])
		{
		case ' ':
			break;

		case '+':
			if (this->num.size() >= 2)
			{
				a = this->num.top();
				this->num.pop();
				b = this->num.top();
				this->num.pop();
				this->num.push(a + b);
			}
			else
			{
				std::cout << "Error" << std::endl;
				return ;
			}
			break;

		case '-':
			if (this->num.size() >= 2)
			{
				a = this->num.top();
				this->num.pop();
				b = this->num.top();
				this->num.pop();
				this->num.push(b - a);
			}
			else
			{
				std::cout << "Error" << std::endl;
				return ;
			}
			break;

		case '/':
			if (this->num.size() >= 2)
			{
				a = this->num.top();
				this->num.pop();
				b = this->num.top();
				this->num.pop();
				if (a != 0)
					this->num.push(b / a);
				else
				{
					std::cout << "Error" << std::endl;
					return ;
				}
			}
			else
			{
				std::cout << "Error" << std::endl;
				return ;
			}
			break;

		case '*':
			if (this->num.size() >= 2)
			{
				a = this->num.top();
				this->num.pop();
				b = this->num.top();
				this->num.pop();
				this->num.push(a * b);
			}
			else
			{
				std::cout << "Error" << std::endl;
				return ;
			}
			break;

		default:
			if (!std::isdigit(input[i]))
			{
				std::cout << "Error" << std::endl;
				return ;
			}
			this->num.push(input[i] - '0');
			break;
		}
	}

	if (this->num.size() == 1)
		std::cout << this->num.top() << std::endl;
	else
		std::cout << "Error" << std::endl;
}

