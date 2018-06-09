#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "Time.h"
#include "Edge.h"
#include "GrafMacierz.h"
#include "GrafLista.h"
#include "Vertex.h"
#include <time.h>

using namespace std;

int mst() {

	static GrafMacierz* graf = nullptr;
	static GrafLista* graf2 = nullptr;

	cout <<endl<< "Wybierz operacje:\n"
		<< "\n 1 - Wczytaj dane z pliku"
		<< "\n 2 - Wygeneruj losowo graf"
		<< "\n 3 - Wyœwietl graf listowo i macierzowo na ekranie"
		<< "\n 4 - Algorytm Kruskala - macierz"
		<< "\n 5 - Algorytm Prima - macierz"
		<< "\n 6 - Algorytm Kruskala - lista"
		<< "\n 7 - Algorytm Prima - lista"
		<< "\n 0 - Powrot\n";

	int wybor;
	int krawedzie;
	int wierzcholki;
	int poczatek, koniec, waga;

	cin >> wybor;
	switch (wybor) {
	case 0:
		return 0;
	case 1: {
		ifstream plik;
		string nazwa;
		cout << "\n Podaj nazwe pliku z ktorego chcesz wczytac dane: ";
		cin >> nazwa;
		plik.open(nazwa, std::ios::in);
		if (plik.good()) {

			plik.seekg(0);
			plik >> krawedzie;
			plik >> wierzcholki;

			graf = new GrafMacierz(wierzcholki, krawedzie);
			graf2 = new GrafLista(wierzcholki, krawedzie);
			graf->newIncidneceMatrix();

			for (int i = 0; i < krawedzie; i++) {

				plik >> poczatek;
				plik >> koniec;
				plik >> waga;

				graf->MSTincidneceMatrix(poczatek, koniec, waga, i);
				graf2->MSTlist(poczatek, koniec, waga);
			}
			graf->showIncidneceMatrix();
			graf2->Show();
		}
		plik.close();
	}
			break;
	case 2: {
		int gestosc;

		cout << "Podaj ile wierzcholkow ma miec wygenerowany graf: ";
		cin >> wierzcholki;
		cout << "\nPodaj jaka gestosc ma miec wygenerowany graf (1 - 100%): ";
		cin >> gestosc;
		int iloscKrawedziMax = wierzcholki * (wierzcholki - 1);
		int iloscKrawedzi = (iloscKrawedziMax * gestosc) / 100;

		graf = new GrafMacierz(wierzcholki, iloscKrawedzi);
		graf2 = new GrafLista(wierzcholki, iloscKrawedzi);

		graf->newIncidneceMatrix();
		for (int i = 0; i < iloscKrawedzi; i++) {

			poczatek = rand() % wierzcholki;
			koniec = rand() % wierzcholki;
			waga = rand() % 10;
			while (koniec == poczatek) koniec = rand() % wierzcholki;

			graf->MSTincidneceMatrix(poczatek, koniec, waga, i);
			graf2->MSTlist(poczatek, koniec, waga);
		}
		graf->showIncidneceMatrix();
		graf2->Show();

		break;
	}
	case 3: {

		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->showIncidneceMatrix();
			graf2->Show();
		}

		break;
	}
	case 4: {

		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->algorytmKruskala();
		}
		break;
	}
	case 5: {

		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->algorytmPrima();
		}
		break;
	}
	case 6: {

		if (graf2 == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf2->algorytmKruskala();
		}
		break;
	}
	case 7: {

		if (graf2 == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf2->algorytmPrima();
		}
		break;
	}
	default:
		cout << "\n Podaj wartosc od 0 do 7";
		_getch();
		return 1;
	}
	return 1;
}

