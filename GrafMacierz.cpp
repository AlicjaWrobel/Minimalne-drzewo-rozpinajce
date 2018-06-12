#include "GrafMacierz.h"
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Tree.h"
#include <queue>

#define INF 1000000 //definicja 'nieskonczonosci'

using namespace std;

GrafMacierz::GrafMacierz(int vertices, int edges)
{
	this->edges = edges;
	this->vertices = vertices;

	macierz = new int*[vertices];
	wagi = new int[edges];

}

void GrafMacierz::newIncidneceMatrix()
{
	for (int i = 0; i < vertices; i++)
		macierz[i] = new int[edges];

	for (int i = 0; i < vertices; i++)
		for (int j = 0; j < edges; j++)
			macierz[i][j] = 0;
}

void GrafMacierz::SCIEZKAincidneceMatrix(int poczatek, int koniec, int waga, int i) {

	macierz[poczatek][i] = 1;
	macierz[koniec][i] = -1;
	wagi[i] = waga;

}

void GrafMacierz::MSTincidneceMatrix(int poczatek, int koniec, int waga, int i) {

	macierz[poczatek][i] = 1;
	macierz[koniec][i] = 1;
	wagi[i] = waga;

}

void GrafMacierz::showIncidneceMatrix() {
	cout << "   ";
	for (int j = 0; j < edges; j++)
		cout << setw(3) << j;

	cout << endl;
	cout << endl;

	for (int i = 0; i < vertices; i++) {
		cout << setw(3) << i;
		for (int j = 0; j < edges; j++)
			cout << setw(3) << macierz[i][j];
		cout << endl;
	}

}

void GrafMacierz::algorytmKruskala() {

	createConnected();
	clearConnected();
	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();
	bool* visited = new bool[vertices];

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++) {

			if (macierz[j][i] == 1) {

				for (int n = j + 1; n < vertices; n++) {

					if (macierz[n][i] == 1) {

							queue->add(Edge(j, n, wagi[i], 0));
							n = vertices;
					
					}

				}
			}
		}
	}

	cout << endl << "ALGORYTM KRUSKALA" << endl;

	queue->sortHeap();
	//queue->bubblesort();
	while (tree->completedTree(vertices) == false)
	{

		edge = queue->removeEdge();
		if (canBeAdded(edge)) {
			addToConnected(edge);
			tree->addEdge(edge);
			cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;
		}
	}
	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;

	delete queue;
	delete tree;

}

void GrafMacierz::algorytmPrima()
{
	int i = 0;

	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();

	cout << endl << "ALGORYTM PRIMA" << endl;
	while (tree->completedTree(vertices) == false)
	{
		for (int j = 0; j < edges; j++) {

			if (macierz[i][j] == 1) {

				for (int n = 0; n < vertices; n++) {

					if (n == i) {
						n++;
					}
					if (macierz[n][j] == 1) {

						queue->add(Edge(i, n, wagi[j],0));
						n = vertices;
					}

				}
			}
		}

		queue->sortHeap(); //sortuje wedlug danego wierzcholka (i=0) || sortuje krawedzie zebrane dotychcasz
		queue->bubblesort();
		edge = queue->removeEdge(); //wybiera najelpsza sciezke
		tree->addEdge(edge); //dodaje
		cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;
		i = edge.vertex2; //idziemy do wiercholka kolejnego
	}

	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;

	delete queue;
	delete tree;
}


