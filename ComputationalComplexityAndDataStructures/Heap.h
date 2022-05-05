#pragma once
#include <string>

using namespace std;

class Heap {
	int* heap = { nullptr };
	int size = 0;
	void heapify(int position);
	void repairHeap();
	int parent(int position);
	int leftChild(int position);
	int rightChild(int position);

public:
	void add(int value);
	void remove();
	void search(int value);
	void readFromFile(int fileN);
	string show();
	void generateRandomData(int value);
	void userInterface();	
	double testAdd();
	double testRemove();
};
