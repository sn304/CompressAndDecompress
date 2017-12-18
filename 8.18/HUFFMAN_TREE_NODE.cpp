#include"HUFFMAN_TREE_NODE.h"
bool operator<(std::shared_ptr<HUFFMAN_TREE_NODE> l, std::shared_ptr<HUFFMAN_TREE_NODE> r) {
	if ((*l).times <= (*r).times)
		return false;
	else
		return true;
}