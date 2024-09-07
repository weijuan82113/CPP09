#include "PmergeMe.h"

//----utils func----

void PmergeMe::printList()
{
	for (std::list<int>::iterator it = list_.begin(); it != list_.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

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

	for (std::list<std::list<int>::iterator>::iterator it = it_list.begin();
		it != it_list.end(); it++)
	{
		std::cout << **it << "-->";
	}
	std::cout << "NULL" << std::endl;
}

void PmergeMe::printListTime()
{
	std::cout << "Time to process a range of "
	<< list_.size() << " elements with std::list :  "
	<< list_time_
	<< " us" << std::endl;
}

void PmergeMe::printDeque()
{
	for (std::deque<int>::iterator it = deque_.begin(); it != deque_.end(); it++)
	{
		std::cout << *it << "-->";
	}
	std::cout << "NULL" << std::endl;
}

void PmergeMe::printDeque(std::deque<int>& deque)
{
	for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); it++)
	{
		std::cout << *it << "-->";
	}
	std::cout << "NULL" << std::endl;
}

void PmergeMe::printItDeque(std::deque<std::deque<int>::iterator>& itDeque)
{
	for (std::deque<std::deque<int>::iterator>::iterator it = itDeque.begin();
		it != itDeque.end(); it++)
	{
		std::cout << **it << "-->" ;
	}
	std::cout << "NULL" << std::endl;
}

void PmergeMe::printDequeTime()
{
	std::cout << "Time to process a range of "
	<< deque_.size() << " elements with std::deque : "
	<< deque_time_
	<< " us" << std::endl;
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
}

void PmergeMe::createContainer(int integer)
{
	list_.push_back(integer);
	deque_.push_back(integer);
}


//------------------   List   ------------------


void PmergeMe::startSortList()
{
	std::clock_t start = std::clock();
	mergeInsertList(1);
	std::clock_t end = std::clock();
	list_time_ = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}


void PmergeMe::mergeInsertList(size_t size)
{
	if (size * 2 > list_.size())
		return;
	std::list<std::list<int>::iterator> big_it_list;
	std::list<std::list<int>::iterator> small_it_list;

	//bigに格納できるまでの個数はi+sizeが必要
	for (size_t i = 0; i + size <= list_.size(); i = i + size * 2)
	{
		std::list<int>::iterator big_it = list_.begin();
		ft_advance(big_it, i);
		std::list<int>::iterator small_it = big_it;
		if (i + size * 2 > list_.size())
		{
			small_it_list.push_back(small_it);
			break;
		}
		ft_advance(small_it, size);
		if (*big_it < *small_it)
			ft_swap(big_it, small_it, size);
		big_it_list.push_back(big_it);
		small_it_list.push_back(small_it);
	}
	mergeInsertList(size * 2);
	std::list<int> temp_sorted_list;
	insertSortedList(temp_sorted_list, big_it_list, small_it_list, size);
	updateList(temp_sorted_list);
}

void PmergeMe::insertSortedList(std::list<int>& temp_sorted_list,
			std::list<std::list<int>::iterator>& big_it_list,
			std::list<std::list<int>::iterator>& small_it_list,
			size_t size)
{
	std::list<std::list<int>::iterator>::iterator big_it = big_it_list.begin();
	std::list<std::list<int>::iterator>::iterator small_it = small_it_list.begin();
	pushBackList(temp_sorted_list, *small_it, size);
	while (big_it != big_it_list.end())
	{
		pushBackList(temp_sorted_list, *big_it, size);
		big_it ++;
	}

	size_t jacobsthal_number = 2;
	size_t pow_i = 2;
	size_t k = 1;
	while (k < small_it_list.size())
	{
		if (k + jacobsthal_number > small_it_list.size())
		{
			ft_advance(small_it, small_it_list.size() - k);
			for (size_t i = 0; i < small_it_list.size() - k; i++)
			{
				binaryInsertList(temp_sorted_list, small_it, size);
				small_it--;
			}
			k += (small_it_list.size() - k);
			break;
		}

		ft_advance(small_it, jacobsthal_number);
		for (size_t i = 0; i < jacobsthal_number ; i++)
		{
			binaryInsertList(temp_sorted_list, small_it, size);
			small_it--;
		}
		ft_advance(small_it, jacobsthal_number);
		k += jacobsthal_number;
		jacobsthal_number = std::pow(2, pow_i) - jacobsthal_number;
		pow_i ++;
	}
}

void PmergeMe::updateList(std::list<int>& temp_sorted_list)
{
	std::list<int>::iterator list_it = list_.begin();
	for (std::list<int>::iterator it = temp_sorted_list.begin();
		it != temp_sorted_list.end(); it++)
	{
		*list_it = *it;
		list_it++;
	}
}

