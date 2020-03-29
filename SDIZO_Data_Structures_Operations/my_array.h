#pragma once

class my_array
{
public:
	my_array(int* tab, int size);
	my_array();
	~my_array();

	void push_back(int n);
	void push_front(int n);
	void insert_at(int index, int n);

	int pop_back();
	int pop_front();
	int remove_at(int index);

	int back() const;
	int front() const;
	int at(int index) const;

	bool contains(int value) const;
	
	void clear();

	int size() const;
	bool is_empty() const;
	
	void print() const;

private:
	int size_ = 0;
	int* tab_ = nullptr;
};
