#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include "waluta.h"

using namespace std;

class wymiana
{
private:
	list<shared_ptr<waluta>> waluty_;

public:
	wymiana() {}

	//wczytywanie danych o walutach
	void loadData() {
		ifstream file("waluty.txt");
		waluta W;
		while (file >> W)
		{
			waluty_.push_back(make_shared<waluta>(W));
		}
	}

	//zapisanie danych do pliku przy zakonczeniu programu
	void saveData()
	{
		ofstream file("waluty.txt");
		for (auto& X : waluty_)
		{
			file << *X << endl;
		}
	}

	double zamiana(string& from, string& to, double& ilosc)
	{
		// lambdaa zwraca kurs waluty która jest przekazywana jako argument
		auto lambda = [&](string& name) {
			for (auto& R : waluty_) {
				if (R->getName() == name) return R->getRate();
			}};

		if (from == "PLN")
		{
			return ilosc / lambda(to);
		}
		else if (to == "PLN")
		{
			return ilosc * lambda(from);
		}
		else
		{
			return ilosc * lambda(from) / lambda(to);
		}
	}


	//napisane przy oddawaniu
	template<typename T>
	void biggestTransactions(T dana)
	{
		vector<T> lista;
		ifstream file("transakcje.txt");

		T X;
		lista.push_back(dana);
		while (file >> X)
		{
			lista.push_back(X);
		}
		file.close();

		sort(lista.begin(), lista.end(), greater<T>());

		ofstream file2("transakcje.txt");

		for (int i = 0; i < 3; i++)
		{
			file2 << lista[i] << endl;
			cout << lista[i] << " ";
		}
		file2.close();
	}

	void exchange() {
		//lambda konwertuje nazwê waluty na duze litery i sprawdza czy dana waluta znajduje siê w bazie danych, jesli nie to wyswietla odpowiedni komunikat
		auto lam = [&](string& c) { string X; for (auto a : c) { X += toupper(a); } c = X;
		for (auto& R : waluty_) {
			if (R->getName() == X) return true; ;
		}
		cout << "nie ma takiej waluty\n"; return false; };

		string zWaluty = "", doWaluty = "";
		double ilosc;

		do {
			cout << "Podaj nazwe waluty do wymiany: ";
			cin >> zWaluty;

		} while (!lam(zWaluty));
		string pln = "PLN";

		biggestTransactions<double>(zamiana(zWaluty, pln, ilosc));

		do {
			cout << "Podaj nazwe waluty docelowej: ";
			cin >> doWaluty;

		} while (!lam(doWaluty));

		cout << "Podaj ilosc " << zWaluty << " do wymiany: ";
		cin >> ilosc;
		cout << ilosc << " " << zWaluty << " to " << zamiana(zWaluty, doWaluty, ilosc) << " " << doWaluty;

	};

	void dodajWalute()
	{
		string nazwa;
		double kurs;

		auto goodName = [&]() {if (nazwa.length() != 3) { cout << " Nazwa waluty musi miec 3 znaki!"; return false; } string x = "";
		for (auto a : nazwa) { x += toupper(a); } nazwa = x; return true;
		};

		do {
			cout << "Podaj nazwe waluty: ";
			cin >> nazwa;
		} while (!goodName());

		cout << "Podaj ile : " << nazwa << " to 1 PLN: ";
		cin >> kurs;

		waluta W(nazwa, kurs);
		waluty_.push_back(make_shared<waluta>(W));
	}

	void seeCurrencies()
	{
		for (auto& a : waluty_)
		{
			cout << a->getName() << " ";
		}
		cout << endl;
	}
};