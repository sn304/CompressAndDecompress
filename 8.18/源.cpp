#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<memory>
#include<queue>
#include<bitset>
#include<cmath>
#include<stack>
//活动调度问题的递归写法
struct activity
{
	int start;
	int finish;
};
bool operator< (activity a, activity b) {
	if (a.finish < b.finish)
		return true;
	else
		return false;
}
std::vector<activity> GREEDY_ACTIVITY_SELECT(std::vector<activity> &activities) {
	std::sort(activities.begin(), activities.end())  ;
	std::vector<activity> reasult;
	reasult.push_back(activities[0]);
	int f = activities[0].finish;
	for (auto x = activities.begin() + 1; x != activities.end(); x++)
	{
		if ((*x).start >= f)
		{
			reasult.push_back(*x);
			f = (*x).finish;
		}
	}
	return reasult;
}
void COMPRESS_HUFFMAN(const std::string& address, const std::string&story_address, std::map <std::string, int>& statistics);
std::map<std::string, int> STATISTICS_WORD(const std::string& address);
void DECOMPRESS_HUFFMAN(std::string address, std::string story_address);
//HUFFMAN算法的应用
		 int main() {
		 COMPRESS_HUFFMAN("g://sun.txt","g://csun.txt" ,STATISTICS_WORD("g://sun.txt"));
			 DECOMPRESS_HUFFMAN("g://csun.txt", "g://asun.txt");
		 }