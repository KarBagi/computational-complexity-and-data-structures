#pragma once

class DynamicArray {
	int size;
	int* mainArray;

public:
	DynamicArray(int size);
	~DynamicArray();

	void addElementToFront(int value);
	void addElementToEnd(int value);
	void addElement(int value, int position);
	void deleteElement();
	void generateArray();
	void readFromFile();
	void showArray();

	void userInterface();
};