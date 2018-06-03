#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <vector>
#include <list>
#include <iterator>

using namespace std;

class GrafLista
{
private:
	Vertex vertex; //wierzcholek

	int edges;
	int vertices;
	int start_vertices;
	int cost;	//koszt
	int firstVertex, lastVertex;

public:
	//int * wagi;
	//int ** lista;
	list<Edge> list;
	GrafLista(int vertices, int edges, int start_vertices);
	~GrafLista();

	void MSTlist(int poczatek, int koniec, int waga);
	void SCIEZKAlist(int poczatek, int koniec, int waga);
	void Show();

	void algorytmKruskala();
	void algorytmPrima();
	void algorytmDijkstry(int firstVertex, int lastVertex);
	void algorytmFordaBellmana(int firstVertex, int lastVertex);

};

