/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:16:58 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/12 01:09:43 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void	PmergeMe::addElementToContainers(int num)
{
	this->_list.push_back(num);
	this->_deque.push_back(num);
}

void	PmergeMe::generateContainers(char **argv)
{
	for (size_t i = 1; argv[i]; ++i)
	{
		char *end;
		int num = std::strtol(argv[i], &end, 10);
		if (*end != '\0')
			throw std::invalid_argument("Error");
		if (num <= 0)
			throw std::invalid_argument("Error");
		if (num > INT_MAX)
			throw std::invalid_argument("Error");
		addElementToContainers(num);
	}
}

void	PmergeMe::printConditions(const std::string &str)
{
	std::cout << str;
	for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printConditionsDeque(const std::string &str)
{
	std::cout << str;
	for (std::deque<int>::iterator it = this->_deque.begin(); it != this->_deque.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printTimes()
{
	std::cout << "Time to process a range of " << this->_list.size()
			  << " elements with std::list  : " << this->_elapsedTimeList << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_deque.size()
			  << " elements with std::deque : " << this->_elapsedTimeDeque << " us" << std::endl;
}

// Process of std::list

void	PmergeMe::processList()
{
	std::clock_t start = std::clock();
	sortList(1);
	std::clock_t end = std::clock();
	this->_elapsedTimeList = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void	PmergeMe::sortList(size_t size)
{
	if (size * 2 > this->_list.size())
		return ;
	size_t	j = 0;
	size_t	k = 0;
	for (size_t i = size - 1; i < this->_list.size(); i = i + size * 2)
	{
		if (i + size > this->_list.size() - 1)
		{
			if (j != 0)
				k = i;
			break ;
		}
		std::list<int>::iterator	it1 = this->_list.begin();
		std::list<int>::iterator	it2 = this->_list.begin();
		std::advance(it1, i);
		std::advance(it2, i + size);
		if (*it1 > *it2)
			listSwap(it1, it2, size);
		j++;
	}
	sortList(size * 2);
	if (j == 1)
		return ;
	std::list<std::list<int>::iterator>	iterList;
	std::list<int>::iterator it = this->_list.begin();
	std::advance(it, size - 1);
	iterList.push_back(it);
	for (size_t i = size * 2 - 1; i < this->_list.size(); i = i + size * 2)
	{
		if (k != 0 && i == k)
			break ;
		it = this->_list.begin();
		std::advance(it, i);
		iterList.push_back(it);
	}
	if (k != 0)
	{
		it = this->_list.begin();
		std::advance(it, k);
		insertIteratorToList(iterList, it);
	}
	for (size_t i = size * 3 - 1; i < this->_list.size(); i = i + size * 2)
	{
		if (k != 0 && i == k)
			break ;
		it = this->_list.begin();
		std::advance(it, i);
		insertIteratorToList(iterList, it);
	}
	updateList(iterList, size);
}

void	PmergeMe::listSwap(std::list<int>::iterator it1, std::list<int>::iterator it2, size_t size)
{
	for (size_t k = 0; k < size; ++k) {
		std::iter_swap(it1, it2);
		it1--;
		it2--;
	}
}

void	PmergeMe::pushToList(std::list<int> &newList, std::list<int>::iterator &it, size_t size)
{
	std::advance(it, 1 - size);
	for (size_t i = 0; i < size; i++)
	{
		newList.push_back(*it);
		it++;
	}
}

void	PmergeMe::updateList(std::list<std::list<int>::iterator> &iterList, size_t size)
{
	std::list<int>	tmp;
	std::list<std::list<int>::iterator>::iterator it1 = iterList.begin();
	std::list<std::list<int>::iterator>::iterator it2 = iterList.end();
	for (; it1 != it2; it1++)
	{
		pushToList(tmp, *it1, size);
	}
	std::list<int>::iterator it = this->_list.begin();
	for (std::advance(it, size * iterList.size()); it != this->_list.end(); it++)
	{
		if (it == this->_list.end())
			break ;
		tmp.push_back(*it);
	}
	this->_list = tmp;
}

void	PmergeMe::insertIteratorToList(std::list<std::list<int>::iterator> &iterList, std::list<int>::iterator it)
{
	std::list<std::list<int>::iterator>::iterator low = iterList.begin();
	std::list<std::list<int>::iterator>::iterator high = iterList.end();

	while (std::distance(low, high) > 0) {
		std::list<std::list<int>::iterator>::iterator mid = low;
		std::advance(mid, std::distance(low, high) / 2);

		if (**mid < *it) {
			low = ++mid;
		} else {
			high = mid;
		}
	}

	iterList.insert(low, it);
}

// Process of std::deque

void	PmergeMe::processDeque()
{
	
	std::clock_t start = std::clock();
	sortDeque(1);
	std::clock_t end = std::clock();
	this->_elapsedTimeDeque = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
}

void	PmergeMe::sortDeque(size_t size)
{
	if (size * 2 > this->_deque.size())
		return ;
	size_t	j = 0;
	size_t	k = 0;
	for (size_t i = size - 1; i < this->_deque.size(); i = i + size * 2)
	{
		if (i + size > this->_deque.size() - 1)
		{
			if (j != 0)
				k = i;
			break ;
		}
		std::deque<int>::iterator	it1 = this->_deque.begin();
		std::deque<int>::iterator	it2 = this->_deque.begin();
		std::advance(it1, i);
		std::advance(it2, i + size);
		if (*it1 > *it2)
			dequeSwap(it1, it2, size);
		j++;
	}
	sortDeque(size * 2);
	if (j == 1)
		return ;
	std::deque<std::deque<int>::iterator>	iterDeque;
	std::deque<int>::iterator it = this->_deque.begin();
	std::advance(it, size - 1);
	iterDeque.push_back(it);
	for (size_t i = size * 2 - 1; i < this->_deque.size(); i = i + size * 2)
	{
		if (k != 0 && i == k)
			break ;
		it = this->_deque.begin();
		std::advance(it, i);
		iterDeque.push_back(it);
	}
	if (k != 0)
	{
		it = this->_deque.begin();
		std::advance(it, k);
		insertIteratorToDeque(iterDeque, it);
	}
	for (size_t i = size * 3 - 1; i < this->_deque.size(); i = i + size * 2)
	{
		if (k != 0 && i == k)
			break ;
		it = this->_deque.begin();
		std::advance(it, i);
		insertIteratorToDeque(iterDeque, it);
	}
	updateDeque(iterDeque, size);
}

void	PmergeMe::dequeSwap(std::deque<int>::iterator it1, std::deque<int>::iterator it2, size_t size)
{
	for (size_t k = 0; k < size; ++k) {
		std::iter_swap(it1, it2);
		it1--;
		it2--;
	}
}

void	PmergeMe::insertIteratorToDeque(std::deque<std::deque<int>::iterator> &iterDeque, std::deque<int>::iterator it)
{
	std::deque<std::deque<int>::iterator>::iterator low = iterDeque.begin();
	std::deque<std::deque<int>::iterator>::iterator high = iterDeque.end();

	while (std::distance(low, high) > 0) {
		std::deque<std::deque<int>::iterator>::iterator mid = low;
		std::advance(mid, std::distance(low, high) / 2);

		if (**mid < *it) {
			low = ++mid;
		} else {
			high = mid;
		}
	}

	iterDeque.insert(low, it);
}

void	PmergeMe::updateDeque(std::deque<std::deque<int>::iterator> &iterDeque, size_t size)
{
	std::deque<int>	tmp;
	std::deque<std::deque<int>::iterator>::iterator it1 = iterDeque.begin();
	std::deque<std::deque<int>::iterator>::iterator it2 = iterDeque.end();
	for (; it1 != it2; it1++)
	{
		pushToDeque(tmp, *it1, size);
	}
	std::deque<int>::iterator it = this->_deque.begin();
	for (std::advance(it, size * iterDeque.size()); it != this->_deque.end(); it++)
	{
		if (it == this->_deque.end())
			break ;
		tmp.push_back(*it);
	}
	this->_deque = tmp;
}

void	PmergeMe::pushToDeque(std::deque<int> &newDeque, std::deque<int>::iterator &it, size_t size)
{
	std::advance(it, 1 - size);
	for (size_t i = 0; i < size; i++)
	{
		newDeque.push_back(*it);
		it++;
	}
}
