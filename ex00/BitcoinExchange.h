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
		void loadDatabase();

	private:

};

#endif