#include <iostream>
#include <windows.h>
#include "DynamicArray.h"
#include "DoublyLinkedList.h"

using namespace std;

int main() {
    int choise = 0;

    do {      // nieskonczona petla zeby program sie sam nie wylaczal
        choise = 0;

        DynamicArray dynArr(0);          //towrzymy obiekt dynArr klasy DynamicArray z 1000-cioma elementami
        DoublyLinkedList<int> list{};       //tworzymy obiekt list klasy DoublyLinkedList
        //Heap heap;

        cout << "1. Dynamiczna tablica" << endl;
        cout << "2. Lista dwukierunkowa" << endl;
        cout << "3. Kopiec" << endl;
        cout << "4. Wyjscie" << endl;

        cout << "Wybierz opcje: ";
        cin >> choise;

        switch (choise) {
        case 1: system("cls"); dynArr.userInterface(); break;       //uruchamiamy interfejs 
        case 2: system("cls"); list.userInterface(); break;         //uzytkownika poszczegolnych klas
        //case 3: heap.userInterface(); getchar(); break;
        }
    } while (choise != 4);

    return 0;
}