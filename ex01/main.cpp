#include "RPN.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: no expresson." << std::endl;
		return 1;
	}
	try
	{
		RPN rpn(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}