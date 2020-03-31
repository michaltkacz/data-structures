#include <iostream>
#include <ctime>
#include <conio.h>
#include "program_manager.h"
#include "output_data_converter.h"


using namespace std;

int main()
{
	srand(unsigned int(time(nullptr)));
	

	char option;
	bool run_program = false;
	program_mode run_mode = USER_INTERFACE_MODE;
	do {
		system("cls");
		cout << endl;
		cout << "==== START ===" << endl;
		cout << "1.Tryb testowania (uruchamia testowanie struktur, ukonczenie moze zajac duzo czasu)" << endl;
		cout << "2.Tryb interfejsu uzytkownika" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";
		option = _getche();
		cout << endl;

		switch (option) {
		case '1':
			run_mode = TEST_MODE;
			run_program = true;
			break;

		case '2':
			run_mode = USER_INTERFACE_MODE;
			run_program = true;
			break;
		case '0':
			return 0;
		}

	} while (!run_program);

	program_manager* pm = new program_manager(run_mode);
	 

	switch(pm->get_program_mode())
	{
	case TEST_MODE:
	{
		pm->run_test_mode();
		std::cout << " TEST " << std::endl;
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
