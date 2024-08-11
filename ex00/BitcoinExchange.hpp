/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:58:16 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/08 19:14:27 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

#ifndef DATABASE_FILEPATH
#define DATABASE_FILEPATH "./data.csv"
#endif

typedef std::string				Date;
typedef std::map<Date, double>	Database;

class	BitcoinExchange
{
	private:
		Database	_rateDatabase;

	public:
		BitcoinExchange();
		~BitcoinExchange();

		void	loadDatabase();
		void	printAllValues(const char *inputFile);
		double	getExchangeValue(const Date &date, float value);
		
		class	FileOpenException : public	std::invalid_argument {
			public:
				FileOpenException(const std::string &str);
		};
		class	InvalidFileFormat : public	std::runtime_error {
			public:
				InvalidFileFormat(const std::string &str);	
		};
		class	InvalidDateException : public	std::runtime_error {
			public:
				InvalidDateException(const std::string &str);
		};
		class	InvalidValueException : public	std::runtime_error {
			public:
				InvalidValueException(const std::string &str);
		};
		class	BadInputException : public std::runtime_error {
			public:
				BadInputException(const std::string &str);
		};
};

#endif
