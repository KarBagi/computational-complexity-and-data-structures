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
	void removeElement(int position);
	int findElement(int value);
	void generateArray(int value);
	void readFromFile();
	void showArray();

	void userInterface();
};