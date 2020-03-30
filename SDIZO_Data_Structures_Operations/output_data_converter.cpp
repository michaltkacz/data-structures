#include "output_data_converter.h"
#include <iostream>
#include <fstream>

output_data_converter::output_data_converter()
{
	output_path_ = "test_output/converted_data_output.txt";
	my_array_path_ = "test_output/my_array/myarray";
	my_list_path_ = "test_output/my_list/mylist";
	my_heap_path_ = "test_output/my_heap/myheap";
	my_rbtree_path_ = "test_output/my_rbtree/myrbtree";

	final_output_ = "";

	data_sizes_size_ = 10;
	data_sizes_= new int[data_sizes_size_]{ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 };
}

output_data_converter::~output_data_converter()
{
	delete[] data_sizes_;
}

void output_data_converter::convert_output_data()
{
	final_output_.append("my_array\n");
	read_from_file(my_array_path_);
	final_output_.append("my_list\n");
	read_from_file(my_list_path_);
	final_output_.append("my_heap\n");
	read_from_file(my_heap_path_);
	final_output_.append("my_rbtree\n");
	read_from_file(my_rbtree_path_);

	write_final_output_to_file();
}

void output_data_converter::read_from_file(std::string filename_begin)
{
	std::string read_value = "";
	for (int i = 0; i < data_sizes_size_; i++)
	{
		std::string filename_end = std::to_string(data_sizes_[i]) + ".txt";
		std::string full_file_pathname = filename_begin + filename_end;
		std::ifstream fin(full_file_pathname, std::ios::in);
		if (fin.is_open())
		{
			final_output_.append(std::to_string(data_sizes_[i]));
			while (true)
			{
				fin >> read_value;
				if(fin.eof())
				{
					break;
				}

				final_output_.append(";" + read_value);
			}
		}
		fin.close();
		final_output_.append("\n");
	}
	final_output_.append("\n");
}

void output_data_converter::write_final_output_to_file()
{
	std::ofstream fout(output_path_, std::ios::out);
	if (fout.is_open())
	{
		fout << final_output_;
	}
	fout.close();
}
