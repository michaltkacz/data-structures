#include <iostream>
#include <ctime>
#include "program_manager.h"
#include "output_data_converter.h"


using namespace std;

int main()
{
	srand(unsigned int(time(nullptr)));
	program_manager* pm = new program_manager(TEST_MODE);

	switch(pm->get_program_mode())
	{
	case TEST_MODE:
	{
		pm->run_test_mode();
		output_data_converter* converter = new output_data_converter();
		converter->convert_output_data();
		delete converter;
		break;
	}
	case USER_INTERFACE_MODE:
	{
		pm->run_user_interface_mode();
		break;
	}
	default:
		break;
	}

	delete pm;
}
