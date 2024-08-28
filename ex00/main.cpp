#include "BitcoinExchange.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		BitcoinExchange b();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;
}