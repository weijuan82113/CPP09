#include "BitcoinExchange.h"

static bool canOpen(std::ifstream& fs,const std::string& fp)
{
	fs.open(fp.c_str());
	if (!fs.is_open())
		return false;
	return true;
}

static std::vector<std::string> tokenize(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = 0;

	// find delim from str[start]
	while ((end = str.find(delim, start)) != std::string::npos)
	{
		//strsub from (str, substr.length = end -start)
		tokens.push_back(str.substr(start, end - start));
		//to find next delim , set start to (end + delim's length)
		start = end + delim.size();
	}
	//store the last string
	if (start <= str.size())
		tokens.push_back(str.substr(start));
	return tokens;
}

static void printTokens(std::vector<std::string> tokens)
{
	for (size_t i = 0; i < tokens.size(); i++)
		std::cout << "tokens[" << i << "]: " << tokens[i] << std::endl;

}

void BitcoinExchange::loadDatabase()
{
	

}


