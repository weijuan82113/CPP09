#ifndef PMERGEME_H_
 #define PMERGEME_H_

#include <iostream>
#include <list>
#include <limits>
#include <cstdlib>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();

		//-----utils-----
		void printList();
		//-----utils-----

		void validateInputArgument(char** argv);
		void createContainer(int integer);
		void mergerInsertList();





		class invalidArgumentPmergeMeException : public std::invalid_argument
		{
			public:
				invalidArgumentPmergeMeException(const std::string &msg);
		};

	private:
		std::list<int> list_;



};

#endif