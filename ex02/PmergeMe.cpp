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

	//utils
	// std::cout << "big it list: ";
	// printItList(big_it_list);
	// std::cout << "small it list: ";
	// printItList(small_it_list);
	// std::cout << "\n\n";
	mergeInsertList(size * 2);
	std::list<int> temp_sorted_list;
	insertSortedList(temp_sorted_list, big_it_list, small_it_list, size);
	updateList(temp_sorted_list);
	//utils
	printList(list_);
}

void PmergeMe::updateList(std::list<int>& temp_sorted_list)
{
	std::list<int>::iterator list_it = list_.begin();
	for (std::list<int>::iterator it = temp_sorted_list.begin();
		it != temp_sorted_list.end(); it ++)
	{
		*list_it = *it;
		list_it++;
	}
}

void PmergeMe::insertSortedList(std::list<int>& temp_sorted_list,
			std::list<std::list<int>::iterator>& big_it_list,
			std::list<std::list<int>::iterator>& small_it_list,
			size_t size)
{
	std::list<std::list<int>::iterator>::iterator big_it = big_it_list.begin();
	std::list<std::list<int>::iterator>::iterator small_it = small_it_list.begin();
	pushBackList(temp_sorted_list, *small_it, size);
	//utils
	//std::cout << "------insertSortedList------\n\n\n" << std::endl;
	while (big_it != big_it_list.end())
	{
		pushBackList(temp_sorted_list, *big_it, size);
		big_it ++;
	}
	//utils
	// std::cout << "----before binary sort----\n";
	// std::cout << "big it list: ";
	// printItList(big_it_list);
	// std::cout << "small it list: ";
	// printItList(small_it_list);
	// std::cout << "\n";
	// std::cout << "temp_sorted_list: " ;
	// printList(temp_sorted_list);
	// std::cout << std::endl;

	size_t jacobsthal_number = 2;
	//pow_iはjacobsthal_number = 2^i - jacobsthal_numberを計算するための変数
	size_t pow_i = 2;
	//kはsmall_it_listからインサート済み個数
	size_t k = 1;
	//ここのロジックを見直す
	while (k < small_it_list.size())
	{
		//残るsmall_itがある場合の対処をする
		if (k + jacobsthal_number > small_it_list.size())
		{
			ft_advance(small_it, small_it_list.size() - k);
			for (size_t i = 0; i < small_it_list.size() - k; i++)
			{
				//utils
				//std::cout << "the small_it to be inserted: " << **small_it << std::endl;
				binaryInsertList(temp_sorted_list, small_it, size);
				small_it--;
				// std::cout << "----after remain binary sort----\n";
				// std::cout << "temp_sorted_list: " ;
				// printList(temp_sorted_list);
			}
			k += (small_it_list.size() - k);
			break;
		}

		ft_advance(small_it, jacobsthal_number);
		for (size_t i = 0; i < jacobsthal_number ; i++)
		{
			//utils
			//jacobsthal_number_groupの最後からbinary-insert
			// std::cout << "the small_it to be inserted: " << **small_it << std::endl;
			binaryInsertList(temp_sorted_list, small_it, size);
			// std::cout << "----after binary sort----\n";
			// std::cout << "temp_sorted_list: " ;
			// printList(temp_sorted_list);
			// std::cout << std::endl;
			small_it--;
		}
		//jacobsthal_number分、前倒したので、またsmall_itをjacobsthal_number分前進させ
		ft_advance(small_it, jacobsthal_number);
		//次のjacobsthal_number_groupの最初位置にする
		k += jacobsthal_number;
		jacobsthal_number = std::pow(2, pow_i) - jacobsthal_number;
		pow_i ++;
	}
	//utils
	//std::cout << "\n------insertSortedList------\n\n\n" << std::endl;
}

int PmergeMe::countPairIndex(std::list<std::list<int>::iterator>& sorted_it_list,
		std::list<std::list<int>::iterator>::iterator small_it, size_t size)
{
	int int_size = static_cast<int>(size);

	//move small_it to the pair of big_it
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
	updateSortedIterators(sorted_it_list, temp_list, size);
	int pair_index = countPairIndex(sorted_it_list, small_it, size);
	//pairを見つからなければ、全ソート済みのリストをbinarySearchする
	if (pair_index == 0)
		pair_index = sorted_it_list.size() - 1;
	std::list<std::list<int>::iterator>::iterator insert_pos_it = binarySearchList(sorted_it_list, **small_it, 0, pair_index);
	if (insert_pos_it == sorted_it_list.end())
		insertList(temp_list, temp_list.end(), *small_it, size);
	else
		insertList(temp_list, *insert_pos_it, *small_it, size);
}

void PmergeMe::updateSortedIterators(std::list<std::list<int>::iterator>& sorted_its,
	std::list<int>& temp_list, size_t size)
{
	for (size_t i = 0; i < temp_list.size() - 1; i = i + size)
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
	it--;
}

PmergeMe::invalidArgumentPmergeMeException::invalidArgumentPmergeMeException(const std::string& msg)
	: std::invalid_argument(msg) {};
