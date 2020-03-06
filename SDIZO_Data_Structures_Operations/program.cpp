// SDIZO_Data_Structures_Operations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include "time_logger.h"
#include "my_array.h"


using namespace std;

int main()
{
	my_array arr;

	arr.push_back(0);
	arr.push_back(1);
	arr.push_back(2);

	arr.remove_at(1);

	arr.print();

}



//srand(time(0));
//const int TAB_SIZE = 5;
//int* tab = new int[TAB_SIZE];

//for (int i = 0; i < TAB_SIZE; i++)
//{
//	tab[i] = rand() % 10;
//}

//ofstream fout("data.txt", ios::out);
//if(fout.is_open())
//{
//	fout << TAB_SIZE << endl;
//	for(int i=0; i< TAB_SIZE; i++)
//	{
//		fout << tab[i] << endl;
//	}
//}
//fout.close();


//int readTabSize;
//int* readTab = nullptr;

//ifstream fin("data.txt", ios::in);
//if(fin.is_open())
//{
//	fin >> readTabSize;
//	readTab = new int[readTabSize];
//	for (int i = 0; i < readTabSize; i++)
//	{
//		fin >> readTab[i];
//	}
//}
//fin.close();

//if (readTab != nullptr)
//{
//	for (int i = 0; i < readTabSize; i++)
//	{
//		cout << readTab[i] << endl;
//	}
//	
//}

//delete[] tab;
//delete[] readTab;

//time_logger timeLogger{};
//for(int i=0; i<10; i++)
//{
//	timeLogger.start();
//	Sleep(1000);
//	timeLogger.stop();
//	cout << timeLogger.get_time_span() << endl;
//}

//cout << endl << timeLogger.mean() << endl;