int PmergeMe::countPairIndexList(std::list<std::list<int>::iterator>& sorted_it_list,
		std::list<std::list<int>::iterator>::iterator small_it, size_t size)
{
	int int_size = static_cast<int>(size);

	std::list<int>::iterator big_int_it = *small_it;
	ft_advance(big_int_it, int_size * (-1));
	size_t i = 0;
	for (std::list<std::list<int>::iterator>::iterator sorted_it = sorted_it_list.begin();
		sorted_it != sorted_it_list.end(); sorted_it++)
	{
		if (**sorted_it == *big_int_it)
			return i;
		i++;
	}
	return 0;
}

std::list<std::list<int>::iterator>::iterator PmergeMe::binarySearchList(std::list<std::list<int>::iterator>& it_list, int item, int low_index, int high_index)
{
	std::list<std::list<int>::iterator>::iterator it = it_list.begin();
	std::list<std::list<int>::iterator>::iterator low_it = it;
	ft_advance(low_it, low_index);
	std::list<std::list<int>::iterator>::iterator high_it = it;
	ft_advance(high_it, high_index);

	if (high_index <= low_index)
	{
		if (item > **low_it)
			ft_advance(low_it, 1);
		return low_it;
	}

	int mid_index = (low_index + high_index) / 2;
	std::list<std::list<int>::iterator>::iterator mid_it = it;
	ft_advance(mid_it, mid_index);
	if (item == **mid_it)
		return mid_it;

	if (item > **mid_it)
		return binarySearchList(it_list, item, mid_index + 1, high_index);

	return binarySearchList(it_list, item, low_index, mid_index - 1);
}

void PmergeMe::insertList(std::list<int>&list ,std::list<int>::iterator pos,
	std::list<int>::iterator insert_it, size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		pos = list.insert(pos, *insert_it);
		pos++;
		insert_it++;
	}
}

void PmergeMe::binaryInsertList(std::list<int>& temp_list,
	std::list<std::list<int>::iterator>::iterator small_it, size_t size)
{
	std::list<std::list<int>::iterator> sorted_it_list;
	updateSortedIteratorsList(sorted_it_list, temp_list, size);
	int pair_index = countPairIndexList(sorted_it_list, small_it, size);
	if (pair_index == 0)
		pair_index = sorted_it_list.size() - 1;
	std::list<std::list<int>::iterator>::iterator insert_pos_it = binarySearchList(sorted_it_list, **small_it, 0, pair_index);
	if (insert_pos_it == sorted_it_list.end())
		insertList(temp_list, temp_list.end(), *small_it, size);
	else
		insertList(temp_list, *insert_pos_it, *small_it, size);
}

void PmergeMe::updateSortedIteratorsList(std::list<std::list<int>::iterator>& sorted_its,
	std::list<int>& temp_list, size_t size)
{
	for (size_t i = 0; i < temp_list.size(); i = i + size)
	{
		std::list<int>::iterator it = temp_list.begin();
		ft_advance(it, i);
		sorted_its.push_back(it);
	}
}

void PmergeMe::pushBackList(std::list<int>& temp_list, std::list<int>::iterator it, size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		temp_list.push_back(*it);
		it++;
	}
}

//------------------   List   ------------------


//------------------   Deque   ------------------

void PmergeMe::startSortDeque()
{
	double start = std::clock();
	mergeInsertDeque(1);
	double end = std::clock();
	deque_time_ = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}



void PmergeMe::mergeInsertDeque(size_t size)
{
	if (size * 2 > deque_.size())
		return;
	std::deque<std::deque<int>::iterator> big_it_deque;
	std::deque<std::deque<int>::iterator> small_it_deque;

	for (size_t i = 0; i + size <= deque_.size(); i = i + size * 2)
	{
		std::deque<int>::iterator big_it = deque_.begin();
		ft_advance(big_it, i);
		std::deque<int>::iterator small_it = big_it;
		if (i + size * 2 > deque_.size())
		{
			small_it_deque.push_back(small_it);
			break;
		}
		ft_advance(small_it, size);
		if (*big_it < *small_it)
			ft_swap(big_it, small_it, size);
		big_it_deque.push_back(big_it);
		small_it_deque.push_back(small_it);
	}
	mergeInsertDeque(size * 2);
	std::deque<int> temp_sorted_deque;
	insertSortedDeque(temp_sorted_deque, big_it_deque, small_it_deque, size);
	updateDeque(temp_sorted_deque);
}

void PmergeMe::updateDeque(std::deque<int>& temp_sorted_deque)
{
	std::deque<int>::iterator deque_it = deque_.begin();
	for (std::deque<int>::iterator it = temp_sorted_deque.begin();
		it != temp_sorted_deque.end(); it++)
	{
		*deque_it = *it;
		deque_it++;
	}
}

