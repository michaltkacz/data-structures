#pragma once
#include <string>

class output_data_converter
{
public:
	output_data_converter();
	~output_data_converter();
	void convert_output_data();

private:
	int data_sizes_size_;
	int* data_sizes_;

	std::string output_path_;
	std::string my_array_path_;
	std::string my_list_path_;
	std::string my_heap_path_;
	std::string my_rbtree_path_;

	std::string final_output_;

	void read_from_file(std::string file);
	void write_final_output_to_file();

};
