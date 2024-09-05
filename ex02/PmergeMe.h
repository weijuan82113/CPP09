#ifndef PMERGEME_H_
 #define PMERGEME_H_

#include <iostream>
#include <list>
#include <limits>
#include <cstdlib>
#include <algorithm> //for std::swap

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();

		//-----utils-----
		void printList(std::list<int>& list);
		void printItList(std::list<std::list<int>::iterator>& itList);
		//-----utils-----

		void validateInputArgument(char** argv);
		void createContainer(int integer);
		void mergerInsertList(size_t size);
		void insertSortedList(std::list<int>& temp_sorted_list,
			std::list<std::list<int>::iterator>& big_it_list,
			std::list<std::list<int>::iterator>& small_it_list,
			size_t size);
		void ft_push_back(std::list<int>& temp_list,
			std::list<int>::iterator& it,
			size_t size);
		//here
		void binary_insert();


		class invalidArgumentPmergeMeException : public std::invalid_argument
		{
			public:
				invalidArgumentPmergeMeException(const std::string &msg);
		};

	private:
		std::list<int> list_;



};

template <typename InputIterator>
void implAdvance(InputIterator& it,
 typename std::iterator_traits<InputIterator>::difference_type n,
 std::input_iterator_tag)
{
	while (n > 0)
	{
		++it;
		n--;
	}
};

// Main advance function
template <typename InputIterator, typename Distance>
void ft_advance(InputIterator& it, Distance n)
{
	implAdvance(it, n,
	 typename std::iterator_traits<InputIterator>::iterator_category());
}

template <typename Iterator>
void ft_swap(Iterator it1, Iterator it2, size_t size)
{
	for (size_t i = 0; i < size; i ++)
	{
		std::swap(*it1, *it2);
		it1++;
		it2++;
	}
}

#endif