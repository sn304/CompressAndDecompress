#include<queue>
#include<memory>
#include"HUFFMAN_TREE_NODE.h"
#include<map>
#include<fstream>
#include<iostream>
#include<bitset>
void read_huffman_tree(std::shared_ptr<HUFFMAN_TREE_NODE> tree, std::map<std::string, std::string>& reasult, std::string code = "");
void COMPRESS_HUFFMAN(const std::string& address, const std::string&story_address, std::map <std::string, int>& statistics)
{
	std::priority_queue<std::shared_ptr<HUFFMAN_TREE_NODE>> Q;
	for (auto p = statistics.begin(); p != statistics.end(); p++)
	{
		auto ptr = std::make_shared<HUFFMAN_TREE_NODE>(p->first, p->second);
		Q.push(ptr);
	}
	for (int i = 1; i != statistics.size(); i++)
	{
		auto lhs = Q.top();
		Q.pop();
		auto rhs = Q.top();
		Q.pop();
		auto new_node = std::make_shared<HUFFMAN_TREE_NODE>((*lhs).times + (*rhs).times);
		new_node->left = lhs;
		new_node->right = rhs;
		lhs->parent = new_node;
		rhs->parent = new_node;
		Q.push(new_node);
	}
	std::map<std::string, std::string> reasult;
	read_huffman_tree(Q.top(), reasult);
	std::fstream in(address);
	if (in)
		std::cout << "in opened" << std::endl;
	std::fstream out(story_address, std::ios::binary | std::ios::out);//要做文件未打开的防范
	if (out)
		std::cout << "out opened" << std::endl;
	std::vector<unsigned char> imfomation;
	std::vector<unsigned long> byte_vec;
	unsigned long byte = 0;
	int size = sizeof(unsigned long) * 8;
	int use = 0;
	int rest = size;
	while (in) {
		std::string word;
		in >> word;
		std::bitset<32> binary(reasult[word]);
		int count_bit = reasult[word].size();
		int num = binary.to_ulong();
		if (rest >= count_bit) {
			byte = byte + (num << (rest - count_bit));
			use = use + count_bit;
			rest = rest - count_bit;
		}
		else {
			byte_vec.push_back(byte);
			imfomation.push_back(rest);
			byte = num << (size - count_bit);
			use = count_bit;
			rest = size - count_bit;

		}
	}
	reasult.erase("");
	int map_count = reasult.size();
	out.write((char*)(&map_count), sizeof(int));            //压缩文件第一个数是生成huffman树的map的大小
	unsigned long* bin_to_ten = new unsigned long[map_count] {0};
	unsigned char * the_len_of_code = new unsigned char[map_count] {0};//全都是为了code
	unsigned char * the_len_of_string = new unsigned char[map_count] {0};
	int t = 0;
	for (auto &a : reasult)
	{
		std::bitset<32>bit(a.second);
		int i = a.second.size() - 1;
		for (;; i--)
			if (i == 0 || bit[i] == 1)
				break;
		bin_to_ten[t] = bit.to_ulong();
		the_len_of_code[t] = a.second.size();
		t++;
	}

	out.write((char *)(bin_to_ten), map_count * sizeof(unsigned long));
	out.write((char *)(the_len_of_code), map_count * sizeof(unsigned char));
	int i = 0;
	for (auto &a : reasult)
	{
		the_len_of_string[i] = a.first.size();
		i++;
	}
	out.write((char*)(the_len_of_string), map_count * sizeof(unsigned char));

	for (auto &a : reasult) {
		out.write((char*)(a.first.c_str()), (1 + a.first.size()) * sizeof(unsigned char));///
	}

	int count_imformation = imfomation.size(); //读完map后读取long_byte的数目
	out.write((char *)(&count_imformation), sizeof(int));
	unsigned char * IM = new unsigned char[count_imformation] {0};
	unsigned long * By = new unsigned long[count_imformation] {0};
	for (int i = 0; i != imfomation.size(); i++)
		IM[i] = imfomation[i];
	for (int i = 0; i != imfomation.size(); i++)
		By[i] = byte_vec[i];
	out.write((char *)(IM), count_imformation * sizeof(unsigned char));
	out.write((char *)(By), count_imformation * sizeof(unsigned long));
	delete[] bin_to_ten;
	delete[] the_len_of_string;
	delete[] IM;
	delete[] By;
}