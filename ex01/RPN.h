#ifndef RPN_H_
 #define RPN_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <stack>
#include <sstream>

enum OperatorType
{
	kADD,
	kSub,
	kMul,
	kDiv,
	kDefault
};

class RPN
{
	public:
		RPN(const std::string& expression);

		class InvalidRpnException : public std::invalid_argument
		{
			public:
				InvalidRpnException(const std::string& msg);
		};


	private:
		static void calculate(const std::string& exp);
		static bool isNum(const std::string& str);
		static int convertToInt(const std::string& str);
		static bool isOperator(const std::string& str);
		static void tokenizeExpression(const std::string& exp, const std::string& delim, std::stack<int>& stck);
		static int calculateOperator(std::stack<int>& stck, std::string ope);
		static OperatorType convertToOperatorType(const std::string& str);
};
//calculate
//spilit → validate(isNUM,opNum) → check stack1

#endif