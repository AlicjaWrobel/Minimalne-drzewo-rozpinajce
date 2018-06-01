#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <vector>
using namespace std;

class Graf
{
private:
	Vertex vertex; //wierzcholek

	int edges;
	int vertices;
	int start_vertices;
	int cost;	//koszt
	int firstVertex, lastVertex;

	bool* usedVertices;
	int* minCost;
	int* preVertex;
public:
	int ** macierz;
	int ** macierz_pomocy;
	int ** lista;
	int * wagi;
	Graf(int vertices, int edges,  int start_vertices); //konstruktor

	void newIncidneceMatrix();
	void MSTincidneceMatrix(int poczatek, int koniec, int waga, int i);
	void SCIEZKAincidneceMatrix(int poczatek, int koniec, int waga, int i);
	void showIncidneceMatrix();

	void algorytmKruskala();
	void algorytmPrima();
	void algorytmDijkstry(int firstVertex, int lastVertex);

	~Graf(); //destruktor
};