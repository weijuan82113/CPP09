/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:45:38 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/12 02:09:24 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

static float	convertToFloat(const std::string& str)
{
	char* end;
	float value = std::strtof(str.c_str(), &end);

	if (*end != '\0') {
		throw std::invalid_argument("Error: Invalid conversion from string to float.");
	}
	return value;
}

static void	checkInputFormat(const std::string &line, std::string tokens[2])
{
	std::string::size_type pos = line.find(" | ");
	if (pos != std::string::npos)
	{
		tokens[0] = line.substr(0, pos);
		tokens[1] = line.substr(pos + 3);
	}
	else
		throw	BitcoinExchange::BadInputException("Error: bad input => " + line);
}

static bool	isNumber(const std::string &str)
{
	size_t	digit = 0;
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it)) {
			return false;
		}
		digit++;
	}
	if (digit == 2 || digit == 4)
		return true;
	return false;
}

static unsigned int	convertToUint(const std::string& str)
{
	char* end;
	errno = 0;
	unsigned int num = std::strtoul(str.c_str(), &end, 10);
	return num;
}

static unsigned int getDaysOfMonth(const unsigned int year, const unsigned int month)
{
	static const unsigned char daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month != 2)
	{
		return daysOfMonth[month - 1];
	}

	bool isLeapYear = false;
	if (year % 400 == 0) {
		isLeapYear = true;
	} else if (year % 100 == 0) {
		isLeapYear = false;
	} else if (year % 4 == 0) {
		isLeapYear = true;
	}
	return daysOfMonth[1] + 1 * isLeapYear;
}

static void	checkDateFormat(const std::string &str)
{
	std::string	yearStr, monthStr, dayStr;
	std::string::size_type	start = 0;
	std::string::size_type	end = str.find("-");

	if (end != std::string::npos)
	{
		yearStr = str.substr(start, end - start);
		start = end + 1;
		end = str.find("-", start);
	}
	else
		throw	BitcoinExchange::BadInputException("Error: bad input => " + str);

	if (end != std::string::npos)
	{
		monthStr = str.substr(start, end - start);
		start = end + 1;
		end = str.find("-", start);
	}
	else
		throw	BitcoinExchange::BadInputException("Error: bad input => " + str);

	if (end == std::string::npos)
		dayStr = str.substr(start);
	else
		throw	BitcoinExchange::BadInputException("Error: bad input => " + str);

	if (!isNumber(yearStr) || !isNumber(monthStr) || !isNumber(dayStr))
		throw	BitcoinExchange::InvalidDateException("Error: invalid date at line " + str);

	unsigned int year = convertToUint(yearStr);
	unsigned int month = convertToUint(monthStr);
	unsigned int day = convertToUint(dayStr);
	if (2009 > year || year > 9999)
		throw	BitcoinExchange::InvalidDateException("Error: invalid year at line " + str);
	if (1 > month || month > 12)
		throw	BitcoinExchange::InvalidDateException("Error: invalid month at line " + str);
	unsigned int daysOfMonth = getDaysOfMonth(year, month);
	if (1 > day || day > daysOfMonth)
		throw	BitcoinExchange::InvalidDateException("Error: invalid month at line " + str);
}

void	BitcoinExchange::loadDatabase()
{
	std::ifstream	ifs;
	std::string 	line;

	if (this->_rateDatabase.size() > 0)
		this->_rateDatabase.clear();
	ifs.open(DATABASE_FILEPATH);
	if (ifs.fail())
		throw	FileOpenException("Error: database file not found.");
	if (!std::getline(ifs, line))
		throw	InvalidFileFormat("Error: database file format error.");
	if (line != "date,exchange_rate")
		throw	InvalidFileFormat("Error: database file format error.");
	while (std::getline(ifs, line))
	{
		std::string tokens[2];
		std::string::size_type pos = line.find(",");
		if (pos != std::string::npos)
		{
			tokens[0] = line.substr(0, pos);
			tokens[1] = line.substr(pos + 1);
		}
		this->_rateDatabase[tokens[0]] = convertToFloat(tokens[1]);
	}
}

double	BitcoinExchange::getExchangeValue(const Date &date, float value)
{
	double	rate;
	Database::const_iterator it = _rateDatabase.lower_bound(date);
	if (it->first == date)
		rate = it->second;
	else if (it != _rateDatabase.begin()) {
		it = --it;
		rate = it->second;
	}
	else
		throw InvalidDateException("Error: no data corresponding to " + date + " in the database.");
	double exchangedValue = static_cast<double>(value) * rate;
	return exchangedValue;
}

void	BitcoinExchange::printAllValues(const char *inputFile)
{
	std::ifstream ifs;
	std::string line;

	ifs.open(inputFile);
	if (ifs.fail())
		throw BitcoinExchange::FileOpenException("Error: could not open file.");
	if (!std::getline(ifs, line))
		throw BitcoinExchange::InvalidFileFormat("Error: File format error.");

	if (line != "date | value")
		throw BitcoinExchange::InvalidFileFormat("Error: Input file format error at line 1");
	while (std::getline(ifs,line))
	{
		if (line.empty())
		{
			std::cerr << "Error: empty line." << std::endl;
			continue;
		}
		std::string	tokens[2];
		try
		{
			checkInputFormat(line, tokens);
			checkDateFormat(tokens[0]);
			float value = convertToFloat(tokens[1]);
			if (value < 0) {
				std::cerr << "Error: not a positive number." << std::endl;
				continue;
			}
			if (value > 1000) {
				std::cerr << "Error: too large a number." << std::endl;
				continue;
			}
			double exchangedValue = getExchangeValue(tokens[0], value);
			std::cout << tokens[0] << " => " << value << " = " << exchangedValue << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}
	}
}

BitcoinExchange::FileOpenException::FileOpenException(const std::string& str) : std::invalid_argument(str) {
}

BitcoinExchange::InvalidFileFormat::InvalidFileFormat(const std::string& str) : std::runtime_error(str) {
}

BitcoinExchange::InvalidDateException::InvalidDateException(const std::string& str) : std::runtime_error(str) {
}

BitcoinExchange::InvalidValueException::InvalidValueException(const std::string& str) : std::runtime_error(str) {
}

BitcoinExchange::BadInputException::BadInputException(const std::string &str) : std::runtime_error(str) {
}