int sciezka() {

	static GrafMacierz* graf = nullptr;
	static GrafLista* graf2 = nullptr;
	int wybor;
	int krawedzie;
	int wierzcholki;
	int poczatek, koniec, waga;
	int firstVertex, lastVertex;

	cout <<endl<< "Wybierz operacje:\n"
		<< "\n 1 - Wczytaj dane z pliku"
		<< "\n 2 - Wygeneruj losowo graf"
		<< "\n 3 - Wyœwietl graf listowo i macierzowo na ekranie"
		<< "\n 4 - Algorytm Dijkstry - macierz"
		<< "\n 5 - Algorytm Forda Bellamana - macierz"
		<< "\n 6 - Algorytm Dijkstry - lista"
		<< "\n 7 - Algorytm Forda Bellamana - lista"
		<< "\n 0 - Powrot \n";


	cin >> wybor;
	switch (wybor) {
	case 0:
		return 0;
	case 1: {
		ifstream plik;
		string nazwa;
		cout << "\n Podaj nazwe pliku z ktorego chcesz wczytac dane: ";
		cin >> nazwa;
		plik.open(nazwa, std::ios::in);
		if (plik.good()) {

			plik.seekg(0);
			plik >> krawedzie;
			plik >> wierzcholki;

			graf = new GrafMacierz(wierzcholki, krawedzie);
			graf2 = new GrafLista(wierzcholki, krawedzie);
			graf->newIncidneceMatrix();

			for (int i = 0; i < krawedzie; i++) {

				plik >> poczatek;
				plik >> koniec;
				plik >> waga;

				graf->SCIEZKAincidneceMatrix(poczatek, koniec, waga, i);
				graf2->SCIEZKAlist(poczatek, koniec, waga);
			}
			graf->showIncidneceMatrix();
			graf2->Show();
		}
		plik.close();
		break;
	}
			
	case 2: {
		int gestosc;

		cout << "Podaj ile wierzcholkow ma miec wygenerowany graf: ";
		cin >> wierzcholki;
		cout << "\nPodaj jaka gestosc ma miec wygenerowany graf (1 - 100%): ";
		cin >> gestosc;
		int iloscKrawedziMax = wierzcholki * (wierzcholki - 1);
		int iloscKrawedzi = (iloscKrawedziMax * gestosc) / 100;

		graf = new GrafMacierz(wierzcholki, iloscKrawedzi);
		graf2 = new GrafLista(wierzcholki, iloscKrawedzi);
		graf->newIncidneceMatrix();

		for (int i = 0; i < iloscKrawedzi; i++) {

			poczatek = rand() % wierzcholki;
			koniec = rand() % wierzcholki;
			waga = rand() % 10;
			while (koniec == poczatek) koniec = rand() % wierzcholki;

			graf->SCIEZKAincidneceMatrix(poczatek, koniec, waga, i);
			graf2->SCIEZKAlist(poczatek, koniec, waga);
		}
		graf->showIncidneceMatrix();
		graf2->Show();
		break;
	}
		
	case 3: {
		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->showIncidneceMatrix();
			graf2->Show();
		}
		break;
	}
	case 4: {
		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			cout << "\n Podaj wierzcholek poczatkowy \n";
			cin >> firstVertex;
			cout << "\n Podaj wierzcholek koncowy \n";
			cin >> lastVertex;

			graf->algorytmDijkstry(firstVertex, lastVertex);

		}
		break;
	}
	case 5: {
		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
	
			cout << "\n Podaj wierzcholek poczatkowy \n";
			cin >> firstVertex;
			cout << "\n Podaj wierzcholek koncowy \n";
			cin >> lastVertex;

				graf->algorytmFordaBellmana(firstVertex, lastVertex);
			
		}
		break;
	}
	case 6: {

		if (graf2 == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			cout << "\n Podaj wierzcholek poczatkowy \n";
			cin >> firstVertex;
			cout << "\n Podaj wierzcholek koncowy \n";
			cin >> lastVertex;

			graf2->algorytmDijkstry(firstVertex, lastVertex);
		}
		break;
	}
	case 7: {

		if (graf2 == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			cout << "\n Podaj wierzcholek poczatkowy \n";
			cin >> firstVertex;
			cout << "\n Podaj wierzcholek koncowy \n";
			cin >> lastVertex;

			graf2->algorytmFordaBellmana(firstVertex, lastVertex);
		}
		break;
	}
	default:
		cout << "\n Podaj wartosc od 0 do 5";
		_getch();
		return 1;
	}
	return 1;
}

