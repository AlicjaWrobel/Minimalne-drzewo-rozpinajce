#include "GrafMacierz.h"
#include <iostream>
#include <iomanip>
#include "Queue.h"
#include "Tree.h"

#define INF 10000 //definicja 'nieskonczonosci'

using namespace std;

GrafMacierz::GrafMacierz(int vertices, int edges, int start_vertices)
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

	Edge edge;
	Queue *queue = new Queue();
	Tree *tree = new Tree();

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
	while (tree->completedTree(vertices) == false)
	{
		edge = queue->removeEdge();
		tree->addEdge(edge);
		cout << edge.vertex1 << "-" << edge.vertex2 << ": " << edge.value << endl;
	}
	cout << endl << "suma wag:" << endl;
	cout << tree->sumValues() << endl;
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

						queue->add(Edge(i, n, wagi[j], 0));
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

void GrafMacierz::algorytmDijkstry(int firstVertex, int lastVertex)
{

	vector<Edge> Edges; // nieuzyte
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
		int cost = 0;
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

		selectedEdge = Edges.front();
		Edges.erase(Edges.begin());
		index = selectedEdge.vertex2;
		startCost = selectedEdge.value;
		UsedEdges[index] = selectedEdge.value;

		for (int j = 0; j < edges; j++) {
			if (macierz[index][j] == 1) {

				for (int n = 0; n < vertices; n++) {

					if (macierz[n][j] == -1) {

						selectedEdge = Edge(0, n, wagi[j], 0);
						cost = selectedEdge.value + startCost;

						int i;
						bool check = 1;
						if (check == 1) {
							for (i = 0; i < Edges.size(); i++)
							{
								if (Edges[i].value == selectedEdge.vertex2)
									check = 0;
							}
						}

						if (Edges[i].value > cost)		// Macierz incydencji spisuje sie tu
						{														// bardzo slabo, o wiele lepiej w tym 			
							selectedEdge.value = cost;					// przypadku bedzie dzialac lista
							Edges[i] = selectedEdge;		// sasiedztwa
						}

						n = vertices;
					}

				}

			}
		}

		//queue->sortHeap();
		//selectedEdge = queue->removeEdge(); //wybiera najelpsza sciezke
		//usedEdges.push_back(selectedEdge); //dodaje
		//notUsedEdges.pop_back();

		//selecteEdge = usedEdges.back();

	}

	cout << "\n\n--- ALGORYTM DIJKSTRY ---\n";
	cout << endl << "Najkrotsze sciezki miedzy wierzcholkami : " << endl;
	for (int i = 0; i<vertices; i++)
	{
		cout << setw(3) << i << "|";
		if (UsedEdges[i] == 1000000)
		{
			cout << setw(3) << "*" << endl;
		}
		else
		{
			cout << setw(3) << UsedEdges[i] << endl;
		}
	}
	cout << endl << "Najkrotsza sciezka w grafie pomiedzy: " << firstVertex << "-"
		<< UsedEdges << " wynosi:  ---" << UsedEdges[lastVertex] << "---";
	delete[]UsedEdges;

	/*vector<Edge> usedEdges; // nieuzyte
	Queue *queue = new Queue();
	Vertex selectedVertex; //aktualny wierzcholek

	for (int i = 0; i < vertices; i++) {

		usedVertices[i] = false;
		preVertex[i] = -1;
		minCost[i] = INF;
	}

	minCost[firstVertex] = 0;

	//for (int i = vertices-1; 0 <= i; i--) queue->add(Vertex(minCost[i], i, preVertex[i]));
	for (int i = 0; i < vertices; i++) queue->add(Vertex(minCost[i], i, preVertex[i]));
	for (int x = 0; x < vertices; x++) {
		selectedVertex = queue->lastVertex();

		if ((selectedVertex.value == minCost[selectedVertex.index]) && (selectedVertex.previous == preVertex[selectedVertex.index])) {
			if (!usedVertices[selectedVertex.index]) {
				usedVertices[selectedVertex.index] = true;

				for (int i = 0; i < edges; i++)
					if (macierz[selectedVertex.index][i] == 1)
						for (int n = 0; i < edges; n++)
							if (macierz[n][i] == -1)
								usedEdges.insert(usedEdges.begin() + usedEdges.size(), Edge(selectedVertex.index, n, wagi[i], 0));

				for (int i = 0; i < usedEdges.size(); i++) {
					if (minCost[usedEdges[i].vertex2] > (minCost[selectedVertex.index] + usedEdges[i].value)) {
						minCost[usedEdges[i].vertex2] = (minCost[selectedVertex.index] + usedEdges[i].value);
						preVertex[usedEdges[i].vertex2] = selectedVertex.index;
						queue->add(Vertex(minCost[usedEdges[i].vertex2], usedEdges[i].vertex2, selectedVertex.index));
					}
				}
				usedEdges.clear();
			}
			queue->removeVertex();

			if (queue->size() > 0)
				selectedVertex = queue->lastVertex();
			else break;
		}
		else {
			queue->removeVertex();
			queue->add(Vertex(minCost[selectedVertex.index], selectedVertex.index, preVertex[selectedVertex.index]));
			x--;
		}

	}

	for (int i = 0; i < vertices; i++) {
		int x = i;
		cout << "\nWierzcholek " << i << ": ";
		if (i == firstVertex) cout << "wierzcholek startowy, ";
		else
			while (preVertex[x] != -1) {
				cout << preVertex[x] << " ";
				x = preVertex[x];
			}
		cout << "koszt: " << minCost[i];
	}*/


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
							edge = Edge(p, k, wagi[j], 0);

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

	cout << endl << "Najkrotsza sciezka pomiedzy wierzcholkiem startowym, a koncowym " <<endl<< firstVertex << "-"
		<< lastVertex << ": " << tab[lastVertex] << endl;

	delete[]tab;

}


GrafMacierz::~GrafMacierz()
{
	for (int i = 0; i < vertices; i++)
		delete[] macierz[i];

	delete[] macierz;
	delete[] wagi;

	delete[]usedVertices;
	delete[]minCost;
	delete[]preVertex;

}
