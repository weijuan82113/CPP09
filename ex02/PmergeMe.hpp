/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokamura <yokamura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:29:08 by yokamura          #+#    #+#             */
/*   Updated: 2024/08/12 02:01:24 by yokamura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <algorithm>
#include <ctime>
#include <exception>
#include <stdexcept>
#include <climits>

class   PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		void    generateContainers(char **argv);
		void	printConditions(const std::string &str);
		void	printConditionsDeque(const std::string &str);
		void	printTimes();
		void	processList();
		void	processDeque();
		
	private:
		std::list<int>		_list;
		std::deque<int>		_deque;
		double				_elapsedTimeList;
		double				_elapsedTimeDeque;

		PmergeMe(const PmergeMe &other);
		PmergeMe&operator=(const PmergeMe &other);
		
		void	addElementToContainers(int num);

		void	sortList(size_t size);
		void	listSwap(std::list<int>::iterator it1, std::list<int>::iterator it2, size_t size);
		void	pushToList(std::list<int> &newList, std::list<int>::iterator &it, size_t size);
		void	insertIteratorToList(std::list<std::list<int>::iterator> &iterList, std::list<int>::iterator it);
		void	updateList(std::list<std::list<int>::iterator> &iterList, size_t size);

		void	sortDeque(size_t size);
		void	dequeSwap(std::deque<int>::iterator it1, std::deque<int>::iterator it2, size_t size);
		void	pushToDeque(std::deque<int> &newDeque, std::deque<int>::iterator &it, size_t size);
		void	insertIteratorToDeque(std::deque<std::deque<int>::iterator> &iterDeque, std::deque<int>::iterator it);
		void	updateDeque(std::deque<std::deque<int>::iterator> &iterDeque, size_t size);
};

#endif
