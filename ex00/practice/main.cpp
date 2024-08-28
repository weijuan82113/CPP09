#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> // For std::strtol
#include <cctype> //For ::isdigit

static bool ft_all_of_str(const std::string& str, int (*func)(int c))
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!func(str[i]))
			return false;
	}
	return true;
};


enum DateType
{
	kYear = 0,
	kMonth = 1,
	kDay = 2
};

static bool isOpen(std::ifstream& fs,const std::string& fp)
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

bool isLeepYear(const long& year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

long getDay(const long& year, const long& month)
{
	switch(month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			if (isLeepYear(year))
				return 29;
			return 28;
		default :
			return 0;
	}
}

bool isDay(const std::vector<long>& dates)
{
	//check the day is the year & month
	if (dates[2] != getDay(dates[0], dates[1]))
		return false;
	return true;
}

static bool isDateType(const std::vector<long>& dates,const DateType& type)
{
	//out of range
	switch (type)
	{
		case (kYear):
			if (dates[type] > 9999)
				return false;
			break;
		case (kMonth):
			if (dates[type] > 12)
				return false;
			break;
		case (kDay):
			if (dates[type] > 31 || !isDay(dates))
				return false;
			break;
		default:
			break;
	}
	return true;
}

static bool isNumber(const std::string& str)
{
	return (!str.empty() && ft_all_of_str(str, ::isdigit));
}

long covertToLong(const std::string& str_date)
{
	const char *p = str_date.c_str();
	char* p_end;
	long long_date = std::strtol(p, &p_end, 10);
	//not be found in the whole string(exit space)

	std::cout << "p: " << p << std::endl;
	std::cout << "p_end: " << *p_end << std::endl;


	if (p != p_end)
		return 0;
	return long_date;
}

static bool isDate(const std::string& date)
{
	std::vector<std::string> date_tokens;
	size_t start = 0;
	size_t end = 0;

	//parse date into yyyy,mm,dd tokens
	while ((end = date.find("-", start)) != std::string::npos)
	{
		date_tokens.push_back(date.substr(start, end - start));
		start = end + 1;
	}
	date_tokens.push_back(date.substr(start));
	//is 3 tokens
	printTokens(date_tokens);
	if (date_tokens.size() != 3)
	{
		std::cout << "Error: date's format is wrong." << std::endl;
		return false;
	}
	std::vector<long> long_date_tokens;
	for (size_t i = 0; i < date_tokens.size(); i++)
	{
		//isNumber
		if (!isNumber(date_tokens[i]))
		{
			std::cout << "Error: date is not number" << std::endl;
			return false;
		}
		//convert string to long
		long long_date;
		if ((long_date = covertToLong(date_tokens[i])) == 0)
		{
			std::cout << "Error: date cant convert to long" << std::endl;
			return false;
		}
		long_date_tokens.push_back(long_date);
	}
	//validate yyyy-mm-dd
	for (size_t i = 0; i < long_date_tokens.size(); i++)
	{
		if (!isDateType(long_date_tokens, static_cast<DateType>(i)))
		{
			std::cout << "Error: the date is out of range" << std::endl;
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	std::string line;
	int i = 0;
	std::ifstream istream;

	if (argc != 2 || !isOpen(istream, argv[1]))
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
		//printTokens(tokens);
		if (tokens.size() != 2)
		{
			std::cerr << "Error: database's format is wrong." << std::endl;
			return 1;
		}
		//here
		if (i !=0 && !isDate(tokens[0]))
		{
			std::cerr << "Error: date's format is wrong." << std::endl;
			return 1;
		}
		i++;
	}


	return 0;
}