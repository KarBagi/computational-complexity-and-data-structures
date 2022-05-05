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
	void readFromFile(int fileN);
	void showArray();
	double testAddElementToFront();
	double testAddElementToEnd(int position);
	double testAddElement();
	double testRemoveElementFront();
	double testRemoveElementEnd(int position);
	double testRemoveElement();

	void userInterface();
};