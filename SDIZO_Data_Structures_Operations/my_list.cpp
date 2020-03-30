#include "my_list.h"
#include <iostream>
#include "ds_exception.h"

my_list::my_list()
{
	head_ = nullptr;
	tail_ = nullptr;
}

my_list::my_list(int value)
{
	init(value);
}

my_list::my_list(int* tab, int size)
{
	for(int i=0; i< size; i++)
	{
		push_back(tab[i]);
	}
}

my_list::~my_list()
{
	while(tail_ != nullptr)
	{
		pop_back();
	}
}


void my_list::push_front(int value) 
{
	if (is_empty())
	{
		init(value);
		return;
	}

	head_->prev = new list_element{ value, head_, nullptr };
	head_ = head_->prev;
}

void my_list::push_back(int value)
{
	if(is_empty())
	{
		init(value);
		return;
	}

	tail_->next = new list_element{ value, nullptr, tail_ };
	tail_ = tail_->next;
}

void my_list::insert_at(int index, int value)
{
	if(index > list_size())
	{
		throw ds_exception("Podany indeks wykracza poza długość listy");
	}

	if (is_empty() || index == 0)
	{
		push_front(value);
		return;
	}

	if(index == list_size())
	{
		push_back(value);
		return;
	}

	int position = 0;
	list_element* current = head_;
	while(position < index-1)
	{
		current = current->next;
		position++;
	}

	list_element* temp = current->next;
	current->next = new list_element{ value, temp, current };
	temp->prev = current->next;

}

int my_list::pop_front()
{
	if(is_empty())
	{
		throw ds_exception("Lista jest pusta");
	}

	int value = head_->value;

	if(head_->next == nullptr)
	{
		delete head_;
		head_ = nullptr;
	}else
	{
		head_ = head_->next;
		delete head_->prev;
		head_->prev = nullptr;
	}

	return value;
}

int my_list::pop_back()
{
	if (is_empty())
	{
		throw ds_exception("Lista jest pusta");
	}

	int value = head_->value;

	if (tail_->prev == nullptr)
	{
		delete tail_;
		tail_ = nullptr;
	}
	else
	{
		tail_ = tail_->prev;
		delete tail_->next;
		tail_->next = nullptr;
	}

	return value;
}

int my_list::remove_at(int index)
{
	if(is_empty())
	{
		throw ds_exception("Lista jest pusta");
	}

	if(index < 0 || index >= list_size())
	{
		throw ds_exception("Podany indeks wykracza poza długość listy");
	}

	if (index == 0)
	{
		return pop_front();
	}

	if (index == list_size()-1)
	{
		return pop_back();
	}

	int position = 0;
	list_element* current = head_;
	while (position < index - 1)
	{
		current = current->next;
		position++;
	}

	int value = current->next->value;

	list_element* temp = current->next;
	current->next = temp->next;
	temp->next->prev = current;
	delete temp;
	
	return value;
}

bool my_list::contains(int value) const
{
	if (is_empty())
	{
		return false;
	}

	list_element* current = head_;
	while(current != nullptr)
	{
		if (current->value == value)
		{
			return true;
		}
		current = current->next;
	}
	return false;
}

int my_list::list_size() const
{
	int s = 0;
	if(head_ == nullptr)
	{
		return s;
	}

	list_element* temp = head_;
	do 
	{
		s++;
		temp = temp->next;
	} while (temp != nullptr);

	return s;
}

bool my_list::is_empty() const
{
	return (head_ == nullptr);
}

void my_list::init(int value)
{
	head_ = new list_element{ value, nullptr, nullptr };
	tail_ = head_;
}

void my_list::print() const
{
	if (is_empty())
	{
		std::cout << "Lista pusta" << std::endl;
		return;
	}

	list_element* temp = head_;
	while (temp != nullptr)
	{
		std::cout << temp->value << ", ";
		temp = temp->next;
	}
	std::cout << std::endl;

	delete temp;
}

void my_list::print_reverse() const
{
	if (is_empty())
	{
		std::cout << "Lista pusta" << std::endl;
		return;
	}

	list_element* temp = tail_;
	while (temp != nullptr)
	{
		std::cout << temp->value << ", ";
		temp = temp->prev;
	}
	std::cout << std::endl;

	delete temp;
}