#pragma once
#include <iostream>
#include <fstream>
#include <ctime>

#include "Heap.h"
#include "Stoper.h"

using namespace std;

void Heap::add(int value) {

	int* newHeap = new int[this->size + 1];					 //nowa tablica wieksza o 1 element
	newHeap[this->size] = value;							//ustawienie wartosci na koniec nowej tablicy

	if (this->heap != NULL) {
		for (int i = 0; i < this->size; i++) {
			newHeap[i] = this->heap[i];						//kopjujemy wartoœci poprzedniej tablicy do nowej
		}
		delete[] this->heap;							   //usuwamy star¹ tablicê
	}

	this->size++;										//zwiêkszamy rozmiar tablicy
	this->heap = newHeap;								//stara tablica na now¹
	repairHeap();										// przywrócenie wlasnosci kopca
}

void Heap::heapify(int position) {

	if (position > (size / 2) && position <= size) return;			//odrzucenie korzenia oraz wyjscia poza rozmiar

	int bigger = position;

	if (this->heap[bigger] < this->heap[leftChild(position)] && leftChild(position) < this->size) {			//sprawdzenie która wartosc jest wieksza
		bigger = leftChild(position);
	}
	else if (this->heap[bigger] < this->heap[rightChild(position)] && rightChild(position) < this->size) {
		bigger = rightChild(position);
	}
	else if (this->heap[position] != this->heap[bigger]) {
		int temp;
		temp = this->heap[position];			//zamiana miejscami wartosci
		this->heap[position] = this->heap[bigger];
		this->heap[bigger] = temp;
		heapify(bigger);				//wywolanie heapify dla indexu wiekszej wartosci oraz ponowne dla indexu poniewaz wartosc w nim sie zmienila
		heapify(position);
	}
}

void Heap::remove() {
	if (this->heap[0] != NULL) {							//jesli pusty to wyswietl wiadomosc
		this->heap[0] = this->heap[this->size - 1];			//zamiana korzenia z ostatnim najmniejszym elementem
		size--;												//zmniejszenie rozmiaru
		heapify(0);											//przywrócenie max do korzenia
	}
	else cout << "Kopiec jest pusty" << endl;
}

void Heap::search(int value) {

	int count = 0;							//zliczenie ilosci wystapien elemntu w kopcu
	for (int i = 0; i < size; i++) {		//jesli wystepuje wartosc bedzie !=0
		if (this->heap[i] == value) {
			count++;
		}
	}
	if (!count == 0) {
		cout << "Ta wartosc istnieje w kopcu" << endl;
	}
	else {
		cout << "Nie ma takiej wartosci w kopcu" << endl;
	}
}

void Heap::readFromFile(int fileN) {
	string fileName;
	string line;

	if (fileN == 0) {
		cout << "Wpisz nazwe pliku: ";
		cin >> fileName;
	}
	else if (fileN != 0) {
		fileName = "data.txt";
	}


	cout << endl;
	ifstream file;						//stworzenie obiektu ifstream powiazanego z filename
	file.open(fileName);

	if (!file) {                              // jesli nie udalo sie otworzyc pliku
		cout << "Blad przy wczytywaniu pliku" << endl;
	}
	else {

		this->heap = new int[size + 1];
		int newSize = 0;
		getline(file, line);								//pobranie lini
		newSize = atoi(line.c_str());						//funkcja zwracajaca wartosc lanucha znakow przekonwertowana na int

		for (int i = 0; i < newSize; i++) {
			getline(file, line);
			add(atoi(line.c_str()));					//dodaje kolejne wczytane wartosci do kopca
		}
		file.close();										//zakonczenie operacji na pliku
	}
}

