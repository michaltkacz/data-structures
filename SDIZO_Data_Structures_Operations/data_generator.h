#pragma once
#include <cstdlib>

class data_generator
{
public:
	data_generator();
	data_generator(int min, int max);

	int* generate_set(const int size) const;
	int generate_value() const;
	int generate_value(int min, int max) const;

private:
	int min_;
	int max_;
};
