#include "PmergeMe.h"


int main(int argc, char* argv[])
{
	if (argc < 2)
		std::cerr << "No positive integer sequence be inputed" << std::endl;
	try
	{
		PmergeMe p;
		p.validateInputArgument(++argv);
		p.mergeInsertList(1);
		std::cout << "After: ";
		p.printList();

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}




	return 0;
}