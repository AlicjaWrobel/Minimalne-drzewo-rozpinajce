#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include "Time.h"
#include "Edge.h"
#include "Graf.h"
#include "Vertex.h"

using namespace std;

int mst() {

	static Graf* graf = nullptr;

	cout <<endl<< "Wybierz operacje:\n"
		<< "\n 1 - Wczytaj dane z pliku"
		<< "\n 2 - Wygeneruj losowo graf"
		<< "\n 3 - Wyœwietl graf listowo i macierzowo na ekranie"
		<< "\n 4 - Algorytm Kruskala - macierzowo"
		<< "\n 5 - Algorytm Prima - macierzowo"
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

			graf = new Graf(wierzcholki, krawedzie, 0);
			graf->newIncidneceMatrix();

			for (int i = 0; i < krawedzie; i++) {

				plik >> poczatek;
				plik >> koniec;
				plik >> waga;

				graf->MSTincidneceMatrix(poczatek, koniec, waga, i);
			}
			graf->showIncidneceMatrix();
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

		graf = new Graf(wierzcholki, iloscKrawedzi, 0);
		graf->newIncidneceMatrix();
		for (int i = 0; i < iloscKrawedzi; i++) {

			poczatek = rand() % wierzcholki;
			koniec = rand() % wierzcholki;
			waga = rand() % wierzcholki;
			while (koniec == poczatek) koniec = rand() % wierzcholki;

			graf->MSTincidneceMatrix(poczatek, koniec, waga, i);
		}
		graf->showIncidneceMatrix();

		break;
	}
	case 3: {

		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->showIncidneceMatrix();
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
	default:
		cout << "\n Podaj wartosc od 0 do 5";
		_getch();
		return 1;
	}
	return 1;
}

int sciezka() {

	static Graf* graf = nullptr;

	cout << "Wybierz operacje:\n"
		<< "\n 1 - Wczytaj dane z pliku"
		<< "\n 2 - Wygeneruj losowo graf"
		<< "\n 3 - Wyœwietl graf listowo i macierzowo na ekranie"
		<< "\n 4 - Algorytm Dijkstry - macierzowo"
		<< "\n 5 - Algorytm 2"
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

			graf = new Graf(wierzcholki, krawedzie, 0);
			graf->newIncidneceMatrix();

			for (int i = 0; i < krawedzie; i++) {

				plik >> poczatek;
				plik >> koniec;
				plik >> waga;

				graf->SCIEZKAincidneceMatrix(poczatek, koniec, waga, i);
			}
			graf->showIncidneceMatrix();
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

		graf = new Graf(wierzcholki, iloscKrawedzi, 0);
		graf->newIncidneceMatrix();
		//graf->newList();
		for (int i = 0; i < iloscKrawedzi; i++) {

			poczatek = rand() % wierzcholki;
			koniec = rand() % wierzcholki;
			waga = 0;
			while (koniec == poczatek) koniec = rand() % wierzcholki;

			graf->SCIEZKAincidneceMatrix(poczatek, koniec, waga, i);
			//graf->SCIEZKAlista(poczatek, koniec, waga, i);
		}
		graf->showIncidneceMatrix();
		//graf->showList();
		break;
	}
		
	case 3: {
		if (graf == nullptr) cout << "Graf nie zostal wczytany \n";
		else {
			graf->showIncidneceMatrix();
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
	default:
		cout << "\n Podaj wartosc od 0 do 5";
		_getch();
		return 1;
	}
	return 1;
}
int menu() {
	static Graf* graf = nullptr;

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