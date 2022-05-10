#pragma once
#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>
#include <fstream>
#include <String>
#include <windows.h>
#include <ctime>
#include "Node.h"
#include "Stoper.h"

using namespace std;

template <class T>
class DoublyLinkedList {
	int counter;

public:

	Node<T>* head;
	Node<T>* tail;

	DoublyLinkedList() = default;

	Node<T>* get(int index) const;

	void readFromFile(int fileN);
	void generateList(int value);
	void addElementHead(int value);
	void addElementBack(int value);
	void addElement(int value, int position);
	void removeElementFront();
	void removeElement(int position);
	int search(const T& value) const;
	void show() const;
	void userInterface();
	double testAddElementHead();
	double testAddElementBack(int position);
	double testAddElement();
	double testRemoveElementFront();
	double testRemoveElement(int position);

};

template <class T>
Node<T>* DoublyLinkedList<T>::get(int index) const
{
	if (index < 0 || index > counter) {
		return nullptr;
	}

	if (index == 0) {
		return head;			//zabezpieczenia 
	}

	if (index == counter - 1) {
		return tail;
	}

	Node<T>* temp_node = head;			//wpisujemy element do pamieci tymczasowej
										//po czym j¹ zwracamy
	for (int i = 0; i < index; ++i)
	{
		temp_node = temp_node->next;
	}

	return temp_node;
}

template <class T>
void DoublyLinkedList<T>::generateList(int value) {
	srand(time(NULL));

	for (int i = 0; i < value; i++) {
		addElementHead((rand() % 100) + 1);			//generowanie liczb pseudolosowych i wpisywanie ich do listy
	}
}

template <class T>
void DoublyLinkedList<T>::readFromFile(int fileN) {			//wczytanie zawartosci pliku
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
			addElementBack(atoi(line.c_str()));
		}
		file.close();
	}
}

template <class T> 
void DoublyLinkedList<T>::addElementHead(int value) {
	Node<T>* node = new Node<T>{ value };

	node->next = head;			//przesuniecie calej listy o jeden i wpisanie elementu jako pierwsy

	if (head != nullptr) {
		head->prev = node;
	}

	head = node;

	if (counter == 0) {
		tail = head;
	}

	counter++;			//powiekszenie rozmiaru o jeden
}

template <class T>
void DoublyLinkedList<T>::addElementBack(int value) {
	if (counter == 0)
	{
		addElementHead(value);		//jezeli lista ma rozmiar == 0 dodajemy do poczatku
		return;
	}

	Node<T>* node = new Node<T>{ value };			//dodawanie elementu na koniec listy 
	tail->next = node;								//jest analogiczne do wczesniejszego
	node->prev = tail;
	tail = node;

	counter++;
}

template <class T> 
void DoublyLinkedList<T>::addElement(int value, int position) {
	if (position < 0 || position > counter) {
		return;				//zabezpieczenia przed wpisaniem zlej wartosci
	}

	if (position == 0)
	{
		addElementHead(value);			//jezeli lista ma rozmiar == 0 dodajemy do poczatku
		return;
	}

	else if (position == counter)
	{
		addElementBack(value);			//jezeli zadana pozycja == rozmiar listy dodajemy element na koniec
		return;
	}

	Node<T>* prev_node = head;

	for (int i = 0; i < position - 1; ++i)			//analogicznie do wczesniejszego dodawania
	{
		prev_node = prev_node->next;
	}

	Node<T>* next_node = prev_node->next;

	Node<T>* node = new Node<T>{ value };

	node->next = next_node;
	node->prev = prev_node;
	prev_node->next = node;
	next_node->prev = node;

	counter++;
}

template <class T> 
void DoublyLinkedList<T>::removeElementFront() {
	if (counter == 0) {
		return;				//pojedyncze usuniecie poczatkowego elementu 
	}

	Node<T>* node = head;
	head = head->next;

	delete node;

	if (head != nullptr) {
		head->prev = nullptr;
	}

	counter--;
}

template <class T>
void DoublyLinkedList<T>::removeElement(int position) {
	if (counter == 0) {
		return;
	}

	if (position < 0 || position >= counter) {		//warunki aby nie wyjechaæ poza liste
		return;
	}

	if (position == 0)
	{
		removeElementFront();
		return;					//usuwamy tylko jeden element
	}

	else if (position == counter - 1)
	{
		if (counter == 0) {
			return;		//jezeli lista == 0 konczy sie funkcja
		}

		if (counter == 1)
		{
			removeElementFront();		//jezeli lista ma rozmiar 0 usuwa tylko jeden element
			return;
		}

		Node<T>* node = tail;		//przypisanie ostatniej wartosci node i jej usuniecie	
		tail = tail->prev;

		tail->next = nullptr;

		delete node;			//zmniejszenie rozmiaru listy o 1
		counter--;

		return;
	}

	Node<T>* prev_node = head;				//tak samo jak przy wczesniejszych usuwaniach

	for (int i = 0; i < position - 1; ++i)
	{
		prev_node = prev_node->next;
	}

	Node<T>* node = prev_node->next;
	Node<T>* next_node = node->next;

	prev_node->next = next_node;
	next_node->prev = prev_node;

	delete node;
	counter--;
}

template <class T>
int DoublyLinkedList<T>::search(const T& value) const {

	if (counter == 0) {
		return -1;
	}

	int index = 0;

	Node<T>* temp_node = head;			//wyszukiwanie wartosci oraz zwracanie jej pozycji

	while (temp_node->value != value)
	{
		index++;			
		temp_node = temp_node->next;

		if (!temp_node)
		{
			return -1;			//jezeli nie ma szukanej liczby w liscie, zwracamy -1
		}
	}

	return index;			//zwracamy pozycje na jakiej znajduje sie szukana wartosc
}

