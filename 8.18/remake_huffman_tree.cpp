#include<string>
#include<map>
#include"HUFFMAN_TREE_NODE.h"
#include<queue>
void remake_huffman_tree(std::map<std::string, std::string> &map, std::shared_ptr<remake_tree> tree) {
	std::queue<std::shared_ptr<remake_tree>> queue;
	tree->word = "";
	auto x = tree;
	queue.push(tree);
	while (!queue.empty())
	{
		x = queue.front();
		if (map.find(x->word) == map.end())
		{
			tree->left = std::make_shared<remake_tree>();
			tree->left->word = tree->word + "0";
			tree->right = std::make_shared<remake_tree>();
			tree->right->word = tree->word + "1";
			queue.pop();
			queue.push(tree->left);
			queue.push(tree->right);
		}
		else
		{
			x->word = map[x->word];
			queue.pop();
		}
	}
}
