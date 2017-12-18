#ifndef __HUFFMAN_TREE_NODE__ 
#define __HUFFMAN_TREE_NODE__ 
#include<memory>
#include<string>
struct HUFFMAN_TREE_NODE {
	HUFFMAN_TREE_NODE(std::string s, int t) :word(s), times(t) {}
	HUFFMAN_TREE_NODE(int t) :times(t) {}
	HUFFMAN_TREE_NODE(const HUFFMAN_TREE_NODE& other) = default;
	HUFFMAN_TREE_NODE() = default;
	std::string word;
	int times;
	std::shared_ptr<HUFFMAN_TREE_NODE> parent;
	std::shared_ptr<HUFFMAN_TREE_NODE> left;
	std::shared_ptr<HUFFMAN_TREE_NODE> right;
};
bool operator<(std::shared_ptr<HUFFMAN_TREE_NODE> l, std::shared_ptr<HUFFMAN_TREE_NODE> r);
struct remake_tree {
	std::shared_ptr<remake_tree> left;
	std::shared_ptr<remake_tree>right;
	std::string word;
};
#endif // !__HUFFMAN_TREE_NODE__ 
