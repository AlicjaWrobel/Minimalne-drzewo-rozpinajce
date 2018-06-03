#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "Time.h"
#include "Edge.h"
#include "GrafMacierz.h"
#include "GrafLista.h"
#include "Vertex.h"

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

			graf = new GrafMacierz(wierzcholki, krawedzie, 0);
			graf2 = new GrafLista(wierzcholki, krawedzie,0);
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

		graf = new GrafMacierz(wierzcholki, iloscKrawedzi, 0);
		graf2 = new GrafLista(wierzcholki, iloscKrawedzi, 0);

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

	cout <<endl<< "Wybierz operacje:\n"
		<< "\n 1 - Wczytaj dane z pliku"
		<< "\n 2 - Wygeneruj losowo graf"
		<< "\n 3 - Wyœwietl graf listowo i macierzowo na ekranie"
		<< "\n 4 - Algorytm Dijkstry - macierz"
		<< "\n 5 - Algorytm Forda Bellamana - macierz"
		<< "\n 6 - Algorytm Dijkstry - lista"
		<< "\n 7 - Algorytm Forda Bellamana - lista"
		<< "\n 0 - Powrot \n";

	int wybor;
	int krawedzie;
	int wierzcholki;
	int poczatek, koniec, waga;
	int firstVertex, lastVertex;

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

			graf = new GrafMacierz(wierzcholki, krawedzie, 0);
			graf2 = new GrafLista(wierzcholki, krawedzie, 0);
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

		graf = new GrafMacierz(wierzcholki, iloscKrawedzi, 0);
		graf2 = new GrafLista(wierzcholki, iloscKrawedzi, 0);
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

			graf2->algorytmFordaBellmana(firstVertex, lastVertex);
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
int menu() {
	static GrafMacierz* graf = nullptr;

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