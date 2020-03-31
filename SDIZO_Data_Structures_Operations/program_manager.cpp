#include "program_manager.h"
#include <iostream>
#include "my_array.h"
#include "my_list.h"
#include "my_heap.h"
#include "my_rbtree.h"
#include "data_generator.h"
#include "time_logger.h"
#include <fstream>
#include "output_data_converter.h"
#include <conio.h>

program_manager::program_manager() : program_mode_(USER_INTERFACE_MODE)
{
}

program_manager::program_manager(program_mode p_mode)
{
	program_mode_ = p_mode;
}

program_manager::~program_manager()
{
}

program_mode program_manager::get_program_mode()
{
	return program_mode_;
}

void program_manager::run_test_mode()
{
	data_generator* dg = new data_generator();

	const int test_redo_number = 500;
	const int data_sizes_size = 20;
	const int data_sizes[data_sizes_size] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000,
											55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000};

	// time loggery dla różnych funkcji
	time_logger* tl_generate = new time_logger();
	
	time_logger* tl_push_back = new time_logger();
	time_logger* tl_push_front = new time_logger();
	time_logger* tl_insert = new time_logger();

	time_logger* tl_pop_back = new time_logger();
	time_logger* tl_pop_front = new time_logger();
	time_logger* tl_remove = new time_logger();
	
	time_logger* tl_find = new time_logger();


	// test my_array
	for (int i = 0; i < data_sizes_size; i++)
	{
		const int data_set_size = data_sizes[i];

		tl_generate->reset();
		tl_push_back->reset();
		tl_push_front->reset();
		tl_insert->reset();
		tl_pop_back->reset();
		tl_pop_front->reset();
		tl_remove->reset();
		tl_find->reset();

		for (int j = 0; j < test_redo_number; j++)
		{
			// utworzenie zestawu danych
			int* data_set = dg->generate_set(data_set_size);

			int value_push_back = dg->generate_value();
			int value_push_front = dg->generate_value();
			int value_insert = dg->generate_value();
			int insert_index = dg->generate_value(0, data_set_size);

			// czas generowania tablicy
			tl_generate->start();
			my_array* array1 = new my_array(data_set, data_set_size);
			tl_generate->stop();

			// zwolnienie pamięci tablicy pomocniczej
			delete data_set;

			// czas dodawania nowego elementu na koniec tablicy
			tl_push_back->start();
			array1->push_back(value_push_back);
			tl_push_back->stop();

			// czas dodawania nowego elementu na początek tablicy
			tl_push_front->start();
			array1->push_front(value_push_front);
			tl_push_front->stop();

			// czas wstawienia nowego elementu w środek tablicy
			tl_insert->start();
			array1->insert_at(insert_index, value_insert);
			tl_insert->stop();

			// czas wyszukiwania elementu w tablicy
			tl_find->start();
			array1->contains(value_insert);
			tl_find->stop();

			// czas usuwania elementu z końca tablicy
			tl_pop_back->start();
			array1->pop_back();
			tl_pop_back->stop();

			// czas usuwania elementu z początku tablicy
			tl_pop_front->start();
			array1->pop_front();
			tl_pop_front->stop();

			// czas usuwania elementu ze środka tablicy
			tl_remove->start();
			array1->remove_at(insert_index);
			tl_remove->stop();

			delete array1;
		}

		// średnie czasy
		std::cout << std::endl;
		std::cout << "-----Array-----" << std::endl;
		std::cout << "Redos: " << test_redo_number << std::endl;
		std::cout << "Data size: " << data_set_size << std::endl;
		std::cout << "Generate: " << tl_generate->mean() << std::endl;
		std::cout << "Push back: " << tl_push_back->mean() << std::endl;
		std::cout << "Push front: " << tl_push_front->mean() << std::endl;
		std::cout << "Insert: " << tl_insert->mean() << std::endl;
		std::cout << "Pop back: " << tl_pop_back->mean() << std::endl;
		std::cout << "Pop front: " << tl_pop_front->mean() << std::endl;
		std::cout << "Remove: " << tl_remove->mean() << std::endl;
		std::cout << "Find: " << tl_find->mean() << std::endl;
		std::cout << std::endl;

		// zapis do pliku
		std::string pathname = "test_output/my_array/myarray" + std::to_string(data_set_size) + ".txt";
		clear_file(pathname);
		tl_generate->save_to_file(pathname);
		tl_push_back->save_to_file(pathname);
		tl_push_front->save_to_file(pathname);
		tl_insert->save_to_file(pathname);
		tl_pop_back->save_to_file(pathname);
		tl_pop_front->save_to_file(pathname);
		tl_remove->save_to_file(pathname);
		tl_find->save_to_file(pathname);
	}

	
	// test my_list
	for (int i = 0; i < data_sizes_size; i++)
	{
		const int data_set_size = data_sizes[i];

		tl_generate->reset();
		tl_push_back->reset();
		tl_push_front->reset();
		tl_insert->reset();
		tl_pop_back->reset();
		tl_pop_front->reset();
		tl_remove->reset();
		tl_find->reset();

		for (int j = 0; j < test_redo_number; j++)
		{
			// utworzenie zestawu danych
			int* data_set = dg->generate_set(data_set_size);

			int value_push_back = dg->generate_value();
			int value_push_front = dg->generate_value();
			int value_insert = dg->generate_value();
			int insert_index = dg->generate_value(0, data_set_size);

			// czas generowania listy
			tl_generate->start();
			my_list* list1 = new my_list(data_set, data_set_size);
			tl_generate->stop();

			// zwolnienie pamięci tablicy pomocniczej
			delete data_set;

			// czas dodawania nowego elementu na koniec listy
			tl_push_back->start();
			list1->push_back(value_push_back);
			tl_push_back->stop();

			// czas dodawania nowego elementu na początek listy
			tl_push_front->start();
			list1->push_front(value_push_front);
			tl_push_front->stop();

			// czas wstawienia nowego elementu w środek listy
			tl_insert->start();
			list1->insert_at(insert_index, value_insert);
			tl_insert->stop();

			// czas wyszukiwania elementu w liście
			tl_find->start();
			list1->contains(value_insert);
			tl_find->stop();

			// czas usuwania elementu z końca listy
			tl_pop_back->start();
			list1->pop_back();
			tl_pop_back->stop();

			// czas usuwania elementu z początku listy
			tl_pop_front->start();
			list1->pop_front();
			tl_pop_front->stop();

			// czas usuwania elementu ze środka listy
			tl_remove->start();
			list1->remove_at(insert_index);
			tl_remove->stop();

			delete list1;
		}

		// średnie czasy
		std::cout << std::endl;
		std::cout << "-----List-----" << std::endl;
		std::cout << "Redos: " << test_redo_number << std::endl;
		std::cout << "Data size: " << data_set_size << std::endl;
		std::cout << "Generate: " << tl_generate->mean() << std::endl;
		std::cout << "Push back: " << tl_push_back->mean() << std::endl;
		std::cout << "Push front: " << tl_push_front->mean() << std::endl;
		std::cout << "Insert: " << tl_insert->mean() << std::endl;
		std::cout << "Pop back: " << tl_pop_back->mean() << std::endl;
		std::cout << "Pop front: " << tl_pop_front->mean() << std::endl;
		std::cout << "Remove: " << tl_remove->mean() << std::endl;
		std::cout << "Find: " << tl_find->mean() << std::endl;
		std::cout << std::endl;

		// zapis do pliku
		std::string pathname = "test_output/my_list/mylist" + std::to_string(data_set_size) + ".txt";
		clear_file(pathname);
		tl_generate->save_to_file(pathname);
		tl_push_back->save_to_file(pathname);
		tl_push_front->save_to_file(pathname);
		tl_insert->save_to_file(pathname);
		tl_pop_back->save_to_file(pathname);
		tl_pop_front->save_to_file(pathname);
		tl_remove->save_to_file(pathname);
		tl_find->save_to_file(pathname);
	} 

	// te time loggery w przypadku drzew nie są potrzebne
	delete tl_push_back;
	delete tl_push_front;
	delete tl_pop_back;
	delete tl_pop_front;


	// test my_heap
	for (int i = 0; i < data_sizes_size; i++)
	{
		const int data_set_size = data_sizes[i];

		tl_generate->reset();
		tl_insert->reset();
		tl_remove->reset();
		tl_find->reset();

		for (int j = 0; j < test_redo_number; j++)
		{
			// utworzenie zestawu danych
			int* data_set = dg->generate_set(data_set_size);

			// liczba do wstawienia, znalezienia i usunięcia
			int value_insert = dg->generate_value();

			// czas generowania sterty
			tl_generate->start();
			my_heap* heap1 = new my_heap(data_set, data_set_size);
			tl_generate->stop();

			// zwolnienie pamięci tablicy pomocniczej
			delete data_set;

			// czas wstawienia nowego elementu na stertę
			tl_insert->start();
			heap1->push_heap(value_insert);
			tl_insert->stop();

			// czas wyszukiwania elementu w stercie
			tl_find->start();
			heap1->contains(value_insert);
			tl_find->stop();

			// czas usuwania elementu ze sterty
			tl_remove->start();
			heap1->pop_heap();
			tl_remove->stop();

			delete heap1;
		}

		// średnie czasy
		std::cout << std::endl;
		std::cout << "-----Heap-----" << std::endl;
		std::cout << "Redos: " << test_redo_number << std::endl;
		std::cout << "Data size: " << data_set_size << std::endl;
		std::cout << "Generate: " << tl_generate->mean() << std::endl;
		std::cout << "Insert: " << tl_insert->mean() << std::endl;
		std::cout << "Remove: " << tl_remove->mean() << std::endl;
		std::cout << "Find: " << tl_find->mean() << std::endl;
		std::cout << std::endl;

		// zapis do pliku
		std::string pathname = "test_output/my_heap/myheap" + std::to_string(data_set_size) + ".txt";
		clear_file(pathname);
		tl_generate->save_to_file(pathname);
		tl_insert->save_to_file(pathname);
		tl_remove->save_to_file(pathname);
		tl_find->save_to_file(pathname);
	}


	// test my_rbtree
	for (int i = 0; i < data_sizes_size; i++)
	{
		const int data_set_size = data_sizes[i];

		tl_generate->reset();
		tl_insert->reset();
		tl_remove->reset();
		tl_find->reset();

		for (int j = 0; j < test_redo_number; j++)
		{
			// utworzenie zestawu danych
			int* data_set = dg->generate_set(data_set_size);

			// liczba do wstawienia, znalezienia i usunięcia
			int value_insert = dg->generate_value();

			// czas generowania drzewa rb
			tl_generate->start();
			my_rbtree* rbtree1 = new my_rbtree(data_set, data_set_size);
			tl_generate->stop();

			// zwolnienie pamięci tablicy pomocniczej
			delete data_set;

			// czas wstawienia nowego elementu do drzewa rb
			tl_insert->start();
			rbtree1->insert(value_insert);
			tl_insert->stop();

			// czas wyszukiwania elementu w drzewie rb
			tl_find->start();
			rbtree1->contains(value_insert);
			tl_find->stop();

			// czas usuwania elementu z drzewa rb
			tl_remove->start();
			rbtree1->remove(value_insert);
			tl_remove->stop();

			delete rbtree1;
		}

		// średnie czasy
		std::cout << std::endl;
		std::cout << "-----RBTree-----" << std::endl;
		std::cout << "Redos: " << test_redo_number << std::endl;
		std::cout << "Data size: " << data_set_size << std::endl;
		std::cout << "Generate: " << tl_generate->mean() << std::endl;
		std::cout << "Insert: " << tl_insert->mean() << std::endl;
		std::cout << "Remove: " << tl_remove->mean() << std::endl;
		std::cout << "Find: " << tl_find->mean() << std::endl;
		std::cout << std::endl;

		// zapis do pliku
		std::string pathname = "test_output/my_rbtree/myrbtree" + std::to_string(data_set_size) + ".txt";
		clear_file(pathname);
		tl_generate->save_to_file(pathname);
		tl_insert->save_to_file(pathname);
		tl_remove->save_to_file(pathname);
		tl_find->save_to_file(pathname);
	}

	delete dg;
	delete tl_generate;
	delete tl_insert;
	delete tl_remove;	
	delete tl_find;

	output_data_converter* converter = new output_data_converter();
	converter->convert_output_data();
	delete converter;
}

