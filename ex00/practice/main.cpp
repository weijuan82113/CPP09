#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

enum DateType
{
	kYear = 0,
	kMonth = 1,
	kDay = 2
};

static bool canOpen(std::ifstream& fs,const std::string& fp)
{
	fs.open(fp.c_str());
	if (!fs.is_open())
		return false;
	return true;
}

static std::vector<std::string> tokenize(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = 0;

	// find delim from str[start]
	while ((end = str.find(delim, start)) != std::string::npos)
	{
		//strsub from (str, substr.length = end -start)
		tokens.push_back(str.substr(start, end - start));
		//to find next delim , set start to (end + delim's length)
		start = end + delim.size();
	}
	//store the last string
	tokens.push_back(str.substr(start));
	return tokens;
}

static void printTokens(std::vector<std::string> tokens)
{
	for (size_t i = 0; i < tokens.size(); i++)
		std::cout << "tokens[" << i << "]: " << tokens[i] << std::endl;

}

static bool checkYear(std::string& year_str)
{
	char *c;
	long year = std::strtol(year_str.c_str(), &c, 10);
	std::cout << "year: " << year;
	return true;
}


static bool checkDateType(std::string& date_str, DateType type)
{
	switch (type)
	{
	case (kYear) :
		if (!checkYear(date_str))
			return false;
		break;

	default:
		break;
	}
	return true;

}


static bool isDate(const std::string& date)
{
	std::vector<std::string> date_tokens;
	size_t start = 0;
	size_t end = 0;

	while ((end = date.find("-", start)) != std::string::npos)
	{
		date_tokens.push_back(date.substr(start, end - start));
		start = end + 1;
	}
	date_tokens.push_back(date.substr(start));
	//is 3 segment
	printTokens(date_tokens);
	if (date_tokens.size() != 3)
	{
		std::cout << "wrong data format" << std::endl;
		return false;
	}
	//from here
	//isNumber
	//isNegative
	//validate yyyy-mm-dd
	for (size_t i = 0; i < date_tokens.size(); i++)
		checkDateType(date_tokens[i], static_cast<DateType>(i));
	return true;
}

int main(int argc, char* argv[])
{
	std::string line;
	int i = 0;
	std::ifstream istream;

	if (argc != 2 || !canOpen(istream, argv[1]))
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	while (std::getline(istream, line))
	{
		//std::cout << line << std::endl;
		if (i == 0 && (line != "date,exchange_rate"))
		{
			std::cerr << "Error: database's format is wrong." << std::endl;
			return 1;
		}
		std::vector<std::string> tokens = tokenize(line, ",");
		printTokens(tokens);
		if (tokens.size() != 2)
		{
			std::cerr << "Error: database's format is wrong." << std::endl;
			return 1;
		}
		if (i !=0 && !isDate(tokens[0]))
		{
			std::cerr << "Error: date's format is wrong." << std::endl;
			return 1;
		}


		i++;
	}


	return 0;
}