#pragma once

class DynamicArray {
	int size;
	int* mainArray;

public:
	DynamicArray(int size);
	~DynamicArray();

	void addElementToFront(int value, int repeat);
	void addElementToEnd(int value, int repeat);
	void addElement(int value, int position, int repeat);
	void removeElement(int position, int repeat);
	int findElement(int value, int repeat);
	void generateArray(int value);
	void readFromFile();
	void showArray();

	void userInterface();
};