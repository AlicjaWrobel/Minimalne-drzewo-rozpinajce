#pragma once
#include "Edge.h"
#include "Vertex.h"
#include <vector>
using namespace std;

class GrafMacierz
{
private:
	Vertex vertex; //wierzcholek

	int edges; //ilosc krawedzi
	int vertices; //ilosc wierzcholkow
	int cost;	//koszt
	int firstVertex, lastVertex; // wierzcholki podane na wejsciu potrzebne przy wznaczaniu najkrotszej sciezki

public:
	int ** macierz; //macierz wartosci
	int * wagi; //tablica wag
	GrafMacierz(int vertices, int edges); //konstruktor
	//GrafMacierz(string sciezka, bool typ);

	void newIncidneceMatrix(); //tworzenie macierzy i wypelnienie jej zerami
	void MSTincidneceMatrix(int poczatek, int koniec, int waga, int i); //macierz dla MST
	void SCIEZKAincidneceMatrix(int poczatek, int koniec, int waga, int i); //macierz dla sciezki
	void showIncidneceMatrix(); //wyswietlenie macierzy 
	
	bool canBeAdded(Edge edge);
	void createConnected();
	void clearConnected();
	bool ** connected = new bool *[vertices];
	void addToConnected(Edge edge);

	void algorytmKruskala();
	void algorytmPrima();
	void algorytmDijkstry(int firstVertex, int lastVertex);
	void algorytmFordaBellmana(int firstVertex, int lastVertex);

	~GrafMacierz(); //destruktor
};