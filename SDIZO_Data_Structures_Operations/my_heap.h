#pragma once
#include <string>

class my_heap
{
public:
	my_heap(int* tab, int size);
	~my_heap();


	void push_heap(int value);
	int pop_heap();

	int top() const;

	bool contains(int value) const;
	bool is_empty() const;

	void print_array() const;
	void print_levels() const;
	void print_tree() const;

private:
	int* tab_;
	int size_;

	void print_tree_(std::string sp, std::string sn, int index) const;

	int parent_index(int child_index) const;
	int left_child_index(int parent_index) const;
	int right_child_index(int parent_index) const;

	void build_heap();
	void heap_fix_down(int p_index);
	void heap_fix_up(int c_index);

	bool search(int value, int index) const;

	std::string cr = "  ";
	std::string cl = "  ";
	std::string cp = "  ";
};
