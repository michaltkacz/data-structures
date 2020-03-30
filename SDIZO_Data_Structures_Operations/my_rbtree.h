#pragma once
#include <string>

class my_rbtree
{
public:
	my_rbtree();
	my_rbtree(int* tab, int size);
	~my_rbtree();

	void insert(int value);
	void remove(int value);
	bool contains(int value) const;

	void print_tree() const;

private:
	struct node
	{
		node* parent;
		node* left;
		node* right;
		int key;
		char color;
	};

	node* nil_;
	node* root_;

	void print_tree_(std::string sp, std::string sn, node* n) const;

	void delete_subtree(node* p);
	void rotate_left(node* a);
	void rotate_right(node* a);

	node* find_min(node* p) const;
	node* find_successor(node* p) const;
	node* find_node(int value) const;

	std::string cr = "  ";
	std::string cl = "  ";
	std::string cp = "  ";

};