string Heap::show() {			//skonstruowanie i wyswietlenie kopca 
	int height = floor(log2(this->size));
	int width = pow(2, height) * 2;
	int aHeight = 0;
	int bigSpaceSize = 0;
	double smallSpaceSize = 0;
	double bigSpaceCounter = 0;
	int heapIterator = 0;


	string output = "";

	for (; aHeight <= height; aHeight++) {
		bigSpaceCounter = pow(2, aHeight) - 1;
		bigSpaceSize = smallSpaceSize;
		smallSpaceSize = pow(2, height - aHeight) - 1;


		for (int i = 0; i < smallSpaceSize; i++) {
			output += " ";
		}
		do {
			if (heapIterator + 1 <= this->size) {
				output += to_string(this->heap[heapIterator++]);
			}
			else {
				output += " ";
			}
			if (bigSpaceCounter > 0) {
				for (int i = 0; i < bigSpaceSize; i++) {
					output += " ";
				}
			}
		} while (bigSpaceCounter-- > 0);
		for (int i = 0; i < smallSpaceSize; i++) {
			output += " ";
		}
		output += '\n';
	}
	return output;


}

void Heap::generateRandomData(int sizeNew) {

	this->heap = new int[size + 1];
	srand(time(NULL));
	int random = 0;

	for (int i = 0; i < sizeNew; ++i) {
		random = ((std::rand() % 100) + 1);					//wygenerowanie pseudorandomowej wartosci z podanego zakresu i dodanie jej do kopca
		add(random);
	}
	this->size = sizeNew;									//przypisanie nowego rozmiaru
}

int Heap::leftChild(int position) {				//zwraca wartosc która odpowiada wartosci lewego potomka dla zadanego indeksu 
	if (position == 0) {
		return  1;
	}
	else {
		return position * 2;
	}
}

int Heap::rightChild(int position) {				//zwraca wartosc która odpowiada wartosci prawego potomka dla zadanego indeksu 
	if (position == 0) {
		return 2;
	}
	else {
		return position * 2 + 1;
	}
}

int Heap::parent(int position) {					//zwraca wartosc która odpowiada wartosci rodzica dla zadanego indeksu 
	return floor(position / 2);
}

void Heap::repairHeap() {																	//przywrócenie w³asnoœci kopca
	int last = this->size - 1;
	while (this->heap[last] > this->heap[parent(last)]) {				//jestli rodzic ma wieksza wartosc to zamieniamy miejscami
		int temp;
		temp = this->heap[last];
		this->heap[last] = this->heap[parent(last)];
		this->heap[parent(last)] = temp;
		last = parent(last);											//ustawienie elementu ostatni na ten zamieniony
	}
}

//pomiary czasow dla poszczegolnych algorytmow

double Heap::testAdd() {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	readFromFile(1);

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		add(5);

		timeSum += stoper.getCounter();

		remove();
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double Heap::testRemove() {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	readFromFile(1);

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		remove();

		timeSum += stoper.getCounter();

		add(31);
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

void Heap::userInterface() {		//interfejs uzytkownika
	int userChoice;

	do {
		cout << "1. Wczytaj z pliku" << endl;
		cout << "2. Wygeneruj wartosci" << endl;
		cout << "3. Dodaj element" << endl;
		cout << "4. Usun element " << endl;
		cout << "5. Wyszukaj element" << endl;
		cout << "6. Pokaz kopiec" << endl;
		cout << "7. Pomiar czasu" << endl;
		cout << "8. Wyjscie" << endl;
		cin >> userChoice;
		switch (userChoice) {
		case 1: {
			readFromFile(0);
			break;
		}
		case 2: {
			cout << "Ile wartosci chcesz wygenerowac: ";
			cin >> userChoice;
			generateRandomData(userChoice);

			cout << endl;
			break;
		}
		case 3: {
			cout << "Jaka wartosc chcesz dodac: ";
			cin >> userChoice;
			add(userChoice);
			cout << endl;
			break;
		}
		case 4: {
			cout << "Usuniecie ostatniego elementu " << endl;
			remove();
			break;
		}
		case 5: {
			cout << "Jakiego elementu szukasz: ";
			cin >> userChoice;
			search(userChoice);

			cout << endl;
			break;
		}
		case 6: {
			cout << show() << endl;
			break;
		}
		case 7: {
			cout << "Dodanie elementu do kopca dla 10000 powtorzen: " << testAdd() << " ns" << endl;
			cout << "Usuniecie elementu z kopca dla 10000 powtorzen: " << testRemove() << " ns" << endl;
		}
		}
	} while (userChoice != 8);
}