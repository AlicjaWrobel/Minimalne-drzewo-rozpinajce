#include "Vertex.h"


Vertex::Vertex()
{
}

Vertex::Vertex(int value, int index)
{
	this->value = value;
	this->index = index;
}

Vertex::Vertex(int value, int index, int previous)
{
	this->value = value;
	this->index = index;
	this->previous = previous;
}

Vertex::~Vertex()
{
}
