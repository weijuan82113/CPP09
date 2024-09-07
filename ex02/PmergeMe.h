#ifndef PMERGEME_H_
 #define PMERGEME_H_

#include <iostream>
#include <list>
#include <limits>
#include <cstdlib>
#include <algorithm> //for std::swap
#include <cmath> // for std::pow
#include <deque>
#include <ctime> // for std::clock;

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();

		//------ utils -------
		void printList();
		void printList(std::list<int>& list);
		void printItList(std::list<std::list<int>::iterator>& itList);
		void printListTime();

		void printDeque();
		void printDeque(std::deque<int>& deque);
		void printItDeque(std::deque<std::deque<int>::iterator>& itDeque);
		void printDequeTime();
		//------- utils -------

		void validateInputArgument(char** argv);
		void createContainer(int integer);

		//------- List -------
		void startSortList();
		void mergeInsertList(size_t size);
		void insertSortedList(std::list<int>& temp_sorted_list,
			std::list<std::list<int>::iterator>& big_it_list,
			std::list<std::list<int>::iterator>& small_it_list,
			size_t size);
		void updateList(std::list<int>& temp_sorted_list);
		void pushBackList(std::list<int>& temp_list,
			std::list<int>::iterator it,
			size_t size);
		void updateSortedIteratorsList(std::list<std::list<int>::iterator>& sorted_its, std::list<int>& temp_list, size_t size);
		void binaryInsertList(std::list<int>& temp_list,
			std::list<std::list<int>::iterator>::iterator small_it, size_t size);
		std::list<std::list<int>::iterator>::iterator binarySearchList(std::list<std::list<int>::iterator>& it_list,
			int item, int low, int high);
		int countPairIndexList(std::list<std::list<int>::iterator>& sorted_it_list,
			std::list<std::list<int>::iterator>::iterator small_it, size_t size);
		void insertList(std::list<int>& list ,std::list<int>::iterator pos_it, std::list<int>::iterator insert_it, size_t size);
		//------- List -------

		//------- Deque -------

		void startSortDeque();
		void mergeInsertDeque(size_t size);
		void insertSortedDeque(std::deque<int>& temp_sorted_deque,
			std::deque<std::deque<int>::iterator>& big_it_deque,
			std::deque<std::deque<int>::iterator>& small_it_deque,
			size_t size);

		void pushBackDeque(std::deque<int>& temp_deque, std::deque<int>::iterator it, size_t size);
		void binaryInsertDeque(std::deque<int>& temp_deque,
			std::deque<std::deque<int>::iterator>::iterator small_it, size_t size);
		void updateSortedIteratorsDeque(std::deque<std::deque<int>::iterator>& sorted_its,
			std::deque<int>& temp_list, size_t size);
		int countPairIndexDeque(std::deque<std::deque<int>::iterator>& sorted_it_list,
			std::deque<std::deque<int>::iterator>::iterator small_it, size_t size);
		std::deque<std::deque<int>::iterator>::iterator binarySearchDeque(std::deque<std::deque<int>::iterator>& it_list,
			int item, int low_index, int high_index);
		void insertDeque(std::deque<int>&deque, std::deque<int>::iterator pos,
			std::deque<int>::iterator insert_it, size_t size);
		void updateDeque(std::deque<int>& temp_sorted_deque);


		//------- Deque -------


		class invalidArgumentPmergeMeException : public std::invalid_argument
		{
			public:
				invalidArgumentPmergeMeException(const std::string &msg);
		};

	private:
		std::list<int> list_;
		std::deque<int> deque_;
		double list_time_;
		double deque_time_;
};

template <typename InputIterator>
void impl_advance(InputIterator& it,
 typename std::iterator_traits<InputIterator>::difference_type n,
 std::input_iterator_tag)
{
	if (n > 0)
	{
		while (n--)
			++it;
	}
	else
	{
		while (n++)
			--it;
	}
};

// Main advance function
template <typename InputIterator, typename Distance>
void ft_advance(InputIterator& it, Distance n)
{
	impl_advance(it, n,
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