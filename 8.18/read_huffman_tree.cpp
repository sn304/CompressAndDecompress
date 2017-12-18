#include"HUFFMAN_TREE_NODE.h"
#include<map>
void read_huffman_tree(std::shared_ptr<HUFFMAN_TREE_NODE> tree, std::map<std::string, std::string>& reasult, std::string code = "") {
	if (tree->left) {
		read_huffman_tree(tree->left, reasult, code + "0");
		read_huffman_tree(tree->right, reasult, code + "1");
	}
	else
	{
		reasult.emplace(tree->word, code);
		return;
	}
}