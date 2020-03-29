#pragma once
#include <iostream>
#include "ds_exception.h"

class my_list
{
public:
	my_list();
	my_list(int value);
	my_list(int* tab, int size);
	~my_list();
	
	void push_front(int value);
	void push_back(int value);
	void insert_at(int index, int value);
	
	int pop_front();
	int pop_back();
	int remove_at(int index);

	bool contains(int value) const;

	int list_size() const;
	bool is_empty() const;

	void print() const;
	void print_reverse() const;

private:
	struct list_element
	{
		int value = 0;
		list_element* next = nullptr;
		list_element* prev = nullptr;
	};

	list_element* head_ = nullptr;
	list_element* tail_ = nullptr;

	void init(int value);
};
