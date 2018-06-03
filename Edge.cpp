#include "Edge.h"

Edge::Edge()
{
	vertex1 = 0;
	vertex2 = 0;
	value = 0;
	next = 0;
}

Edge::Edge(int vertex1, int vertex2, int value, Edge *next)
{
	this->vertex1 = vertex1;
	this->vertex2 = vertex2;
	this->value = value;
	this->next = next;
}

Edge::~Edge()
{
}
