#include "my_array.h"
#include <algorithm>
#include <iostream>
#include "ds_exception.h"


my_array::my_array(int* tab, const int size)
{
	size_ = size;
	tab_ = new int[size_];
	std::copy(tab, tab + size, tab_);
}

my_array::my_array()
{
	size_ = 0;
	tab_ = new int[size_];
}

my_array::~my_array()
{
	delete[] tab_;
}

void my_array::push_back(const int n)
{
	const int new_size = size_ + 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + size_, temp);
	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	tab_[size_ - 1] = n;
}

void my_array::push_front(const int n)
{
	const int new_size = size_ + 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + size_, temp + 1);
	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	tab_[0] = n;
}

void my_array::insert_at(const int index, const int n)
{
	if(index > size_)
	{
		throw ds_exception("Podany indeks wykracza poza rozmiar tablicy");
	}

	if (index == size_)
	{
		push_back(n);
		return;
	}

	if (index == 0)
	{
		push_front(n);
		return;
	}

	const int new_size = size_ + 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + index, temp);
	temp[index] = n;
	std::copy(tab_ + index, tab_ + size_, temp + index + 1);
	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;
}

int my_array::pop_back()
{
	if (is_empty())
	{
		throw ds_exception("Tablica jest pusta");
	}
	
	const int value = tab_[size_ - 1];

	const int new_size = size_ - 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + new_size, temp);
	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	return value;
}

int my_array::pop_front()
{
	if (is_empty())
	{
		throw ds_exception("Tablica jest pusta");
	}

	const int value = tab_[0];

	const int new_size = size_ - 1;
	int* temp = new int[new_size];
	std::copy(tab_+1, tab_ + size_, temp);
	
	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	return value;
}

int my_array::remove_at(const int index)
{
	if (is_empty())
	{
		throw ds_exception("Tablica jest pusta");
	}

	if (index >= size_ || index < 0)
	{
		throw ds_exception("Podany indeks wykracza poza rozmiar tablicy");
	}

	if (index == size_-1)
	{
		return pop_back();
	}

	if (index == 0)
	{
		return pop_front();
	}

	const int value = tab_[index];

	const int new_size = size_ - 1;
	int* temp = new int[new_size];
	std::copy(tab_, tab_ + index, temp);
	std::copy(tab_ + index +1, tab_ + size_, temp + index);

	delete[] tab_;
	size_ = new_size;
	tab_ = temp;

	return value;
}

int my_array::back() const
{
	if (size_ <= 0)
	{
		throw ds_exception("Tablica jest pusta");
	}
	return tab_[size_ - 1];
}

int my_array::front() const
{
	if (size_ <= 0)
	{
		throw ds_exception("Tablica jest pusta");
	}
	return tab_[0];
}

int my_array::at(const int index) const
{
	if (size_ <= 0)
	{
		throw ds_exception("Tablica jest pusta");
	}

	if (index >= size_ || index < 0)
	{
		throw ds_exception("Podany indeks wykracza poza rozmiar tablicy");
	}

	return tab_[index];
}

bool my_array::contains(int value) const
{
	if (is_empty())
	{
		return false;
	}

	for(int i=0; i<size_; i++)
	{
		if (tab_[i] == value)
		{
			return true;
		}
	}

	return false;
}

void my_array::clear()
{
	delete[] tab_;
	size_ = 0;
	tab_ = new int[size_];
}

int my_array::size() const
{
	return size_;
}


bool my_array::is_empty() const
{
	return !bool(size_);
}

void my_array::print() const
{
	if(is_empty())
	{
		std::cout << "Tablica pusta" << std::endl;
		return;
	}

	for (int i = 0; i < size_; i++)
	{
		std::cout << tab_[i] << ", ";
	}
	std::cout << std::endl;
}
