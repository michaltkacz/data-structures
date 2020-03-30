#include "program_manager.h"
#include <iostream>
#include "my_array.h"
#include "my_list.h"
#include "my_heap.h"
#include "my_rbtree.h"
#include "data_generator.h"
#include "time_logger.h"
#include <fstream>

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

	const int test_redo_number = 10;
	const int data_sizes_size = 10;
	const int data_sizes[data_sizes_size] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

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
}

void program_manager::clear_file(std::string file_pathname)
{
	std::ofstream fout(file_pathname, std::ofstream::out | std::ofstream::trunc);
	fout.close();
}

void program_manager::run_user_interface_mode()
{
	//...

}


