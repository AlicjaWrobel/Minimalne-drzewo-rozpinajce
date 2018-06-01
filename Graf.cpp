#include "Graf.h"
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Tree.h"

#define INF INT_MAX //definicja nieskonczonosci

using namespace std;

Graf::Graf(int vertices, int edges, int start_vertices)
{
	this->edges = edges;
	this->vertices = vertices;
	this->start_vertices = start_vertices;

	macierz = new int*[vertices];
	wagi = new int[edges];

	usedVertices = new bool[vertices];
	minCost = new int[vertices];
	preVertex = new int[vertices];

}

void Graf::newIncidneceMatrix()
{
	for (int i = 0; i < vertices; i++)
		macierz[i] = new int[edges];

	for (int i = 0; i < vertices; i++) 
		for (int j = 0; j < edges; j++) 
			macierz[i][j] = 0;
}

void Graf::SCIEZKAincidneceMatrix(int poczatek, int koniec, int waga, int i) {

	macierz[poczatek][i] = 1;
	macierz[koniec][i] = -1;
	wagi[i] = waga;

}

void Graf::MSTincidneceMatrix(int poczatek, int koniec, int waga, int i) {

	macierz[poczatek][i] = 1;
	macierz[koniec][i] = 1;
	wagi[i] = waga;

}

void Graf::showIncidneceMatrix() {
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

void Graf::algorytmKruskala() {

	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++) {

			if (macierz[j][i] == 1) {

				for (int n = j+1; n < vertices; n++) {

					if (macierz[n][i] == 1) {

						queue->add(Edge(j, n, wagi[i], 0));
						n = vertices;
					}

				}
			}
		}
	}

	cout <<endl<<"ALGORYTM KRUSKALA"<<endl;
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

void Graf::algorytmPrima()
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

						queue->add(Edge(i,n,wagi[j],0));
						n = vertices;
					}

				}
			}
		}

		queue->sortHeap(); //sortuje wedlug danego wierzcholka (i=0) || sortuje krawedzie zebrane dotychcasz
		edge = queue->removeEdge(); //wybiera najelpsza sciezke
		tree->addEdge(edge); //dodaje
		cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;
		i = edge.vertex2; //idziemy do wiercholka kolejnego
	}

	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;
}

void Graf::algorytmDijkstry(int firstVertex, int lastVertex)
{
	vector<Edge> usedEdges; //uzyte
	vector<Edge> notUsedEdges; //nie uzyte
	//Vertex selectedVertex;
	Edge selecteEdge; //aktualna krawedz

	for (int i = 0; i < vertices; i++) {

		//usedVertices[i] = false;
		minCost[i] = INF;
		preVertex[i] = -1;
	}

	minCost[firstVertex] = 0;

	for (int i = 0; i < vertices; i++) notUsedEdges.push_back(Edge(i, preVertex[i], minCost[i],0));

	//selecteEdge.vertex1 = firstVertex;
	usedEdges.push_back(Edge(0, firstVertex, 0, 0));
	selecteEdge = usedEdges.front();
	notUsedEdges.erase(usedEdges.begin());

	while (usedEdges.size() > 0)			
	{

	}


	/*for (int i = 0; i < vertices; i++) queue->add(Vertex(minCost[i], i, preVertex[i]));
	
	for (int x = 0; x < vertices; x++) {
		selectedVertex.index = firstVertex;
		//
		selecteEdge.vertex1 = selectedVertex.index;

		if ((selectedVertex.value == minCost[selectedVertex.index]) && (selectedVertex.previous == preVertex[selectedVertex.index])) {
			if (!usedVertices[selectedVertex.index]) {
				usedVertices[selectedVertex.index] = true;
				for (int i = 0; i < vertices; i++)
					if (macierz[selectedVertex.index][i] != INF)
						usedEdges.insert(usedEdges.begin() + usedEdges.size(),
							Edge(selectedVertex.index, i, macierz[selectedVertex.index][i],0));
				for (int i = 0; i < usedEdges.size(); i++) {
					if (minCost[usedEdges[i].vertex2] >(minCost[selectedVertex.index] + usedEdges[i].value)) {
						minCost[usedEdges[i].vertex2] = (minCost[selectedVertex.index] + usedEdges[i].value);
						preVertex[usedEdges[i].vertex2] = selectedVertex.index;
						//cout << "\nDla " << usedEdges[i].node2 << " minimalny koszt dojscia to " << minimalCost[usedEdges[i].node2] << " a poprzedni wiercholek to " << previousNodes[usedEdges[i].node2];
						queue->add(Vertex(minCost[usedEdges[i].vertex2], usedEdges[i].vertex2, selectedVertex.index));
					}
				}
				usedEdges.clear();
			}
			queue->removeVertex();

			if (queue->size() > 0)
				selectedVertex.index = selecteEdge.vertex2;
			else break;
		}
		else {
			queue->removeVertex();
			queue->add(Vertex(minCost[selectedVertex.index], selectedVertex.index, preVertex[selectedVertex.index]));
			x--;
		}
	
	}*/


}


Graf::~Graf()
{
	for (int i = 0; i<vertices; i++)
		delete[] macierz[i];

	delete[] macierz;
	delete[] wagi;
	
	delete[]usedVertices;
	delete[]minCost;
	delete[]preVertex;

}
