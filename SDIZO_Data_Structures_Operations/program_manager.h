﻿#pragma once
#include "data_generator.h"
#include <string>

enum program_mode
{
	TEST_MODE,
	USER_INTERFACE_MODE
};

class program_manager
{
public:
	program_manager();
	program_manager(program_mode p_mode);
	~program_manager();

	program_mode get_program_mode();
	void run_test_mode();
	void run_user_interface_mode();
	

private:
	program_mode program_mode_;

	void clear_file(std::string file_pathname);
};
