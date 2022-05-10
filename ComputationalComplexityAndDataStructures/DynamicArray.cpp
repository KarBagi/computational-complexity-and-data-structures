#include <iostream>
#include <fstream>
#include <String>
#include <windows.h>
#include <ctime>
#include "DynamicArray.h"
#include "Stoper.h"

using namespace std;

Stoper stoper;

DynamicArray::DynamicArray(int s) {		//konstruktor
	size = s;
	mainArray = new int[size];

	mainArray = NULL;
}

DynamicArray::~DynamicArray() {		//destruktor
	for (int i = 0; i < size; i++) {
		mainArray = 0;
	}

	delete[] mainArray;
}

void DynamicArray::readFromFile(int fileN) {		//wczytywanie zawartosci pliku
	string filename;
	string line;

	if (fileN == 0) {
		cout << "Podaj nazwe pliku: ";
		cin >> filename;
	}
	else if (fileN == 1) {
		filename = "data.txt";
	}

	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Problem z otworzeniem pliku" << endl;
	}

	else {
		int newSize = 0;

		getline(file, line);

		newSize = atoi(line.c_str());

		for (int i = 0; i < newSize; i++) {
			getline(file, line);
			addElementToEnd(atoi(line.c_str()));
		}
		file.close();
	}
}

void DynamicArray::addElementToFront(int value) {			//dodanie elementu na poczatek tablicy
	int* newArray = new int[this -> size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		newArray[0] = value;			//na pierwsze miejsce w nowej tablicy wpisujemy zadana wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i < this->size; i++) {
				newArray[i + 1] = mainArray[i];				//wszystkie nastepne wartosci przepisujemy do nowej tablicy
			}
			//delete[] mainArray;		//usuwamy glowna tablice
		}	

	this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
	mainArray = newArray;		//przepisujemy nowa tablice do glownej
}

void DynamicArray::addElementToEnd(int value) {		//dodanie elementu na koniec tablicy
	int* newArray = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

	newArray[this -> size] = value;			//na ostatnie miejsce w nowej tablicy zapisujemy zadana wartosc

	if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
		for (int i = 0; i < this->size; i++) {
			newArray[i] = mainArray[i];		//wszystkie poprzednie liczby przepisujemy do nowej tablicy
		}
		//delete[] mainArray;		//usuwamy glowna tablice
	}

	this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
	mainArray = newArray;		//przepisujemy nowa tablice do glownej
}

void DynamicArray::addElement(int value, int position) {		//dodanie elementu da zadana pozycje tablicy
	int* newArray = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

	if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
		for (int i = 0; i <= this->size; i++) {
			if (i < position) {
				newArray[i] = mainArray[i];			//jezeli wartosc i jest mniejsza od zadanej pozycji to elementy sa na tych samych indeksach
			}
			else if (i == position) {
				newArray[i] = value;			//jezeli i == pozycja, wpisujemy w to miejsce zadana wartosc
			}
			else if (i > position) {
				newArray[i] = mainArray[i-1];		//wszystkie wartosci powyzej maja indeks o 1 wiekszy
			}
		}
		delete[] mainArray; 		//usuwamy glowna tablice
	}

	this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
	mainArray = newArray;		//przepisujemy nowa tablice do glownej
}

