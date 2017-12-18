#include<queue>
#include<memory>
#include"HUFFMAN_TREE_NODE.h"
#include<map>
#include<fstream>
#include<iostream>
#include<bitset>
void DECOMPRESS_HUFFMAN(std::string address, std::string story_address) {
	std::fstream in(address, std::ios::binary | std::ios::in);
	std::fstream out(story_address);
	std::map<std::string, std::string> map;
	int map_count;
	in.read((char*)(&map_count), sizeof(int));//读取map大小
	unsigned long* bin_to_ten = new unsigned long[map_count] {0};
	unsigned char * the_len_of_code = new unsigned char[map_count] {0};
	unsigned char * the_len_of_string = new unsigned char[map_count] {0};
	in.read((char *)(bin_to_ten), map_count * sizeof(unsigned long));
	in.read((char *)(the_len_of_code), map_count * sizeof(unsigned char));
	in.read((char *)(the_len_of_string), map_count * sizeof(unsigned char));
	std::vector<std::string> vec_of_string;
	for (int i = 0; i != map_count; i++)
	{
		char *string = new char[the_len_of_string[i] + 1];
		in.read(string, 1 + the_len_of_string[i]);
		vec_of_string.push_back(string);
		delete[] string;
	}
	for (int i = 0; i != map_count; i++)
	{
		std::string tem = "";
		std::bitset<32>bit(bin_to_ten[i]);
		for (int x = the_len_of_code[i] - 1; x != -1; x--)
		{
			if (bit[x] == 1)
				tem = tem + "1";
			else
				tem = tem + "0";
		}
		map[tem] = vec_of_string[i];
	}
	int count_imformation;
	in.read((char *)(&count_imformation), sizeof(int));//读取imformation数组的大小
	unsigned char * IM = new unsigned char[count_imformation] {0};
	unsigned long * By = new unsigned long[count_imformation] {0};
	in.read((char *)(IM), count_imformation * sizeof(unsigned char));
	in.read((char *)(By), count_imformation * sizeof(unsigned long));
	constexpr int size = sizeof(unsigned long) * 8;
	for (int x = 0; x != count_imformation;) {
		unsigned long byte = By[x];
		std::bitset<size> bit(byte);

		std::string buff_code;
		for (int i = size - 1; i != IM[x] - 2; i--)
		{

			if (map.find(buff_code) == map.end())
			{
				if (bit[i] == 0)
					buff_code += "0";
				else
					buff_code += "1";
				if (i == 0)
				{
					out << map[buff_code] << " ";
				}

			}
			else if (i >= 0) {
				out << map[buff_code] << " ";
				if (bit[i] == 0)
					buff_code = "0";
				else
					buff_code = "1";
			}
		}

		x++;
	}

	delete[] bin_to_ten;
	delete[] the_len_of_string;
	delete[] IM;
	delete[] By;
}