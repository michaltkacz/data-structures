#include "my_heap.h"
#include <algorithm>
#include <iostream>
#include "ds_exception.h"


#pragma warning(push)
#pragma warning(disable : 4309)
my_heap::my_heap(int* tab, int size)
{
	size_ = size;
	tab_ = new int[size_];
	std::copy(tab, tab + size, tab_);
	
	cr[0] = 218;
	cr[1] = 196;
	cl[0] = 192;
	cl[1] = 196;
	cp[0] = 179;

	build_heap();
}
#pragma warning(pop)

my_heap::~my_heap()
{
	delete[] tab_;
}

void my_heap::push_heap(int value)
{
	if(is_empty())
	{
		size_ = 1;
		tab_ = new int[size_];
		tab_[size_ - 1] = value;
		return;
	}

	const int new_size = size_ + 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + size_, temp);

	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	tab_[size_ - 1] = value;

	heap_fix_up(size_-1);
}

int my_heap::pop_heap()
{
	if (is_empty())
	{
		throw ds_exception("Kopiec jest pusty");
	}

	int value = tab_[0];

	if(size_ == 1)
	{
		size_ = 0;
		delete[] tab_;
	}else
	{
		tab_[0] = tab_[size_ - 1];
		const int new_size = size_ - 1;
		int* temp = new int[new_size];
		std::copy(tab_, tab_ + new_size, temp);
		delete[] tab_;
		tab_ = temp;
		size_ = new_size;
		heap_fix_down(0);
	}

	return value;
}

int my_heap::top() const
{
	if (is_empty())
	{
		throw ds_exception("Kopiec jest pusty");
	}

	return tab_[0];
}

bool my_heap::contains(int value) const
{
	if (is_empty())
	{
		return false;
	}

	return search(value, 0);
}

bool my_heap::search(int value, int index) const
{
	if(index < 0 || index >= size_)
	{
		return false;
	}

	if(tab_[index] == value)
	{
		return true;
	}

	if(search(value, left_child_index(index)))
	{
		return true;
	}

	return search(value, right_child_index(index));
}

bool my_heap::is_empty() const
{
	return !bool(size_);
}

void my_heap::print_array() const
{
	if (is_empty())
	{
		std::cout << "Kopiec jest pusty" << std::endl;
		return;
	}

	for(int i=0; i<size_; i++)
	{
		std::cout << tab_[i] << ", ";
	}

	std::cout << std::endl;
}

void my_heap::print_levels() const
{
	if(is_empty())
	{
		std::cout << "Kopiec jest pusty" << std::endl;
		return;
	}

	int level_number = 0; // zero is the top most level
	int num_items_at_this_level = 1; // level zero has at most one item

	int num_printed_this_level = 0; // number of items printed at this level
	for(int i=0; i<size_; i++) // for each item in the heap
	{
		if (num_printed_this_level == 0) // start of a new level
			std::cout << "\nlevel #" << level_number << " : ";

		std::cout << tab_[i] << ' ';
		++num_printed_this_level;

		if (num_printed_this_level == num_items_at_this_level) // completed this level
		{
			++level_number;
			num_items_at_this_level *= 2; // next level has at most twice as many items
			num_printed_this_level = 0;
		}
	}

	std::cout << std::endl;
}


void my_heap::print_tree() const
{
	if(is_empty())
	{
		std::cout << "Kopiec jest pusty" << std::endl;
		return;
	}

	print_tree_("", "", 0);
}

void my_heap::print_tree_(std::string sp, std::string sn, int index) const
{
	if (is_empty() || index >= size_)
	{
		return;
	}

	std::string s;

	if (tab_[index])
	{
		s = sp;
		if (sn == cr) s[s.length() - 2] = ' ';
		print_tree_(s + cp, cr, right_child_index(index));

		s = s.substr(0, sp.length() - 2);
		std::cout << s << sn << tab_[index] << std::endl;

		s = sp;
		if (sn == cl) s[s.length() - 2] = ' ';
		print_tree_(s + cp, cl, left_child_index(index));
	}
}

int my_heap::parent_index(int child_index) const
{
	return int(floor((child_index-1) / 2));
}

int my_heap::left_child_index(int parent_index) const
{
	return 2 * parent_index + 1;
}

int my_heap::right_child_index(int parent_index) const
{
	return 2 * parent_index + 2;
}

void my_heap::heap_fix_up(int c_index)
{
	int p_index = parent_index(c_index);
	while (c_index > 0 && tab_[p_index] < tab_[c_index]) {
		std::swap(tab_[c_index], tab_[p_index]);
		c_index = parent_index(c_index);
	}
}

void my_heap::heap_fix_down(int p_index)
{
	int l_index = left_child_index(p_index);
	int r_index = right_child_index(p_index);
	int largest_index = p_index;

	if (l_index < size_ && tab_[l_index] > tab_[largest_index])
		largest_index = l_index;

	if (r_index < size_ && tab_[r_index] > tab_[largest_index])
		largest_index = r_index;

	if (largest_index != p_index)
	{
		std::swap(tab_[p_index], tab_[largest_index]);
		heap_fix_down(largest_index);
	}
}

void my_heap::build_heap()
{
	int parent_index = size_ / 2; 
	while (parent_index != -1) {
		heap_fix_down(parent_index);
		parent_index = parent_index - 1;
	}
}