#include "BitcoinExchange.h"

BitcoinExchange::BitcoinExchange()
{
	loadDatabase(database_);
}

BitcoinExchange::~BitcoinExchange() {}

//util func
static void printTokens(std::vector<std::string> tokens)
{
	for (size_t i = 0; i < tokens.size(); i++)
		std::cout << "tokens[" << i << "]: " << tokens[i] << std::endl;

}

void loadDatabase(std::map<std::string, double>& database)
{
	std::string line;
	std::ifstream istream;

	if (!isOpen(istream, DATABASEPATH))
		throw (BitcoinExchange::InvalidDatabaseException("Error: could not open file."));
	int i = 0;
	while (std::getline(istream, line))
	{
		if (i == 0 && (line != "date,exchange_rate"))
			throw (BitcoinExchange::InvalidDatabaseException("Error: database's format is wrong."));
		std::vector<std::string> tokens = tokenize(line, ",");
		if (tokens.size() != 2)
			throw (BitcoinExchange::InvalidDatabaseException("Error: database's format is wrong."));
		if (i !=0 && !isDate(tokens[0]))
			throw (BitcoinExchange::RangeErrorDatabaseException("Error: date's format is wrong."));
		if (i !=0 && !isValue(tokens[1]))
			throw (BitcoinExchange::RangeErrorDatabaseException("Error: value's format is wrong."));
		database[tokens[0]] = convertToDouble(tokens[1]);
		i++;
	}
}

bool isOpen(std::ifstream& fs,const std::string& fp)
{
	fs.open(fp.c_str());
	if (!fs.is_open())
		return false;
	return true;
}

std::vector<std::string> tokenize(const std::string& str, const std::string& delim)
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

double convertToDouble(const std::string& str)
{
	std::stringstream ss(str);
	double result;
	ss >> result;
	return result;
}

bool isValue(const std::string& value)
{
	std::stringstream ss(value);
	double result;
	ss >> result;
	if(ss.fail() || result < 0)
		throw (BitcoinExchange::RangeErrorDatabaseException("Error: cant convert value to positive double"));
	std::cout << "double: " << result << std::endl;
	return true;
}

bool isDate(const std::string& date)
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
		return false;
	std::vector<long> long_date_tokens;
	for (size_t i = 0; i < date_tokens.size(); i++)
	{
		//isNumber
		if (!isNumber(date_tokens[i]))
			throw (BitcoinExchange::RangeErrorDatabaseException("Error: date is not number"));
		//convert string to long
		long long_date;
		if ((long_date = covertToLong(date_tokens[i])) == 0)
			throw (BitcoinExchange::RangeErrorDatabaseException("Error: date cant convert to long"));
		long_date_tokens.push_back(long_date);
	}
	//validate yyyy-mm-dd
	for (size_t i = 0; i < long_date_tokens.size(); i++)
	{
		if (!isDateType(long_date_tokens, static_cast<DateType>(i)))
			throw (BitcoinExchange::RangeErrorDatabaseException("Error: the date is out of range"));
	}
	return true;
}

bool isNumber(const std::string& str)
{
	return (!str.empty() && ft_all_of_str(str, ::isdigit));
}

bool ft_all_of_str(const std::string& str, int (*func)(int c))
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!func(str[i]))
			return false;
	}
	return true;
}

long covertToLong(const std::string& str_date)
{
	const char *p = str_date.c_str();
	char* p_end;
	long long_date = std::strtol(p, &p_end, 10);
	//after transfer, remain charactors not transfered
	if (*p_end != '\0')
		return 0;
	return long_date;
}

bool isDateType(const std::vector<long>& dates,const DateType& type)
{
	//out of range
	switch (type)
	{
		case (kYear):
			if (dates[kYear] > 9999)
				return false;
			break;
		case (kMonth):
			if (dates[kMonth] > 12)
				return false;
			break;
		case (kDay):
			if (dates[kDay] > getDay(dates[kYear], dates[kMonth]))
				return false;
			break;
		default:
			break;
	}
	return true;
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
			if (isLeapYear(year))
				return 29;
			return 28;
		default :
			return 0;
	}
}

bool isLeapYear(const long& year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}



BitcoinExchange::InvalidDatabaseException::InvalidDatabaseException(const std::string& msg) : std::invalid_argument(msg) {}
BitcoinExchange::RangeErrorDatabaseException::RangeErrorDatabaseException(const std::string& msg) : std::range_error(msg) {}