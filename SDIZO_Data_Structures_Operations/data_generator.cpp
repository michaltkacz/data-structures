#include "data_generator.h"


data_generator::data_generator()
{
	min_ = 0;
	max_ = 100000;
}

data_generator::data_generator(int min, int max)
{
	min_ = min;
	max_ = max;
}

int* data_generator::generate_set(const int size) const
{
	int* tab = new int[size];
	for(int i=0; i<size; i++)
	{
		tab[i] = generate_value();
	}
	return tab;
}

int data_generator::generate_value() const
{
	return (rand() % (max_ - min_)) + min_;
}


int data_generator::generate_value(int min, int max) const
{
	return (rand() % (max - min)) + min;
}