#include <iostream>
#include <fstream>
#include <String>
#include <windows.h>
#include <ctime>
#include "DynamicArray.h"
#include "Stoper.h"

using namespace std;

DynamicArray::DynamicArray(int s) {		//konstruktor
	size = s;
	mainArray = new int[size];

	for (int i = 0; i < size; i++) {
		mainArray[i] = 0;
	}
}

DynamicArray::~DynamicArray() {		//destruktor
	for (int i = 0; i < size; i++) {
		mainArray = 0;
	}

	delete[] mainArray;
}

void DynamicArray::readFromFile() {
	string filename;
	string line;

	cout << "Podaj nazwe pliku: ";
	cin >> filename;

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

void DynamicArray::addElementToFront(int value) {
	int* newArray = new int[this -> size + 1];
	
		newArray[0] = value;

		if (mainArray != NULL) {
			for (int i = 0; i < this->size; i++) {
				newArray[i + 1] = mainArray[i];
			}
			delete[] mainArray;
		}

	this -> size++;
	mainArray = newArray;
}

void DynamicArray::addElementToEnd(int value) {
	int* newArray = new int[this->size + 1];

	newArray[this -> size] = value;

	if (mainArray != NULL) {
		for (int i = 0; i < this->size; i++) {
			newArray[i] = mainArray[i];
		}
		delete[] mainArray;
	}

	this->size++;
	mainArray = newArray;
}

void DynamicArray::addElement(int value, int position) {
	int* newArray = new int[this->size + 1];

	if (mainArray != NULL) {
		for (int i = 0; i <= this->size; i++) {
			if (i < position) {
				newArray[i] = mainArray[i];
			}
			else if (i == position) {
				newArray[i] = value;
			}
			else if (i > position) {
				newArray[i] = mainArray[i-1];
			}
		}
		delete[] mainArray;
	}

	this->size++;
	mainArray = newArray;
}

void DynamicArray::removeElement(int position) {
	int* newArray = new int[this->size - 1];

	if (mainArray != NULL) {
		for (int i = 0; i <= this->size; i++) {
			if (i < position) {
				newArray[i] = mainArray[i];
			}
			else if (i == position) continue;
			else if (i > position) {
				newArray[i - 1] = mainArray[i];
			}
		}

		delete[] mainArray;
	}

	this->size--;
	mainArray = newArray;
}

void DynamicArray::showArray() {
	for (int i = 0; i < this -> size; i++) {
		cout << mainArray[i] << " ";
		cout << i << endl;
	}

	cout << endl;
}

int DynamicArray::findElement(int value) {
	for (int i = 0; i < this->size; i++) {
		if (mainArray[i] == value) {
			value = i;

			return value;

			break;
		}
		else if (i == this->size - 1) {
			return 2147483647;
		}

		else if (mainArray[i] != value) continue;
	}
}

void DynamicArray::generateArray(int value) {
	srand(time(NULL));
	for (int i = 0; i < value; i++) {
		addElementToEnd(rand() % 100);
	}
}

void DynamicArray::userInterface() {
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
		cout << "7. Wyjscie" << endl;

		cout << "wybierz opcje: ";
		cin >> choise;
		cout << endl;

		switch (choise) {
		case 1: {
			readFromFile();

			break;
		}
		case 2: {
			cout << "Ile elementow chcesz wygenerowac: ";
			cin >> value;
			cout << endl;

			generateArray(value);

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
		}

	} while (choise != 7);
}