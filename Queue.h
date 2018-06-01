#pragma once
#include <vector>
#include "Edge.h"
#include "Vertex.h"
using namespace std;

class Queue
{
private:
	vector<Edge> tab; //kolejka
	vector<Edge> count_tab; //przechwuje elementy, które ju¿ wyst¹pi³y

	vector<Vertex> tab2; //kolejka
	vector<Vertex> count_tab2; //przechwuje elementy, które ju¿ wyst¹pi³y
	bool heap;
public:
	Queue();
	void addEdge(Edge edge); //dodaje krawedzi
	bool add(Edge edge); //dodaje krawedz po sprawdzeniu czy wystapila
	void addAppeared(Edge edge); // dodaje krawedz do listy wystapien
	void sortHeap(); //przywracania wlasnosci kopca min
	Edge removeEdge(); //usuwa element

	void addVertex(Vertex vertex); //dodaje wiercholek
	bool add(Vertex vertex); //dodaje wiercholek po sprawdzeniu czy wystapil
	void addAppeared(Vertex vertex); // dodaje wiercholek do listy wystapien
	Vertex removeVertex(); //usuwa element

	int size(); // rozmiar kolejki krawedzi
	void showQueue();

	int size2(); // rozmiar kolejki wierzcholkow
	void showQueue2();

	~Queue();
};