int Suma_tablicy(int tab[], int rozmiar)
{
	int suma = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		suma = suma + tab[i];
	}
	return suma;
}

GrafLista *Generator_grafow2(int l_wierz, double procent)
{

	static GrafLista* graf2 = nullptr;
	int wybor;
	int poczatek, koniec, waga;
	int firstVertex, lastVertex;

	int iloscKrawedziMax = l_wierz * (l_wierz - 1);
	int iloscKrawedzi = (iloscKrawedziMax * procent) / 100;

	graf2 = new GrafLista(l_wierz, iloscKrawedzi);

	for (int i = 0; i < iloscKrawedzi; i++) {

		poczatek = rand() % l_wierz;
		koniec = rand() % l_wierz;
		waga = rand() % 10;
		while (koniec == poczatek) koniec = rand() % l_wierz;


		graf2->MSTlist(poczatek, koniec, waga);
		graf2->SCIEZKAlist(poczatek, koniec, waga);
	}
	return graf2;
}

GrafMacierz *Generator_grafow(int l_wierz, int procent)
{

	static GrafMacierz* graf = nullptr;

	int wybor;
	int poczatek, koniec, waga;
	int firstVertex, lastVertex;

	int iloscKrawedziMax = l_wierz * (l_wierz - 1);
	int iloscKrawedzi = (iloscKrawedziMax * procent) / 100;

	graf = new GrafMacierz(l_wierz, iloscKrawedzi);
	graf->newIncidneceMatrix();

	for (int i = 0; i < iloscKrawedzi; i++) {

		poczatek = rand() % l_wierz;
		koniec = rand() % l_wierz;
		waga = rand() % 10;
		while (koniec == poczatek) koniec = rand() % l_wierz;

		graf->SCIEZKAincidneceMatrix(poczatek, koniec, waga, i);
		graf->MSTincidneceMatrix(poczatek, koniec, waga, i);
	}
	return graf;
}

void Pojedynczy_pomiar(int wierz, int gestosc)
{
	GrafLista *g_lista;
	GrafMacierz *g_macierz;
	Time zegarek;

	int pocz;
	int koniec;
	Generator_grafow(wierz, gestosc);

	g_lista = Generator_grafow2(wierz, gestosc);
	g_macierz = Generator_grafow(wierz, gestosc);

	cout << endl << "Prim Lista ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_lista->algorytmPrima();
		zegarek.GetCounter();

	}

	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	cout << endl << "Kruskal Lista ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_lista->algorytmKruskala();
		zegarek.GetCounter();

	}
	cout << zegarek.printAverage() << endl;
	zegarek.reset(); 

	cout << "Prim Macierz " ;
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_macierz->algorytmPrima();
		zegarek.GetCounter();
	}

	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	cout <<"Kruskal Macierz ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_macierz->algorytmKruskala();
		zegarek.GetCounter();
	}
	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	srand(time(NULL));
	pocz = rand() % (wierz - 1) + 1;
	koniec = rand() % (wierz - 1) + 1;

	cout << "Dijkstry lista ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_lista->algorytmDijkstry(pocz, koniec);
		zegarek.GetCounter();
	}
	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	cout << "Bellman lista ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_lista->algorytmFordaBellmana(pocz, koniec);
		zegarek.GetCounter();
	}

	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	cout << "Dijkstry macierz ";
	for (int i = 0; i < 100; i++)
	{
		zegarek.StartCounter();
		g_macierz->algorytmDijkstry(pocz, koniec);
		zegarek.GetCounter();
	}

	cout << zegarek.printAverage() << endl;
	zegarek.reset();

	cout << "Bellam macierz ";
	for (int i = 0; i < 100; i++)
	{
	zegarek.StartCounter();
	g_macierz->algorytmFordaBellmana(pocz, koniec);
	zegarek.GetCounter();

	}
	cout << zegarek.printAverage() << endl <<endl;
	zegarek.reset();

}

