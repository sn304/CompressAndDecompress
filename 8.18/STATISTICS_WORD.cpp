#include<map>
#include<fstream>
#include<string>
std::map<std::string, int> STATISTICS_WORD(const std::string& address)
{
	std::fstream file(address);
	std::string word;
	std::map<std::string, int> statistics;
	while (file)
	{
		file >> word;
		statistics[word]++;
	}
	return statistics;
}