void PmergeMe::insertSortedDeque(std::deque<int>& temp_sorted_deque,
			std::deque<std::deque<int>::iterator>& big_it_deque,
			std::deque<std::deque<int>::iterator>& small_it_deque,
			size_t size)
{
	std::deque<std::deque<int>::iterator>::iterator big_it = big_it_deque.begin();
	std::deque<std::deque<int>::iterator>::iterator small_it = small_it_deque.begin();
	pushBackDeque(temp_sorted_deque, *small_it, size);
	//utils
	while (big_it != big_it_deque.end())
	{
		pushBackDeque(temp_sorted_deque, *big_it, size);
		big_it ++;
	}
	size_t jacobsthal_number = 2;
	size_t pow_i = 2;
	size_t k = 1;
	while (k < small_it_deque.size())
	{
		if (k + jacobsthal_number > small_it_deque.size())
		{
			ft_advance(small_it, small_it_deque.size() - k);
			for (size_t i = 0; i < small_it_deque.size() - k; i++)
			{
				binaryInsertDeque(temp_sorted_deque, small_it, size);
				small_it--;
			}
			k += (small_it_deque.size() - k);
			break;
		}

		ft_advance(small_it, jacobsthal_number);
		for (size_t i = 0; i < jacobsthal_number; i++)
		{
			binaryInsertDeque(temp_sorted_deque, small_it, size);
			small_it--;
		}
		ft_advance(small_it, jacobsthal_number);
		k += jacobsthal_number;
		jacobsthal_number = std::pow(2, pow_i) - jacobsthal_number;
		pow_i ++;
	}
}

void PmergeMe::binaryInsertDeque(std::deque<int>& temp_deque,
	std::deque<std::deque<int>::iterator>::iterator small_it, size_t size)
{
	std::deque<std::deque<int>::iterator> sorted_it_deque;
	updateSortedIteratorsDeque(sorted_it_deque, temp_deque, size);
	int pair_index = countPairIndexDeque(sorted_it_deque, small_it, size);
	if (pair_index == 0)
		pair_index = sorted_it_deque.size() - 1;
	std::deque<std::deque<int>::iterator>::iterator insert_pos_it = binarySearchDeque(sorted_it_deque, **small_it, 0, pair_index);
	if (insert_pos_it == sorted_it_deque.end())
		insertDeque(temp_deque, temp_deque.end(), *small_it, size);
	else
		insertDeque(temp_deque, *insert_pos_it, *small_it, size);
}


void PmergeMe::insertDeque(std::deque<int>&deque, std::deque<int>::iterator pos,
	std::deque<int>::iterator insert_it, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		pos = deque.insert(pos, *insert_it);
		pos++;
		insert_it++;
	}
}


std::deque<std::deque<int>::iterator>::iterator PmergeMe::binarySearchDeque(std::deque<std::deque<int>::iterator>& it_list,
			int item, int low_index, int high_index)
{
	std::deque<std::deque<int>::iterator>::iterator it = it_list.begin();
	std::deque<std::deque<int>::iterator>::iterator low_it = it;
	ft_advance(low_it, low_index);
	std::deque<std::deque<int>::iterator>::iterator high_it = it;
	ft_advance(high_it, high_index);

	if (high_index <= low_index)
	{
		if (item > *it_list[low_index])
			ft_advance(low_it, 1);
		return low_it;
	}

	int mid_index = (low_index + high_index) / 2;
	std::deque<std::deque<int>::iterator>::iterator mid_it = it;
	ft_advance(mid_it, mid_index);
	if (item == *it_list[mid_index])
		return mid_it;

	if (item > *it_list[mid_index])
		return binarySearchDeque(it_list, item, mid_index + 1, high_index);

	return binarySearchDeque(it_list, item, low_index, mid_index - 1);
}

int PmergeMe::countPairIndexDeque(std::deque<std::deque<int>::iterator>& sorted_it_list,
	std::deque<std::deque<int>::iterator>::iterator small_it, size_t size)
{
	int int_size = static_cast<int>(size);

	std::deque<int>::iterator big_int_it = *small_it;
	ft_advance(big_int_it, int_size * (-1));
	size_t i = 0;
	for (std::deque<std::deque<int>::iterator>::iterator sorted_it = sorted_it_list.begin();
		sorted_it != sorted_it_list.end(); sorted_it++)
	{
		if (**sorted_it == *big_int_it)
			return i;
		i++;
	}
	return 0;
}

void PmergeMe::updateSortedIteratorsDeque(std::deque<std::deque<int>::iterator>& sorted_its,
			std::deque<int>& temp_deque, size_t size)
{
	for (size_t i = 0; i < temp_deque.size(); i = i + size)
	{
		std::deque<int>::iterator it = temp_deque.begin();
		ft_advance(it, i);
		sorted_its.push_back(it);
	}
}

void PmergeMe::pushBackDeque(std::deque<int>& temp_deque, std::deque<int>::iterator it, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		temp_deque.push_back(*it);
		it ++;
	}
}

//------------------   Deque   ------------------

PmergeMe::invalidArgumentPmergeMeException::invalidArgumentPmergeMeException(const std::string& msg)
	: std::invalid_argument(msg) {};