template <class T>
void DoublyLinkedList<T>::show() const {
	Node<T>* temp_node = head;

	while (temp_node) {
		cout << temp_node->value << "\t";		//funkcja odpowiedzialna za wyswietlenie calej listy
		temp_node = temp_node->next;
	}
	cout << endl;
}

//pomiary czasow dla poszczegolnych algorytmow 

template <class T> 
double DoublyLinkedList<T>::testAddElementHead() {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		addElementHead(5);

		timeSum += stoper.getCounter();

		removeElementFront();
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

template <class T>
double DoublyLinkedList<T>::testAddElementBack(int position) {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		addElementBack(5);

		timeSum += stoper.getCounter();

		removeElement(position);
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

template <class T>
double DoublyLinkedList<T>::testAddElement() {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;
	int position;
	srand(time(NULL));

	for (int i = 0; i < numberOfTests; i++) {
		position = rand() % 30000;

		stoper.startCounter();

		addElement(5, position);

		timeSum += stoper.getCounter();

		removeElement(position);
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

template <class T> 
double DoublyLinkedList<T>::testRemoveElementFront() {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;

	for (int i = 0; i < numberOfTests; i++) {
		stoper.startCounter();

		removeElementFront();

		timeSum += stoper.getCounter();

		addElementHead(3);
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

template <class T> 
double DoublyLinkedList<T>::testRemoveElement(int position) {
	Stoper stoper;

	int numberOfTests = 10000;
	double timeSum = 0;
	double timeAvg = 0;
	srand(time(NULL));

	for (int i = 0; i < numberOfTests; i++) {
		position = rand() % 30000;

		stoper.startCounter();

		removeElement(position);

		timeSum += stoper.getCounter();

		addElement(5, position);
	}

	timeAvg = timeSum / numberOfTests;

	return timeAvg;
}

template <class T> 
void DoublyLinkedList<T>::userInterface() {			//interfejs uzytkownika
	int choise;
	int choise1;
	int value;
	int position;

	do {
		choise = 0;
		choise1 = 0;
		value = 0;
		position = 0;

		cout << "1. Wczytaj elementy z pliku" << endl;
		cout << "2. Wygeneruj losowe elementy" << endl;
		cout << "3. Dodaj element" << endl;
		cout << "4. Usun element" << endl;
		cout << "5. Wyszukaj element" << endl;
		cout << "6. Pokaz liste" << endl;
		cout << "7. Pomiar czasu" << endl;
		cout << "8. Wyjscie" << endl;

		cout << "Wybierz opcje: ";
		cin >> choise;
		cout << endl;

		switch (choise) {
		case 1: {
			readFromFile(0);

			break;
		}
		case 2: {
			cout << endl << "Ile elementow chcesz wygenerowac: ";
			cin >> value;

			generateList(value);

			break;
		}
		case 3: {
			cout << endl << "1. Dodaj element na poczatku" << endl;
			cout << "2. Dodaj element na koncu" << endl;
			cout << "3. Dodaj element na wybranej pozycji" << endl;

			cout << "Wybierz opcje: ";
			cin >> choise1;

			switch (choise1) {
			case 1: {
				cout << endl << "Jaka wartosc chcesz dodac: ";
				cin >> value;

				addElementHead(value);

				break;
			}
			case 2: {
				cout << endl << "Jaka wartosc chcesz dodac: ";
				cin >> value;

				addElementBack(value);
				
				break;
			}
			case 3: {
				cout << endl << "Na jakiej pozycji chcesz dodac wartosc: ";
				cin >> position;

				cout << endl << "Jaka wartosc chcesz dodac: ";
				cin >> value;

				addElement(value, position - 1);
			
				break;
			}
			}
			break;
		}
		case 4: {
			cout << endl << "1. Usun element na poczatku" << endl;
			cout << "2. Usun element na koncu" << endl;
			cout << "3. Usun element na wybranej pozycji" << endl;

			cout << "Wybierz opcje: ";
			cin >> choise1;

			switch (choise1) {
			case 1: {
				removeElementFront();

				break;
			}
			case 2: {
				removeElement(counter - 1);

				break;
			}
			case 3: {
				cout << endl << "Na jakiej pozycji chcesz usunac element: ";
				cin >> position;

				removeElement(position - 1);

				break;
			}
			}
			break;
		}
		case 5: {
			cout << endl << "Jaka wartosc chcesz znalezc: ";
			cin >> value;

			position = search(value);

			if (position == -1) {
				cout << endl << "Nie ma takiej wartosci w liscie" << endl;
			}
			else {
				cout << endl << "Ta wartosc znajduje sie na " << position + 1 << " pozycji" << endl;
			}

			break;
		}
		case 6: {
			show();

			break;
		}
		case 7: {
			generateList(30000);

			cout << "Dodawanie na poczatek listy dla 10000 powtorzen: " << testAddElementHead() << " ns" << endl;
			cout << "Dodawanie na koniec listy dla 10000 powtorzen: " << testAddElementBack(counter - 1) << " ns" << endl;
			cout << "Dodawanie na losowej listy dla 10000 powtorzen: " << testAddElement() << " ns" << endl << endl;

			cout << "Usuniecie elementu z poczatku listy dla 10000 powtorzen: " << testRemoveElementFront() << " ns" << endl;
			cout << "Usuniecie elementu z konca listy dla 10000 powtorzen: " <<testRemoveElement(counter - 1) << " ns" << endl;
			cout << "Usuniecie elementu ze srodka listy dla 10000 powtorzen: " << testRemoveElement(5) << " ns" << endl;

			break;
		}
		}
	} while (choise != 8);
}

#endif // !DOUBLY_ LINKED_LIST