#pragma once
class Edge
{
private:
public:
	Edge * next;
	int value;	//waga
	int vertex1; //1 wierzcholek krawedzi
	int vertex2; //2 wierzcholek krawedzi
	Edge(); //konstruktor
	Edge(int vertex1, int vertex2, int value, Edge *next);
	~Edge(); //destruktor
};