void GrafMacierz::algorytmDijkstry(int firstVertex, int lastVertex)
{

	vector<Edge> Edges(vertices); // nieuzyte
	int *UsedEdges = new int[vertices]; //uzyte
	Edge selectedEdge; //aktualna krawedz

	selectedEdge.value = INF;

	for (int i = 0; i < vertices; i++) {

		selectedEdge.vertex2 = i;
		Edges[i] = selectedEdge;
	}

	selectedEdge.value = 0;
	selectedEdge.vertex2 = firstVertex;
	Edges[firstVertex] = selectedEdge;

	while (Edges.size() > 0)
	{
		int cost;
		int startCost;
		int index;
		Edge wsk;

		for (int i = 0; i < Edges.size(); i++)
			for (int j = 0; j<Edges.size() - 1; j++)
			{
				if (Edges[j].value > Edges[j + 1].value)
				{
					wsk = Edges[j];
					Edges[j] = Edges[j + 1];
					Edges[j + 1] = wsk;
				}
			}

		selectedEdge = Edges[0];
		Edges.erase(Edges.begin());
		index = selectedEdge.vertex2;
		startCost = selectedEdge.value;
		UsedEdges[index] = selectedEdge.value;

		for (int j = 0; j < edges; j++) {
			if (macierz[index][j] == 1) {

				for (int n = 0; n < vertices; n++) {

					if (macierz[n][j] == -1) {

						selectedEdge = Edge(0, n, wagi[j],0);
						cost = selectedEdge.value + startCost;

						int i = 0;
							for (int z = 0; z<Edges.size(); z++)
							{
								if (Edges[z].vertex2 == selectedEdge.vertex2) {
									i = z;
									z = Edges.size();
								}
								else {
									i = -1;
								}
							}

						if(i >=0 && Edges.size() != 0)
						if (Edges[i].value > cost)
						{
							selectedEdge.value = cost;
							Edges[i] = selectedEdge;
						}

						n = vertices;
					}

				}

			}
		}

	}

	cout << endl << "ALGORYTM DIJKSTRY" << endl;
	cout << endl << "Najkrotsze sciezki: " << endl;
	for (int i = 0; i < vertices; i++)
	{
		cout << setw(3) << firstVertex << "-" << i << ":";
		if (UsedEdges[i] == 1000000)
		{
			cout << setw(3) << "*" << endl;
		}
		else
		{
			cout << setw(3) << UsedEdges[i] << endl;
		}
	}

	if (lastVertex>vertices-1) {
		cout << endl << "Dany wierzcholek nie istnieje" << endl;
	}
	else {
		cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " << endl << firstVertex << "-"
			<< lastVertex << ": " << UsedEdges[lastVertex] << endl;
	}
	delete[]UsedEdges;
}

void GrafMacierz::algorytmFordaBellmana(int firstVertex, int lastVertex)
{

	int *tab = new int[vertices];	// wektor aktulanych wag
	Edge edge;
	for (int i = 0; i < vertices; i++)
	{
		tab[i] = INF;
	}

	tab[firstVertex] = 0;
	for (int i = 0; i < vertices - 1; i++)  //tyle razy zeby znalezc jak najkrótsz¹ scie¿kê, -1 bo pomijamy startowy wierzcholek
	{
		for (int p = 0; p < vertices; p++)
			for (int j = 0; j < edges; j++)
			{
				if (macierz[p][j] == 1)
				{
					for (int k = 0; k < vertices; k++)
					{
						if (macierz[k][j] == -1)
						{
							edge = Edge(p, k, wagi[j],0);

							if (tab[edge.vertex2] > tab[edge.vertex1] + edge.value)		// jezeli dlugosc sciezki krotszej jest wieksza niz dlugosc sciezki po wiekszej ilosci krawedzi
							{
								tab[edge.vertex2] = tab[edge.vertex1] + edge.value;
							}
							k = vertices;
						}
					}
				}
			}

	}

	cout << endl << "ALGORYTM FORDA BELLMANA" <<endl;
	cout << endl << "Najkrotsze sciezki: " << endl ;
	for (int i = 0; i < vertices; i++)
	{
		cout << setw(3) << firstVertex << "-" << i << ":";
		if (tab[i] == 1000000)
		{
			cout << setw(3) << "*" << endl;
		}
		else
		{
			cout << setw(3) << tab[i] << endl;
		}
	}

	if (lastVertex>vertices - 1) {
		cout << endl << "Dany wierzcholek nie istnieje" << endl;
	}
	else {
		cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " << endl << firstVertex << "-"
			<< lastVertex << ": " << tab[lastVertex] << endl;
	}

	delete[]tab;

}

void GrafMacierz::createConnected() {
	for (int i = 0; i < vertices; i++) {
		connected[i] = new bool[vertices];
	}
}

void GrafMacierz::clearConnected() {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			connected[i][j] = false;
		}
	}
	for (int i = 0; i < vertices; i++) {
		connected[i][i] = true;
	}
}


void GrafMacierz::addToConnected(Edge edge) {
	connected[edge.vertex1][edge.vertex1] = true;
	for (int i = 0; i < vertices; i++) {
		if (connected[edge.vertex1][i]) {
			connected[edge.vertex2][i] = true;
		}
		if (connected[edge.vertex2][i]) {
			connected[edge.vertex1][i] = true;
		}
	}
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			if (connected[i][j])
				for (int k = 0; k < vertices; k++) {
					if (connected[i][k])
						connected[j][k] = true;
				}
		}
	}

}

bool GrafMacierz::canBeAdded(Edge edge) {
	if (connected[edge.vertex1][edge.vertex2])
		return false;
	else if (connected[edge.vertex2][edge.vertex1])
		return false;
	else
		return true;
}


GrafMacierz::~GrafMacierz()
{
	for (int i = 0; i < vertices; i++)
		delete[] macierz[i];

	delete[] macierz;
	delete[] wagi;

}
