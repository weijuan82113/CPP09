/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 01:20:21 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/09 02:51:01 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(const std::string &expString) : _expString(expString) {}

RPN::~RPN() {}

static std::vector<std::string>	split(const std::string& str, char delimiter)
{
    std::vector<std::string>	tokens;
    std::istringstream			iss(str);
    std::string					token;
    while (std::getline(iss, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

static bool	isOverflowByPlus(long a, long b)
{
	if (a > 0 && b > 0 && a > std::numeric_limits<long>::max() - b)
		return true;
	if (a < 0 && b < 0 && a < std::numeric_limits<long>::min() - b)
		return true;
	return false;
}

static bool	isOverflowByMinus(long a, long b)
{
	if (a > 0 && b < 0 && a > std::numeric_limits<long>::max() + b)
		return true;
	if (a < 0 && b > 0 && a < std::numeric_limits<long>::min() + b)
		return true;
	return false;
}

static bool	isOverflowByMultiply(long a, long b)
{
	if (a == 0 || b == 0) return false;
	if (a > 0 && b > 0 && a > std::numeric_limits<long>::max() / b)
		return true;
	if (a > 0 && b < 0 && std::numeric_limits<long>::min() / a > b)
		return true;
	if (a < 0 && b > 0 && a < std::numeric_limits<long>::min() / b)
		return true;
	if (a < 0 && b < 0)
	{
		if (a == std::numeric_limits<long>::min() || b == std::numeric_limits<long>::min())
			return true;
		else
			return a < std::numeric_limits<long>::min() / std::abs(b);
	}
	return false;
}

static bool	isOverflowByDivision(long a, long b)
{
	if (a == std::numeric_limits<long>::min() && b == -1)
		return true;
	return false;
}

long	RPN::getAnswer()
{
	if (this->_expString.empty())
		throw	std::invalid_argument("Error: empty expression.");

	std::stack<long>	stack;
	std::vector<std::string> tokens = split(this->_expString, ' ');
	
	for (size_t i = 0; i < tokens.size(); i++)
	{
		const std::string	&token = tokens[i];
		if (token.size() != 1)
			throw	std::invalid_argument("Error: invalid expression.");
		if (std::isdigit(token[0]))
		{
			char	*end;
			long	num = std::strtol(token.c_str(), &end, 10);
			stack.push(num);
		}
		else
		{
			if (stack.size() < 2)
				throw	std::invalid_argument("Error: invalid expression.");
			long	operand2 = stack.top();
			stack.pop();
			long	operand1 = stack.top();
			stack.pop();
			
			if (token == "+")
			{
				if (isOverflowByPlus(operand1, operand2))
					throw	std::out_of_range("Error: Overflow by plus.");
				stack.push(operand1 + operand2);
			}
			else if (token == "-")
			{
				if (isOverflowByMinus(operand1, operand2))
					throw	std::out_of_range("Error: Overflow by minus.");
				stack.push(operand1 - operand2);
			}
			else if (token == "*")
			{
				if (isOverflowByMultiply(operand1, operand2))
					throw	std::out_of_range("Error: Overflow by multiplication.");
				stack.push(operand1 * operand2);
			}
			else if (token == "/")
			{
				if (operand2 == 0)
					throw	std::invalid_argument("Error: division by zero.");
				if (isOverflowByDivision(operand1, operand2))
					throw	std::out_of_range("Error: Overflow by division.");
				stack.push(operand1 / operand2);
			}
			else
				throw	std::invalid_argument("Error: unknown operator" + token);
		}
	}
	if (stack.size() != 1)
		throw	std::invalid_argument("Error: invalid expression.");
	return stack.top();
}