void DynamicArray::removeElement(int position) {		//usuniecie elementu z tablicy

	if (this->size != 0) {			//sprawdzamy czy tablica nie jest pusta
		int* newArray = new int[this->size - 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		for (int i = 0; i <= this->size; i++) {
			if (i < position) {
				newArray[i] = mainArray[i];			//jezeli i jest < od zadanej pozycji to wszystkie wartosci sa takie same
			}
			else if (i == position) continue;		//jezeli i jest rowne wartosci position kontynuujemy algorytm bez jej wpisywania
			else if (i > position) {
				newArray[i - 1] = mainArray[i];		//reszte przepisujemy z indeksem o 1 mniejszym
			}
		}

		this->size--;			//zmniejszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray;		//przepisujemy nowa tablice do glownej
	}
	else cout << "Tablica jest pusta" << endl << endl;
}

void DynamicArray::showArray() {
	for (int i = 0; i < this -> size; i++) {
		cout << mainArray[i] << " ";		//wyswietlenie calej zawartosci tablicy oraz indeksow poszczegolnych wartosci
		cout << i << endl;
	}

	cout << endl;
}

int DynamicArray::findElement(int value) {		//wyszukanie wartosci
	if (this->size > 0) {
		for (int i = 0; i < this->size; i++) {
			if (mainArray[i] == value) {
				value = i;

				return value;		//jezeli znajdziemy poszukiwana wartosc zwracamy 'i'

				break;
			}
			else if (i == this->size - 1) {
				return 2147483647;			//jezeli nie ma takiej wartosci w tablicy zwracamy maksymalna wartosc Int
			}

			else if (mainArray[i] != value) continue;
		}
	}
}

void DynamicArray::generateArray(int value) {			//generowanie tablicy o zadanej wielkosci
	srand(time(NULL));
	for (int i = 0; i < value; i++) {
		addElementToEnd(rand() % 100 + 1);
	}
}

//pomiary czasow dla poszczegolnych algorytmow 

double DynamicArray::testAddElementToFront() {	
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	//readFromFile(1);

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		//addElementToFront(5);

		int* newArray = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		newArray[0] = 5;			//na pierwsze miejsce w nowej tablicy wpisujemy zadana wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i < this->size; i++) {
				newArray[i + 1] = mainArray[i];				//wszystkie nastepne wartosci przepisujemy do nowej tablicy
			}
			delete[] mainArray;		//usuwamy glowna tablice
		}

		this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray;		//przepisujemy nowa tablice do glownej

		timeSum += stoper.getCounter();

		//removeElement(0);

		int* newArray2 = new int[this->size - 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i <= this->size; i++) {
				if (i < 0) {
					newArray2[i] = mainArray[i];			//jezeli i jest < od zadanej pozycji to wszystkie wartosci sa takie same
				}
				else if (i == 0) continue;		//jezeli i jest rowne wartosci position kontynuujemy algorytm bez jej wpisywania
				else if (i > 0) {
					newArray2[i - 1] = mainArray[i];		//reszte przepisujemy z indeksem o 1 mniejszym
				}
			}
			delete[] mainArray; 		//usuwamy glowna tablice
		}

		this->size--;			//zmniejszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray2;		//przepisujemy nowa tablice do glownej
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double DynamicArray::testAddElementToEnd(int position) {
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		int* newArray = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		newArray[this->size] = 5;			//na ostatnie miejsce w nowej tablicy zapisujemy zadana wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i < this->size; i++) {
				newArray[i] = mainArray[i];		//wszystkie poprzednie liczby przepisujemy do nowej tablicy
			}
			delete[] mainArray;		//usuwamy glowna tablice
		}

		this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray;		//przepisujemy nowa tablice do glownej

		timeSum += stoper.getCounter();


		int* newArray2 = new int[this->size - 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i <= this->size; i++) {
				if (i < position) {
					newArray2[i] = mainArray[i];			//jezeli i jest < od zadanej pozycji to wszystkie wartosci sa takie same
				}
				else if (i == position) continue;		//jezeli i jest rowne wartosci position kontynuujemy algorytm bez jej wpisywania
				else if (i > position) {
					newArray2[i - 1] = mainArray[i];		//reszte przepisujemy z indeksem o 1 mniejszym
				}
			}
			delete[] mainArray; 		//usuwamy glowna tablice
		}

		this->size--;			//zmniejszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray2;		//przepisujemy nowa tablice do glownej
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double DynamicArray::testAddElement() {
	srand(time(NULL));
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;
	int position;


	for (int i = 0; i < numberOfTests; i++) {
		position = rand() % 30000;

		stoper.startCounter();

		int* newArray = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i <= this->size; i++) {
				if (i < position) {
					newArray[i] = mainArray[i];			//jezeli wartosc i jest mniejsza od zadanej pozycji to elementy sa na tych samych indeksach
				}
				else if (i == position) {
					newArray[i] = 5;			//jezeli i == pozycja, wpisujemy w to miejsce zadana wartosc
				}
				else if (i > position) {
					newArray[i] = mainArray[i - 1];		//wszystkie wartosci powyzej maja indeks o 1 wiekszy
				}
			}
			delete[] mainArray; 		//usuwamy glowna tablice
		}

		this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray;		//przepisujemy nowa tablice do glownej

		timeSum += stoper.getCounter();


		int* newArray2 = new int[this->size - 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i <= this->size; i++) {
				if (i < position) {
					newArray2[i] = mainArray[i];			//jezeli i jest < od zadanej pozycji to wszystkie wartosci sa takie same
				}
				else if (i == position) continue;		//jezeli i jest rowne wartosci position kontynuujemy algorytm bez jej wpisywania
				else if (i > position) {
					newArray2[i - 1] = mainArray[i];		//reszte przepisujemy z indeksem o 1 mniejszym
				}
			}
			delete[] mainArray; 		//usuwamy glowna tablice
		}

		this->size--;			//zmniejszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray2;		//przepisujemy nowa tablice do glownej
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double DynamicArray::testRemoveElementFront() {
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		int* newArray = new int[this->size - 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i <= this->size; i++) {
				if (i < 0) {
					newArray[i] = mainArray[i];			//jezeli i jest < od zadanej pozycji to wszystkie wartosci sa takie same
				}
				else if (i == 0) continue;		//jezeli i jest rowne wartosci position kontynuujemy algorytm bez jej wpisywania
				else if (i > 0) {
					newArray[i - 1] = mainArray[i];		//reszte przepisujemy z indeksem o 1 mniejszym
				}
			}
			delete[] mainArray; 		//usuwamy glowna tablice
		}

		this->size--;			//zmniejszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray;		//przepisujemy nowa tablice do glownej

		timeSum += stoper.getCounter();


		int* newArray2 = new int[this->size + 1];				//stworzenie nowej tablicy o 1 wieksza od poprzedniej, w ktorej zapiszemy dodatkowa wartosc

		newArray2[0] = 6;			//na pierwsze miejsce w nowej tablicy wpisujemy zadana wartosc

		if (mainArray != NULL) {			//sprawdzamy czy tablica nie jest pusta
			for (int i = 0; i < this->size; i++) {
				newArray2[i + 1] = mainArray[i];				//wszystkie nastepne wartosci przepisujemy do nowej tablicy
			}
			delete[] mainArray;		//usuwamy glowna tablice
		}

		this->size++;			//powiekszamy rozmiar domyslnej tablicy o 1
		mainArray = newArray2;		//przepisujemy nowa tablice do glownej
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double DynamicArray::testRemoveElementEnd(int position) {
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	if (this->size != 0) {
		for (int i = 0; i < numberOfTests; i++) {
			stoper.startCounter();

			this->size--;

			int* newArray = new int[this->size];
			
			for (int i = 0; i < this->size; i++) {
				newArray[i] = mainArray[i];
			}

			delete[] mainArray;
			mainArray = newArray;

			timeSum += stoper.getCounter();

			this->size++;

			int* newArray2 = new int[this->size];

			for (int i = 0; i < this->size; i++) {
				newArray2[i] = mainArray[i];
			}

			delete[] mainArray;
			newArray2[this->size - 1] = 6;
			mainArray = newArray2;
		}
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

double DynamicArray::testRemoveElement() {
	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;
	int position;
	srand(time(NULL));


	if (this->size != 0) {
		for (int i = 0; i < numberOfTests; i++) {
			position = rand() % 30000;
			stoper.startCounter();

			int* newArray = new int[this->size - 1];

			for (int i = 0; i < this->size; i++) {
				if (i < position) {
					newArray[i] = mainArray[i];
				}
				else if (i == position) {
					continue;
				}
				else if (i > position) {
					newArray[i - 1] = mainArray[i];
				}
			}

			delete[] mainArray;
			this->size--;
			mainArray = newArray;

			timeSum += stoper.getCounter();


			int* newArray2 = new int[this->size + 1];

			for (int i = 0; i < this->size; i++) {
				if (i < position) {
					newArray2[i] = mainArray[i];			//jezeli wartosc i jest mniejsza od zadanej pozycji to elementy sa na tych samych indeksach
				}
				else if (i == position) {
					newArray2[i] = 20;			//jezeli i == pozycja, wpisujemy w to miejsce zadana wartosc
				}
				else if (i > position) {
					newArray2[i] = mainArray[i - 1];		//wszystkie wartosci powyzej maja indeks o 1 wiekszy
				}
			}

			delete[] mainArray;
			this->size++;
			mainArray = newArray2;
		}
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

void DynamicArray::userInterface() {		//interfejs uzytkownika
	int choise;
	int choise1;
	int position;
	int value;

	do {
		choise = 0;
		position = 0;
		value = 0;

		cout << "1. Wczytanie wartosci z pliku" << endl;
		cout << "2. Wygenerowanie losowych wartosci" << endl;
		cout << "3. Dodanie elementu do tablicy" << endl;
		cout << "4. Usuniecie elementu z tablicy" << endl;
		cout << "5. Znajdz element" << endl;
		cout << "6. Wyswietl zawartosc tablicy" << endl;
		cout << "7. Pomiary czasu " << endl;
		cout << "8. Wyjscie" << endl;

		cout << "wybierz opcje: ";
		cin >> choise;
		cout << endl;

		switch (choise) {
		case 1: {
			readFromFile(0);
			cout << endl;

			break;
		}
		case 2: {
			cout << "Ile elementow chcesz wygenerowac: ";
			cin >> value;
			cout << endl;

			generateArray(value);

			cout << "Wygenerowano " << value << " elementow" << endl;

			break;
		}
		case 3: {
			choise1 = 0;

			cout << "1. Dodaj element na poczatku" << endl;
			cout << "2. Dodaj element na koncu" << endl;
			cout << "3. Dodaj element na wybranej pozycji" << endl;

			cout << "Wybierz opcje: ";
			cin >> choise1;

			switch (choise1) {
			case 1: {
				cout << "Podaj wartosc elementu: ";
				cin >> value;
				cout << endl;

				addElementToFront(value);

				break;
			}
			case 2: {
				cout << "Podaj wartosc elementu: ";
				cin >> value;
				cout << endl;

				addElementToEnd(value);

				break;
			}
			case 3: {
				cout << "Na jakiej pozycji:";
				cin >> position;
				cout << endl;

				cout << "Podaj wartosc elementu: ";
				cin >> value;
				cout << endl;

				addElement(value, position);

				break;
			}
			}
			break;
		}
		case 4: {
			choise1 = 0;

			cout << "1. Usun element na poczatku" << endl;
			cout << "2. Usun element na koncu" << endl;
			cout << "3. Usun element na wybranej pozycji" << endl;

			cout << "Wybierz opcje: ";
			cin >> choise1;

			switch (choise1) {
			case 1: {
				removeElement(0);

				break;
			}
			case 2: {
				removeElement(this->size);

				break;
			}
			case 3: {
				cout << "Na jakiej pozycji:";
				cin >> position;

				removeElement(position);

				break;
			}
			}

			break;
		}
		case 5: {
			cout << "Podaj wartosc elementu jakiego chcesz znalezc: ";
			cin >> value;
			cout << endl;

			position = findElement(value);

			if (position == 2147483647) {
				cout << "Nie ma takiej liczby w tablicy" << endl;
			}
			else {
				cout << value << " znajduje sie na " << position << " pozycji" << endl;
			}

			break;
		}
		case 6: {
			showArray();

			break;
		}
		case 7: {
			int i = 0;

			if (i == 0) {
				generateArray(30000);
				i++;
			}

			cout << "Dodawanie na poczatek tablicy dla 10000 powtorzen: " << testAddElementToFront()  << " ns"<< endl;
			cout << "Dodawanie na koniec tablicy dla 10000 powtorzen: " << testAddElementToEnd(this->size) << " ns" << endl;
			cout << "Dodawanie na losowej pozycji dla 10000 powtorzen: " << testAddElement() << " ns" << endl << endl;

			cout << "Usuniecie elementu z poczatku tablicy dla 10000 powtorzen: " << testRemoveElementFront() << " ns" << endl;
			cout << "Usuniecie elementu z konca tablicy dla 10000 powtorzen: " << testRemoveElementEnd(this->size) << " ns" << endl;
			cout << "Usuniecie elementu ze srodka tablicy dla 10000 powtorzen: " << testRemoveElement() << " ns" << endl;

			break;
		}
		}

	} while (choise != 8);
}