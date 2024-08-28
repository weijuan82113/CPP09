#ifndef BITCOINEXCHANGE_H_
 #define BITCOINEXCHANGE_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> // For std::strtol
#include <cctype> //For ::isdigit
#include <map> //For std::map

#define DATABASEPATH "data_bk.csv"

enum DateType
{
	kYear = 0,
	kMonth = 1,
	kDay = 2
};

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();

		class InvalidDatabaseException : std::invalid_argument
		{
			public:
				InvalidDatabaseException(const std::string& msg);
		};
		class RangeErrorDatabaseException : std::range_error
		{
			public:
				RangeErrorDatabaseException(const std::string& msg);
		};
	private:
		std::map<std::string, double> database_;

		static void loadDatabase(const std::map<std::string, double>& database);
		static bool isOpen(std::ifstream& fs,const std::string& fp);
		static std::vector<std::string> tokenize(const std::string& str, const std::string& delim);
		static bool isDate(const std::string& date);
		static bool isNumber(const std::string& str);
		static bool ft_all_of_str(const std::string& str, int (*func)(int c));
		static long covertToLong(const std::string& str_date);
		static bool isDateType(const std::vector<long>& dates,const DateType& type);
		static long getDay(const long& year, const long& month);
		static bool isLeapYear(const long& year);


};

#endif