int pomiary()
{
	
	//  10 wierzcholkow
	// 25%gestosc
	cout << "W_10_G_25_AL_" << endl;

		Pojedynczy_pomiar(10, 25);

	// 50%gestosc
	cout << "W_10_G_50_AL_" << endl;

		Pojedynczy_pomiar(10, 50);

	// 75%gestosc
	cout << "W_10_G_75_AL_" << endl;

		Pojedynczy_pomiar(10, 75);

	// 99%gestosc
	cout << "W_10_G_99_AL_" << endl;

		Pojedynczy_pomiar(10, 99);


	// 25 wierzcholkow
	// 25%gestosc
	cout << "W_25_G_25_AL_" << endl;

		Pojedynczy_pomiar(25, 25);


	// 50%gestosc
	cout << "W_25_G_50_AL_" << endl;

		Pojedynczy_pomiar(25, 50);

	// 75%gestosc
	cout << "W_25_G_75_AL_" << endl;

		Pojedynczy_pomiar(25, 75);

	// 99%gestosc
	cout << "W_25_G_99_AL_" << endl;

		Pojedynczy_pomiar(25, 99);

	// 50 wierzcholkow

	// 25%gestosc
	cout << "W_50_G_25_AL_" << endl;

		Pojedynczy_pomiar(50, 25);

	// 50%gestosc
	cout << "W_50_G_50_AL_" << endl;

		Pojedynczy_pomiar(50, 50);

	// 75%gestosc
	cout<< "W_50_G_75_AL_" << endl;

		Pojedynczy_pomiar(50, 75);
	
	// 99%gestosc
	cout<< "W_50_G_99_AL_" << endl;

		Pojedynczy_pomiar(50, 99);


	// 100 wierzcholkow
	// 25%gestosc
	cout<< "W_100_G_25_AL_" << endl;

		Pojedynczy_pomiar(100, 25);


	// 50%gestosc
	cout<< "W_100_G_50_AL_" << endl;

		Pojedynczy_pomiar(100, 50);

	// 75%gestosc
	cout << "W_100_G_75_AL_" << endl;

		Pojedynczy_pomiar(100, 75);

	// 99%gestosc
	cout << "W_100_G_99_AL_" << endl;

		Pojedynczy_pomiar(100, 99);
	


	// 70 wierzcholkow
	// 25%gestosc
	cout << "W_70_G_25_AL_" << endl;

		Pojedynczy_pomiar(60, 25);
	

	// 50%gestosc
	cout << "W_70_G_50_AL_" << endl;

		Pojedynczy_pomiar(70, 50);
	
	// 75%gestosc
	cout << "W_70_G_75_AL_" << endl;

		Pojedynczy_pomiar(70, 75);
	
	// 99%gestosc
	cout << "W_70_G_99_AL_" << endl;

		Pojedynczy_pomiar(70, 99);
	
	return 0;
}

int menu() {
	cout << "Wybierz operacje:\n"
		<< "\n 1 - Budowanie minimalnego drzewa rozpinajacego"
		<< "\n 2 - Szukanie najkrotszej sciezki w grafie"
		<< "\n 3 - Pomiary"
		<< "\n 0 - Wyjscie \n";

	int wybor;
	cin >> wybor;

	switch (wybor) {
	case 0:
		return 0;
	case 1: {
		while (mst());
		break;
	}
	case 2: {
		while (sciezka());
		break;
	}
	case 3: {
		while (pomiary());
		break;
	}
	default:
		cout << "\n Podaj wartosc od 0 do 5";
		_getch();
		return 1;
	}
	return 1;
}

int main() {
	while (menu());
	return 0;
}