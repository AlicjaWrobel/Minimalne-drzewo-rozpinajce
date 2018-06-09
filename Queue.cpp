#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue()
{
	heap = false;

}

void Queue::addEdge(Edge edge)
{
	heap = false;
	tab.push_back(edge); //dodaje element na koniec
}

bool Queue::add(Edge edge)
{
	heap = false;
	for (int i = 0; i<count_tab.size(); i++)
	{
		if ((count_tab[i].vertex2 == edge.vertex2 && count_tab[i].vertex1 == edge.vertex1) ||
			(count_tab[i].vertex2 == edge.vertex1 && count_tab[i].vertex1 == edge.vertex2))
		{
			return false;
		}
	}

	addAppeared(edge);
	tab.push_back(edge);
	return true;
}

void Queue::addAppeared(Edge edge)
{
	count_tab.push_back(edge);
}

void Queue::sortHeap()
{
	heap = true;
	int j, ojciec;
	Edge edge;

	for (int i = 1; i<tab.size(); i++)
	{
		ojciec = ((i - 1) / 2);
		edge = tab[i];

		if (edge.value < tab[ojciec].value &&  ojciec >= 0)
		{			
			tab[i] = tab[ojciec];
			tab[ojciec] = edge;
		 }

	}
}

Edge Queue::removeEdge()
{
	heap = false;
	Edge first;

	first = tab.front(); //referencja na 1 element
	tab.erase(tab.begin());
	sortHeap();

	return first;
}

void Queue::addVertex(Vertex vertex)
{
	tab2.push_back(vertex); //dodaje element na koniec
}

bool Queue::add(Vertex vertex)
{
	for (int i = 0; i<count_tab.size(); i++)
	{
		if (count_tab2[i].index == vertex.index) return false;
	}

	addAppeared(vertex);
	tab2.push_back(vertex);
	return true;
}

void Queue::addAppeared(Vertex vertex)
{
	count_tab2.push_back(vertex);
}

Vertex Queue::removeVertex()
{
	Vertex last;
	last = tab2.front(); //referencja na ostatni element
	tab2.erase(tab2.begin());
	return last;
}

Vertex Queue::lastVertex()
{
	Vertex last;

	last = tab2.back(); //referencja na ostatni element

	return last;
}

Vertex Queue::getFirst()
{
	return tab2.front();
}


int Queue::size()
{
	return tab.size();
}

void Queue::showQueue()
{
	for (int i = 0; i < tab.size(); i++)
	{
		cout << "Poczatek krawedzi: " << tab[i].vertex1 << " Koniec Krawedzi: " << tab[i].vertex2 << " Waga krawdzi"<< tab[i].value <<endl;
	}
}

int Queue::size2()
{
	return tab2.size();
}

void Queue::showQueue2()
{
	for (int i = 0; i < tab2.size(); i++)
	{
		cout << "Indeks wierzcholka: " << tab2[i].index << " Koszt dojscia: " << tab2[i].value << " Poprzednik: " << tab2[i].previous << endl;
	}
}


Queue::~Queue()
{
}
