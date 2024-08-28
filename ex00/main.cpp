#include "BitcoinExchange.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange b;
		b.inputFile(argv[1]);
		b.printData();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}