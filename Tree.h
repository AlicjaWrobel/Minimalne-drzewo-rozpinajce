#pragma once
#include "Edge.h"

class Tree
{
private:
	Edge * head;
	int size;
public:
	Tree();
	Tree(int size);
	bool completedTree(int vertices); //sprawdza czy drzewo kompletne
	void addEdge(Edge edge);		// dopisanie nowej krawedzi 
	int sumValues();			// zwraca wage drzewa
	~Tree();
};