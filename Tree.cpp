#include "Tree.h"
#include <iostream>

using namespace std;



Tree::Tree()
{
	head = 0;
	size = 0;
}

Tree::Tree(int size)
{
	this->size = size;
	for (int i = 0; i<size; i++)
	{
		Edge *new_edge = new Edge;
		new_edge->vertex1 = 0;
		new_edge->vertex2 = 0;
		new_edge->value = 0;
		if (head == 0)
		{
			head = new_edge;
		}
		else
		{
			Edge *wsk;
			wsk = head;
			while (wsk->next)
			{
				wsk = wsk->next;
			}
			wsk->next= new_edge;
			new_edge->next = 0;
		}
	}
}

bool Tree::completedTree(int vertices)
{
	if ((vertices - 1) == size)
		return true;
	else
	return false;
}

void Tree::addEdge(Edge edge)
{
	Edge *new_edge = new Edge;
	new_edge->vertex1 = edge.vertex1;
	new_edge->vertex2 = edge.vertex2;
	new_edge->value = edge.value;
	new_edge->next = 0;
	if (head == 0)
	{
		head = new_edge;
		size++;
	}
	else
	{
		Edge *wsk;
		wsk = head;
		while (wsk->next)
		{
			wsk = wsk->next;
		}
		wsk->next = new_edge;
		size++;
	}
}


int Tree::sumValues()
{
	int sum = 0;
	Edge *wsk = head;

	while (wsk->next!= 0)
	{
		sum = sum + wsk->value;
		wsk = wsk->next;
	}

	sum = sum + wsk->value;
	return sum;
}

Tree::~Tree()
{
}
