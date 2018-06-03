#pragma once
#include "Edge.h"

class Tree
{
private:
	Edge * head;
	int size;									// dla minimalnego drzewa rozpinajacego w formie listy
public:
	Tree(void);
	Tree(int size);
	bool completedTree(int vertices);
	void addEdge(Edge edge);					// funkcja wywola funkcje powiekszenia listy wowczas dopisana zostaje nowa krawedz
	void sort();
	void sortValues();
	int sumValues();							// Funkcja zwraca nam calkowita wage drzewa/listy jesli jest ukonczne
	void showTree();
	~Tree(void);
};