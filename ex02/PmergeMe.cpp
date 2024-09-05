#include "PmergeMe.h"

//----utils func----

void PmergeMe::printList(std::list<int>& list)
{
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it << "-->";
	}
	std::cout << "NULL" << std::endl;
}


void PmergeMe::printItList(std::list<std::list<int>::iterator>& it_list)
{

	for (std::list<std::list<int>::iterator>::iterator it = it_list.begin(); it != it_list.end(); it++)
	{
		std::cout << **it << "-->";
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
	printList(list_);
}


void PmergeMe::createContainer(int integer)
{
	list_.push_back(integer);
}

void PmergeMe::mergerInsertList(size_t size)
{
	if (size * 2 > list_.size())
		return;
	std::list<std::list<int>::iterator> big_it_list;
	std::list<std::list<int>::iterator> small_it_list;

	//bigに格納できるまでの個数がi+sizeが必要
	for (size_t i = 0; i + size <= list_.size(); i = i + size * 2)
	{
		std::list<int>::iterator big_it = list_.begin();
		ft_advance(big_it, i);
		std::list<int>::iterator small_it = big_it;
		std::cout << "i: " << i << std::endl;
		std::cout << "size: " << size  << std::endl;
		std::cout << "list_.size(): " << list_.size() << "\n\n" << std::endl;
		if (i + size * 2 > list_.size())
		{
			small_it_list.push_back(small_it);
			break;
		}
		ft_advance(small_it, size);
		if (*big_it < *small_it)
		{
			ft_swap(big_it, small_it, size);
		}
		big_it_list.push_back(big_it);
		small_it_list.push_back(small_it);
	}
	std::cout << "big it list: ";
	printItList(big_it_list);
	std::cout << "small it list: ";
	printItList(small_it_list);
	//utils
	printList(list_);
	mergerInsertList(size * 2);
	std::list<int> temp_sorted_list;
	insertSortedList(temp_sorted_list, big_it_list, small_it_list, size);


}


void PmergeMe::insertSortedList(std::list<int>& temp_sorted_list,
			std::list<std::list<int>::iterator>& big_it_list,
			std::list<std::list<int>::iterator>& small_it_list,
			size_t size)
{
	std::list<std::list<int>::iterator>::iterator big_it = big_it_list.begin();
	std::list<std::list<int>::iterator>::iterator small_it = small_it_list.begin();
	ft_push_back(temp_sorted_list, *small_it, size);
	small_it++;
	while (big_it != big_it_list.end())
	{
		ft_push_back(temp_sorted_list, *big_it, size);
		big_it ++;
	}
	std::cout << "temp_sorted_list: " ;
	printList(temp_sorted_list);
	if (small_it != small_it_list.end())
	{
		//here
		// binary_insert with jacobsthal_number

	}
}

void PmergeMe::ft_push_back(std::list<int>& temp_list, std::list<int>::iterator& it, size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		temp_list.push_back(*it);
		it++;
	}
	it--;
}


PmergeMe::invalidArgumentPmergeMeException::invalidArgumentPmergeMeException(const std::string& msg)
	: std::invalid_argument(msg) {};
