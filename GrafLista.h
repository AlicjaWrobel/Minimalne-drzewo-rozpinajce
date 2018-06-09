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

	int edges; //ilosc krawedzi
	int vertices; //ilosc wierzcholkow
	int cost;	//koszt
	int firstVertex, lastVertex;  // wierzcholki podane na wejsciu potrzebne przy wznaczaniu najkrotszej sciezki


public:
	list<Edge> list; //lista wierzcholkow
	GrafLista(int vertices, int edges);
	~GrafLista();

	void MSTlist(int poczatek, int koniec, int waga); //lista dla MST
	void SCIEZKAlist(int poczatek, int koniec, int waga); //lista dla sciezki
	void Show(); //wyswietlenie listy

	void algorytmKruskala();
	void algorytmPrima();
	void algorytmDijkstry(int firstVertex, int lastVertex);
	void algorytmFordaBellmana(int firstVertex, int lastVertex);

};

