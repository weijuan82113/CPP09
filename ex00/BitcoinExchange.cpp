#include "BitcoinExchange.h"

//------util func------

// static void printTokens(std::vector<std::string> tokens)
// {
// 	for (size_t i = 0; i < tokens.size(); i++)
// 		std::cout << "tokens[" << i << "]: " << tokens[i] << std::endl;

// }
// static void printMap(const std::map<std::string, double>& m)
// {
// 	for (std::map<std::string, double>::const_iterator it = m.begin(); it != m.end(); ++it)
//         std::cout << "first: " << it->first << ", second: " << it->second << std::endl;
// }
// static void printVector(const std::vector<std::pair<std::string, double> > v)
// {
// 	for (std::vector<std::pair<std::string, double> >::const_iterator it = v.begin(); it != v.end(); it++)
// 		 std::cout << "first: " << it->first << ", second: " << it->second << std::endl;
// }

//------util func------



BitcoinExchange::BitcoinExchange()
{
	loadDatabase(database_);
	// std::cout << "------db------" << std::endl;
	// printMap(database_);
	// std::cout << "------db------\n\n" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& b)
{
	*this = b;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->database_ = other.database_;
		this->data_ = other.data_;
	}
	return *this;
}

void BitcoinExchange::loadDatabase(std::map<std::string, double>& database)
{
	std::string line;
	std::ifstream istream;

	if (!isOpen(istream, DATABASEPATH))
		throw (InvalidDatabaseException("Database Error: could not open file."));
	int i = 0;
	while (std::getline(istream, line))
	{
		if (i == 0 && (line != "date,exchange_rate"))
			throw (InvalidDatabaseException("Database Error: database's format is wrong."));
		std::vector<std::string> tokens = tokenize(line, ",");
		if (tokens.size() != 2)
			throw (InvalidDatabaseException("Database Error: database's format is wrong."));
		if (i !=0 && !isDate(tokens[0]))
			throw (RangeErrorDatabaseException("Database Error: date's format is wrong."));
		if (i !=0 && (!isValue(tokens[1]) || convertToDouble(tokens[1]) < 0))
			throw (RangeErrorDatabaseException("Database Error: value's format is wrong."));
		database[tokens[0]] = convertToDouble(tokens[1]);
		i++;
	}
}

void BitcoinExchange::inputFile(const std::string& fp)
{
	std::string line;
	std::ifstream istream;

	if (!isOpen(istream, fp))
		throw (InvalidInputfileException("Error: could not open file."));
	int i = 0;
	while (std::getline(istream, line))
	{
		std::pair<std::string, double> temp_pair;
		if (i == 0 && (line != "date | value"))
			throw (InvalidInputfileException("Error: inputfile's format is wrong."));
		std::vector<std::string> tokens = tokenize(line, " | ");
		if (tokens.size() == 1)
		{
			temp_pair = std::make_pair(tokens[0], 0.0);
			data_.push_back(temp_pair);
			i ++;
			continue;
		}
		if (tokens.size() != 2)
			throw(InvalidInputfileException("Error: inputfile's format is wrong."));
		if(i != 0 && !isValue(tokens[1]))
			throw(InvalidInputfileException("Error: inputfile's value is wrong."));
		temp_pair = std::make_pair(tokens[0], convertToDouble(tokens[1]));
		data_.push_back(temp_pair);
		i ++;
	}
	// std::cout << "------input data------" << std::endl;
	// printVector(data_);
	// std::cout << "------input data------\n\n" << std::endl;
}

void BitcoinExchange::printData()
{
	//data_.begin() + 1 to skip the format's first row
	for (std::vector<std::pair<std::string, double> >::const_iterator it = data_.begin() + 1; it != data_.end(); it++)
	{
		if (!isDate(it->first))
		{
			std::cout << "Error: bad input => " << it->first << std::endl;
			continue;
		}
		if (it->second < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (it->second > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		//print data * database
		std::map<std::string, double>::const_iterator search = database_.find(it->first);
		if (search == database_.end())
			findClosestMatch(it,database_);
		else
			std::cout << it->first << " => " << it->second << " = "<< it->second * search->second << std::endl;
	}
}


//------static util func()------
void BitcoinExchange::findClosestMatch(const std::vector<std::pair<std::string, double> >::const_iterator& it,
 											std::map<std::string, double> db)
{
	std::map<std::string, double>::const_iterator search = db.lower_bound(it->first);
	if (search == db.begin())
		std::cout << "Error: can not find the suitable value in database" << " => " << it->first << std::endl;
	//back to previous value
	search --;
	std::cout << it->first << " => " << it->second << " = "<< it->second * search->second << std::endl;
}

bool BitcoinExchange::isOpen(std::ifstream& fs,const std::string& fp)
{
	fs.open(fp.c_str());
	if (!fs.is_open())
		return false;
	return true;
}

std::vector<std::string> BitcoinExchange::tokenize(const std::string& str, const std::string& delim)
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

double BitcoinExchange::convertToDouble(const std::string& str)
{
	std::stringstream ss(str);
	double result;
	ss >> result;
	return result;
}

bool BitcoinExchange::isValue(const std::string& value)
{
	std::stringstream ss(value);
	double result;
	ss >> result;
	return !ss.fail();
}

bool BitcoinExchange::isDate(const std::string& date)
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
	if (date_tokens.size() != 3)
		return false;
	std::vector<long> long_date_tokens;
	for (size_t i = 0; i < date_tokens.size(); i++)
	{
		//isNumber
		if (!isNumber(date_tokens[i]))
			return false;
		//convert string to long
		long long_date;
		if ((long_date = covertToLong(date_tokens[i])) == 0)
			return false;
		long_date_tokens.push_back(long_date);
	}
	//validate yyyy-mm-dd
	for (size_t i = 0; i < long_date_tokens.size(); i++)
	{
		if (!isDateType(long_date_tokens, static_cast<DateType>(i)))
			return false;
	}
	return true;
}

bool BitcoinExchange::isNumber(const std::string& str)
{
	return (!str.empty() && ft_all_of_str(str, ::isdigit));
}

bool BitcoinExchange::ft_all_of_str(const std::string& str, int (*func)(int c))
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!func(str[i]))
			return false;
	}
	return true;
}

long BitcoinExchange::covertToLong(const std::string& str_date)
{
	const char *p = str_date.c_str();
	char* p_end;
	long long_date = std::strtol(p, &p_end, 10);
	//after transfer, remain charactors not transfered
	if (*p_end != '\0')
		return 0;
	return long_date;
}

bool BitcoinExchange::isDateType(const std::vector<long>& dates,const DateType& type)
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

long BitcoinExchange::getDay(const long& year, const long& month)
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

bool BitcoinExchange::isLeapYear(const long& year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

BitcoinExchange::InvalidDatabaseException::InvalidDatabaseException(const std::string& msg) : std::invalid_argument(msg) {}
BitcoinExchange::RangeErrorDatabaseException::RangeErrorDatabaseException(const std::string& msg) : std::range_error(msg) {}
BitcoinExchange::InvalidInputfileException::InvalidInputfileException(const std::string& msg) : std::invalid_argument(msg) {}
BitcoinExchange::RangeErrorInputfileException::RangeErrorInputfileException(const std::string& msg) : std::range_error(msg) {}