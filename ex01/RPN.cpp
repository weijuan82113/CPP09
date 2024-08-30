#include "RPN.h"

RPN::RPN(const std::string& expression)
{
	calculate(expression);
}

void RPN::calculate(const std::string& exp)
{
	std::string delim = " ";
	std::stack<int> calculator;

	tokenizeExpression(exp, " ", calculator);
	if (calculator.size() > 1)
		throw InvalidRpnException("Error: the expression is wrong");
	std::cout << calculator.top() << std::endl;
}

void RPN::tokenizeExpression(const std::string& exp, const std::string& delim, std::stack<int>& stck)
{
	size_t start = 0;
	size_t end = 0;
	std::string cut_str;

	while((end = exp.find(delim, start)) != std::string::npos)
	{
		//validate
		cut_str = exp.substr(start, end - start);
		if (!isNum(cut_str) && !isOperator(cut_str))
			throw (InvalidRpnException("Error"));
		if (isOperator(cut_str))
			stck.push(calculateOperator(stck , cut_str));
		else
			stck.push(convertToInt(cut_str));
		start = end + delim.size();
	}
	cut_str = exp.substr(start);
	if (!isNum(cut_str) && !isOperator(cut_str))
		throw (InvalidRpnException("Error"));
	if (isOperator(cut_str))
		stck.push(calculateOperator(stck , cut_str));
	else
		stck.push(convertToInt(cut_str));
}

int RPN::calculateOperator(std::stack<int>& stck, std::string ope)
{
	if (stck.size() < 2)
		throw (InvalidRpnException("Error: the expression is wrong"));
	int b = stck.top();
	stck.pop();
	int a = stck.top();
	stck.pop();
	switch(convertToOperatorType(ope))
	{
		case(kADD):
			return a + b;
		case(kSub):
			return a - b;
		case(kMul):
			return a * b;
		case(kDiv):
			if (b == 0)
				throw InvalidRpnException("Error: the Divisor is 0");
			return a / b;
		default:
			throw InvalidRpnException("Error: the operator calculate is wrong");
			break;
	}
}

OperatorType RPN::convertToOperatorType(const std::string& str)
{
	if (str == "+")
		return kADD;
	if (str == "-")
		return kSub;
	if (str == "*")
		return kMul;
	if (str == "/")
		return kDiv;
	return kDefault;
}

int RPN::convertToInt(const std::string& str)
{
	int ret_int;
	std::stringstream ss;
	ss << str;
	ss >> ret_int;
	return  ret_int;
}

bool RPN::isOperator(const std::string& str)
{
	return (str == "+" || str == "-" || str == "*" || str == "/");
}


bool RPN::isNum(const std::string& str)
{
	int integer;
	std::stringstream ss;
	ss << str;
	ss >> integer;
	if (ss.fail())
		return false;
	if (integer > 9 || integer < -9)
		return false;
	return true;
}


RPN::InvalidRpnException::InvalidRpnException(const std::string& msg) : std::invalid_argument(msg) {}