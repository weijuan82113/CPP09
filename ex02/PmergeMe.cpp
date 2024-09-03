#include "PmergeMe.h"

//----utils func----

void PmergeMe::printList()
{
	for (std::list<int>::iterator it = list_.begin(); it != list_.end(); it++)
	{
		std::cout << *it << "-->";
	}
	std::cout << "NULL" << std::endl;
}

//----utils func----

PmergeMe::PmergeMe() {};
PmergeMe::~PmergeMe() {};

void PmergeMe::validateInputArgument(char** argv)
{
	for (int i = 0; argv[i]; i ++)
	{
		char* end;
		long l = std::strtol(argv[i], &end, 10);

		if (*end != '\0')
			throw invalidArgumentPmergeMeException("Error");
		if (l < 0)
			throw invalidArgumentPmergeMeException("Error");
		if (l > static_cast<long>(std::numeric_limits<int>::max()))
			throw invalidArgumentPmergeMeException("Error");
		createContainer(static_cast<int>(l));
	}
	//utils
	printList();
}


void PmergeMe::createContainer(int integer)
{
	list_.push_back(integer);
}

void PmergeMe::mergerInsertList()
{

}

PmergeMe::invalidArgumentPmergeMeException::invalidArgumentPmergeMeException(const std::string& msg)
	: std::invalid_argument(msg) {};
