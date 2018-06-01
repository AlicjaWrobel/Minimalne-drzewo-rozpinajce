#pragma once
class Vertex
{
private:
public:
	int value;	//wartosc, koszt
	int index;	//indeks
	int previous; //poprzednik
	Vertex();
	Vertex(int value, int index); //graf nieskierownay
	Vertex(int value, int index, int previous); //graf skierowany
	~Vertex(); //destruktor
};

