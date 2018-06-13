#include "GrafLista.h"
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Tree.h"
#include <queue>


#define INF 1000000 //definicja 'nieskonczonosci'


GrafLista::GrafLista(int vertices, int edges)
{
	this->edges = edges;
	this->vertices = vertices;

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
	std::vector<std::list<Edge>> listGraph2(vertices);

	for (std::list<Edge>::iterator i = list.begin(); i != list.end(); ++i) {
		listGraph2[i->vertex1].push_back(Edge(i->vertex1, i->vertex2, i->value, 0));
	}

	for (int i = 0; i < vertices; i++) {
		cout << "\nWiercholek " << i << ": ";
		for (std::list<Edge>::iterator iter = listGraph2[i].begin(); iter != listGraph2[i].end(); ++iter) {
			cout << "->" << iter->vertex2 << ":" << iter->value << " ";
		}
	}
	cout << "\n";
}

void GrafLista::algorytmKruskala()
{
	createConnected();
	clearConnected();
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
	queue->bubblesort();
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
		queue->bubblesort();
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

	delete queue;
	delete tree;
}

struct compareNodes {
	bool operator()(Vertex x, Vertex y)
	{
		if (x.value > y.value) return true;
		return false;
	}
};

typedef std::priority_queue <Vertex, std::vector <Vertex>, compareNodes> VertexQueue;

void GrafLista::algorytmDijkstry(int firstVertex, int lastVertex)
{
	vector<bool> usedvertices(vertices);
	vector<int> minimalCost(vertices);
	vector<int> previousvertices(vertices);

	for (int i = 0; i < vertices; i++) {
		usedvertices[i] = false;
		minimalCost[i] = INF;
		previousvertices[i] = -1;
	}

	vector<std::list<Edge>> listGraph2(vertices);
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		listGraph2[iter->vertex1].push_back(Edge(iter->vertex1, iter->vertex2, iter->value, 0));
	}

	minimalCost[firstVertex] = 0;
	vector<Edge> usedEdges;
	VertexQueue mojaKolejka;
	Vertex selectedVertex;
	for (int i = 0; i < vertices; i++) mojaKolejka.push(Vertex(minimalCost[i], i, previousvertices[i]));
	for (int x = 0; x < vertices; x++) {
		selectedVertex = mojaKolejka.top();
		if ((selectedVertex.value == minimalCost[selectedVertex.index]) && selectedVertex.previous == previousvertices[selectedVertex.index]) {
			if (!usedvertices[selectedVertex.index]) {
				usedvertices[selectedVertex.index] = true;

				for (std::list<Edge>::iterator iter = listGraph2[selectedVertex.index].begin(); iter != listGraph2[selectedVertex.index].end(); ++iter)
					usedEdges.insert(usedEdges.begin() + usedEdges.size(), Edge(*iter));
				for (int i = 0; i < usedEdges.size(); i++) {
					if (minimalCost[usedEdges[i].vertex2] >(minimalCost[selectedVertex.index] + usedEdges[i].value)) {
						minimalCost[usedEdges[i].vertex2] = (minimalCost[selectedVertex.index] + usedEdges[i].value);
						previousvertices[usedEdges[i].vertex2] = selectedVertex.index;
						mojaKolejka.push(Vertex(minimalCost[usedEdges[i].vertex2], usedEdges[i].vertex2, selectedVertex.index));
					}
				}
				usedEdges.clear();
			}
			mojaKolejka.pop();

			if (mojaKolejka.size() > 0)
				selectedVertex = mojaKolejka.top();
			else break;
		}
		else {
			mojaKolejka.pop();
			mojaKolejka.push(Vertex(minimalCost[selectedVertex.index], selectedVertex.index, previousvertices[selectedVertex.index]));
			x--;
		}
	}

	cout << endl << "ALGORYTM DIJKSTRY" << endl;
	cout << endl << "Najkrotsze sciezki: " << endl;
	for (int i = 0; i < vertices; i++)
	{
		cout << setw(3) << firstVertex << "-" << i << ":";
		if (minimalCost[i] == 1000000)
		{
			cout << setw(3) << "*" << endl;
		}
		else
		{
			cout << setw(3) << minimalCost[i] << endl;
		}
	}

	if (lastVertex>vertices - 1) {
		cout << endl << "Dany wierzcholek nie istnieje" << endl;
	}
	else {
		cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " << endl << firstVertex << "-"
			<< lastVertex << ": " << minimalCost[lastVertex] << endl;
	}

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

	if (lastVertex>vertices - 1) {
		cout << endl << "Dany wierzcholek nie istnieje" << endl;
	}
	else {
		cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " << endl << firstVertex << "-"
			<< lastVertex << ": " << tab[lastVertex] << endl;
	}

	delete[]tab;
}

void GrafLista::createConnected() {
	for (int i = 0; i < vertices; i++) {
		connected[i] = new bool[vertices];
	}
}

void GrafLista::clearConnected() {
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			connected[i][j] = false;
		}
	}
	for (int i = 0; i < vertices; i++) {
		connected[i][i] = true;
	}
}


void GrafLista::addToConnected(Edge edge) {
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

bool GrafLista::canBeAdded(Edge edge) {
	if (connected[edge.vertex1][edge.vertex2])
		return false;
else if (connected[edge.vertex2][edge.vertex1])
		return false;
	else
		return true;
}

GrafLista::~GrafLista()
{

}
