#include "GrafLista.h"
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Tree.h"


#define INF 10000 //definicja 'nieskonczonosci'


GrafLista::GrafLista(int vertices, int edges, int start_vertices)
{
	this->edges = edges;
	this->vertices = vertices;
	this->start_vertices = start_vertices;

	//wagi = new int[edges];
	//lista= new int*[edges];
	//for (int i = 0; i < edges; i++) lista[i] = new int[3];
}

void GrafLista::MSTlist(int poczatek, int koniec, int waga) {

	Edge edge;
	edge.vertex1 = poczatek;
	edge.vertex2 = koniec;
	edge.value = waga;

	list.push_back(edge);

	edge.vertex2 = poczatek;
	edge.vertex1 = koniec;
	edge.value = waga;

	list.push_back(edge);
}

void GrafLista::SCIEZKAlist(int poczatek, int koniec, int waga) {

	Edge edge;
	edge.vertex1 = poczatek;
	edge.vertex2 = koniec;
	edge.value = waga;

	list.push_back(edge);
}


void GrafLista::Show()
{
	cout << endl << "Lista sasiedztwa grafu: " << endl;

	for (std::list<Edge>::iterator i = list.begin(); i != list.end(); ++i) {
		cout << i->vertex1 << "-" << i->vertex2 << ": " << i->value << endl;
	}

}

void GrafLista::algorytmKruskala()
{
	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();


	for (std::list<Edge>::iterator i = list.begin(); i != list.end(); ++i) {

		for (int k = 0; k < list.size(); k++) {

			edge.value = i->value;
			edge.vertex1 = i->vertex1;
			edge.vertex2 = i->vertex2;

			queue->add(edge);
		}

	}

	cout << endl << "ALGORYTM KRUSKALA" << endl;
	queue->sortHeap();
	while (tree->completedTree(vertices) == false)
	{
		edge = queue->removeEdge();
		tree->addEdge(edge);
		cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;
	}
	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;
}

void GrafLista::algorytmPrima()
{
	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();

	cout << endl << "ALGORYTM PRIMA" << endl;

	std::list<Edge>::iterator i = list.begin();
	while (tree->completedTree(vertices) == false)
	{
		edge.vertex1 = i->vertex1;

		for (std::list<Edge>::iterator j = list.begin(); j != list.end(); ++j) {
			if (j->vertex1 == edge.vertex1) {

				edge.value = j->value;
				edge.vertex2 = j->vertex2;

				queue->add(edge);

			}
		}
		queue->sortHeap(); //sortuje wedlug danego wierzcholka (i=0) || sortuje krawedzie zebrane dotychcasz
		edge = queue->removeEdge(); //wybiera najelpsza sciezke
		tree->addEdge(edge); //dodaje
		cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;

		i = list.begin();
		for (std::list<Edge>::iterator j = list.begin(); j != list.end(); ++j) {
			if (j->vertex1 != edge.vertex2)
				i++;
			else {
				j = list.end();
				j--;
			}
		}

	}

	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;
}

void GrafLista::algorytmFordaBellmana(int firstVertex, int lastVertex)
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
			for (std::list<Edge>::iterator j = list.begin(); j != list.end(); ++j) {

				edge.value = j->value;
				edge.vertex1 = j->vertex1;
				edge.vertex2 = j->vertex2;

				if (tab[edge.vertex2] > tab[edge.vertex1] + edge.value)		// jezeli dlugosc sciezki krotszej jest wieksza niz dlugosc sciezki po wiekszej ilosci krawedzi
				{
					tab[edge.vertex2] = tab[edge.vertex1] + edge.value;
				}
			}

	}

	cout << endl << "ALGORYTM FORDA BELLMANA" << endl;
	cout << endl << "Najkrotsze sciezki: " << endl;
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

	cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " << endl << firstVertex << "-"
		<< lastVertex << ": " << tab[lastVertex] << endl;

	delete[]tab;
}

GrafLista::~GrafLista()
{
	//for (int i = 0; i < edges; i++)
	//	delete[] list[i];

	//delete[] lista;
	//delete[] wagi;
}