void program_manager::clear_file(std::string file_pathname)
{
	std::ofstream fout(file_pathname, std::ofstream::out | std::ofstream::trunc);
	fout.close();
}

void program_manager::run_user_interface_mode()
{
	char option;
	do {
		system("cls");
		std::cout << std::endl;
		std::cout << "==== MENU GLOWNE ===" << std::endl;
		std::cout << "1.Tablica dynamiczna" << std::endl;
		std::cout << "2.Lista dwukierunkowa" << std::endl;
		std::cout << "3.Kopiec binarny (typu maks)" << std::endl;
		std::cout << "4.Drzewo czerwono-czarne" << std::endl;
		std::cout << "0.Wyjscie" << std::endl;
		std::cout << "Podaj opcje:";
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1':
			menu_my_array();
			break;

		case '2':
			menu_my_list();
			break;

		case '3':
			menu_my_heap();
			break;
		case '4':
			menu_my_rbtree();
			break;
		}

	} while (option != '0');

}

void program_manager::menu_my_array()
{
	char option;
	int index;
	int value;
	my_array* array1 = nullptr;

	do {
		system("cls");
		display_menu("--- TABLICA DYNAMICZNA---");
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1': //tutaj wczytytwanie tablicy z pliku
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			std::ifstream fin(file_name);
			if (fin.is_open())
			{
				int size = 0;
				fin >> size;
				int* tab = new int[size];
				for (int i = 0; i < size; i++)
				{
					fin >> tab[i];
				}

				delete array1;
				array1 = new my_array(tab, size);

				delete[] tab;
				fin.close();
				std::cout << "Wczytano dane" << std::endl;
			}
			else
			{
				std::cout << "Brak takiego pliku" << std::endl;
			}
			waitForKey();
			break;
		}
		case '2': // usuwanie elementu z tablicy
		{
			if (array1 != nullptr)
			{
				std::cout << "Podaj index:";
				std::cin >> index;
				try
				{
					array1->remove_at(index);
					std::cout << "Usunieto element o podanym indeksie" << std::endl;
					
				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej tablicy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '3': //tutaj dodawanie elemetu do tablicy
		{
			if (array1 != nullptr)
			{
				std::cout << "Podaj index:";
				std::cin >> index;
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				try
				{
					array1->insert_at(index, value);
					std::cout << "Wstawiono element na podanym indeksie" << std::endl;
					
				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej tablicy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '4': //tutaj znajdowanie elemetu w tablicy
		{
			if (array1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				if (array1->contains(value))
				{
					std::cout << "Podana wartosc jest w tablicy" << std::endl;
				}
				else
				{
					std::cout << "Podanej wartosci nie ma w tablicy" << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej tablicy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '5': //tutaj generowanie  tablicy
		{
			std::cout << "Podaj ilosc elementow tablicy:";
			std::cin >> value;

			delete array1;

			data_generator* dg = new data_generator();
			int* tab = dg->generate_set(value);
			array1 = new my_array(tab, value);
			delete[] tab;

			std::cout << "Wygeneorwane losowe dane" << std::endl;
			waitForKey();
			break;
		}
		case '6': //tutaj wyświetlanie tablicy
		{
			if (array1 != nullptr)
			{
				std::cout << "Tablica:" << std::endl;
				array1->print();
			}
			else
			{
				std::cout << "Brak zainicjalizowanej tablicy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '0':
		{
			delete array1;
		}
		}
	} while (option != '0');
}

void program_manager::menu_my_list()
{
	char option;
	int index;
	int value;
	my_list* list1 = nullptr;

	do {
		system("cls");
		display_menu("--- LISTA DWUKIERUNKOWA ---");
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1': //tutaj wczytytwanie listy z pliku
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			std::ifstream fin(file_name);
			if (fin.is_open())
			{
				int size = 0;
				fin >> size;
				int* tab = new int[size];
				for (int i = 0; i < size; i++)
				{
					fin >> tab[i];
				}
				
				delete list1;
				list1 = new my_list(tab, size);

				delete[] tab;
				fin.close();
				std::cout << "Wczytano dane" << std::endl;
			}
			else
			{
				std::cout << "Brak takiego pliku" << std::endl;
			}
			waitForKey();
			break;
		}
		case '2': // usuwanie elementu z listy
		{
			if (list1 != nullptr)
			{
				std::cout << "Podaj index:";
				std::cin >> index;
				try
				{
					list1->remove_at(index);
					std::cout << "Usunieto element o podanym indeksie" << std::endl;

				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej listy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '3': //tutaj dodawanie elemetu do listy
		{
			if (list1 != nullptr)
			{
				std::cout << "Podaj index:";
				std::cin >> index;
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				try
				{
					list1->insert_at(index, value);
					std::cout << "Wstawiono element na podanym indeksie" << std::endl;
				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej listy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '4': //tutaj znajdowanie elemetu w listy
		{
			if (list1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				if (list1->contains(value))
				{
					std::cout << "Podana wartosc jest w listy" << std::endl;
				}
				else
				{
					std::cout << "Podanej wartosci nie ma w listy" << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanej listy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '5': //tutaj generowanie  tablicy
		{
			std::cout << "Podaj ilosc elementow listy:";
			std::cin >> value;

			

			data_generator* dg = new data_generator();
			int* tab = dg->generate_set(value);
			delete list1;
			list1 = new my_list(tab, value);
			delete[] tab;

			std::cout << "Wygeneorwane losowe dane" << std::endl;
			waitForKey();
			break;
		}
		case '6': //tutaj wyświetlanie listy
		{
			if (list1 != nullptr)
			{
				std::cout << "Od glowy do ogona:" << std::endl;
				list1->print();
				std::cout << "Od ogona do glowy:" << std::endl;
				list1->print_reverse();
			}
			else
			{
				std::cout << "Brak zainicjalizowanej listy" << std::endl;
			}
			waitForKey();
			break;
		}
		case '0':
		{
			delete list1;
		}
		}
	} while (option != '0');
}

void program_manager::menu_my_heap()
{
	char option;
	int value;
	my_heap* heap1 = nullptr;

	do {
		system("cls");
		display_menu("--- KOPIEC BINARNY ---");
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1': //tutaj wczytytwanie kopca z pliku
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			std::ifstream fin(file_name);
			if (fin.is_open())
			{
				int size = 0;
				fin >> size;
				int* tab = new int[size];
				for (int i = 0; i < size; i++)
				{
					fin >> tab[i];
				}

				delete heap1;
				heap1 = new my_heap(tab, size);

				delete[] tab;
				fin.close();
				std::cout << "Wczytano dane" << std::endl;
			}
			else
			{
				std::cout << "Brak takiego pliku" << std::endl;
			}
			waitForKey();
			break;
		}
		case '2': // usuwanie elementu z kopca
		{
			if (heap1 != nullptr)
			{
				try
				{
					heap1->pop_heap();
					std::cout << "Usunieto korzen kopca" << std::endl;

				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego kopca" << std::endl;
			}
			waitForKey();
			break;
		}
		case '3': //tutaj dodawanie elemetu do kopca
		{
			if (heap1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				try
				{
					heap1->push_heap(value);
					std::cout << "Wstawiono element do kopca" << std::endl;
				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego kopca" << std::endl;
			}
			waitForKey();
			break;
		}
		case '4': //tutaj znajdowanie elemetu w kopcu
		{
			if (heap1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				if (heap1->contains(value))
				{
					std::cout << "Podana wartosc jest w kopcu" << std::endl;
				}
				else
				{
					std::cout << "Podanej wartosci nie ma w kopcu" << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego kopca" << std::endl;
			}
			waitForKey();
			break;
		}
		case '5': //tutaj generowanie kopca
		{
			std::cout << "Podaj ilosc elementow kopca:";
			std::cin >> value;

			data_generator* dg = new data_generator();
			int* tab = dg->generate_set(value);
			delete heap1;
			heap1 = new my_heap(tab, value);
			delete[] tab;

			std::cout << "Wygeneorwane losowe dane" << std::endl;
			waitForKey();
			break;
		}
		case '6': //tutaj wyświetlanie kopca
		{
			if (heap1 != nullptr)
			{
				std::cout << "Tablica kopca:" << std::endl;
				heap1->print_array();
				std::cout << "Poziomy kopca:" << std::endl;
				heap1->print_levels();
				std::cout << "Drzewo kopca:" << std::endl;
				heap1->print_tree();
			}
			else
			{
				std::cout << "Brak zainicjalizowanego kopca" << std::endl;
			}
			waitForKey();
			break;
		}
		case '0':
		{
			delete heap1;
		}
		}
	} while (option != '0');
}

void program_manager::menu_my_rbtree()
{
	char option;
	int value;
	my_rbtree* rbtree1 = nullptr;

	do {
		system("cls");
		display_menu("--- DRZEWO CZERWONO-CZARNE ---");
		option = _getche();
		std::cout << std::endl;

		switch (option) {
		case '1': //tutaj wczytytwanie drzewa rb z pliku
		{
			std::cout << "Podaj nazwe pliku z roszerzeniem: ";
			std::string file_name;
			std::cin >> file_name;

			std::ifstream fin(file_name);
			if (fin.is_open())
			{
				int size = 0;
				fin >> size;
				int* tab = new int[size];
				for (int i = 0; i < size; i++)
				{
					fin >> tab[i];
				}

				delete rbtree1;
				rbtree1 = new my_rbtree(tab, size);

				delete[] tab;
				fin.close();
				std::cout << "Wczytano dane" << std::endl;
			}
			else
			{
				std::cout << "Brak takiego pliku" << std::endl;
			}
			waitForKey();
			break;
		}
		case '2': // usuwanie elementu z drzewa rb
		{
			if (rbtree1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				try
				{
					rbtree1->remove(value);
					std::cout << "Usunieto element" << std::endl;

				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego drzewa rb" << std::endl;
			}
			waitForKey();
			break;
		}
		case '3': //tutaj dodawanie elemetu do drzewa rb
		{
			if (rbtree1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				try
				{
					rbtree1->insert(value);
					std::cout << "Wstawiono element do drzewa rb" << std::endl;
				}
				catch (ds_exception &e)
				{
					std::cout << e.what() << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego drzewa rb" << std::endl;
			}
			waitForKey();
			break;
		}
		case '4': //tutaj znajdowanie elemetu w drzewie rb
		{
			if (rbtree1 != nullptr)
			{
				std::cout << "Podaj wartosc:";
				std::cin >> value;
				if (rbtree1->contains(value))
				{
					std::cout << "Podana wartosc jest w drzewie rb" << std::endl;
				}
				else
				{
					std::cout << "Podanej wartosci nie ma w drzewie rb" << std::endl;
				}
			}
			else
			{
				std::cout << "Brak zainicjalizowanego drzewa rb" << std::endl;
			}
			waitForKey();
			break;
		}
		case '5': //tutaj generowanie drzewa rb
		{
			std::cout << "Podaj ilosc elementow drzewa rb:";
			std::cin >> value;

			data_generator* dg = new data_generator();
			int* tab = dg->generate_set(value);
			delete rbtree1;
			rbtree1 = new my_rbtree(tab, value);
			delete[] tab;

			std::cout << "Wygeneorwane losowe dane" << std::endl;
			waitForKey();
			break;
		}
		case '6': //tutaj wyświetlanie drzewa rb
		{
			if (rbtree1 != nullptr)
			{
				std::cout << "Drzewo rb:" << std::endl;
				rbtree1->print_tree();
			}
			else
			{
				std::cout << "Brak zainicjalizowanego drzewa rb" << std::endl;
			}
			waitForKey();
			break;
		}
		case '0':
		{
			delete rbtree1;
		}
		}
	} while (option != '0');
}

void program_manager::display_menu(std::string title)
{
	std::cout << std::endl;
	std::cout << title << std::endl;
	std::cout << "1.Wczytaj z pliku" << std::endl;
	std::cout << "2.Usun" << std::endl;
	std::cout << "3.Dodaj" << std::endl;
	std::cout << "4.Znajdz" << std::endl;
	std::cout << "5.Utworz losowo" << std::endl;
	std::cout << "6.Wyswietl" << std::endl;
	std::cout << "0.Powrot do menu glownego" << std::endl;
	std::cout << "Podaj opcje:";
}

void program_manager::waitForKey()
{
	std::cout << "Wcisnij [ENTER] aby kontynuowac.\n";
	std::cin.get();
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}