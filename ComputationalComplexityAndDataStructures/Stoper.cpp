#include <iostream>
#include <ctime>
#include <windows.h>
#include "Stoper.h"

using namespace std;

double PCFreq = 0.0;
_int64 CounterStart = 0;

void Stoper::startCounter() {			//stoper
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";			//zabezpieczenie przed nieprawidlowym dzialaniemm 
																//stopera
	PCFreq = double(li.QuadPart) / 1000000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double Stoper::getCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;			//zworcenie wartosci stopera
}