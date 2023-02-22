#pragma once
#include <iostream>
#include <fstream>
#include "wymiana.h"

class menu
{
public:
	void opcje() {
		cout << "-----Witaj w systemie wymiany walut!-----\n";
		cout << "1. Wymien dowolne waluty.\n";
		cout << "2. Wyswietl dostepne waluty do konwersji.\n";
		cout << "3. Dodaj nowa walute.\n";
		cout << "4. Zakoncz dzialanie programu.\n";
	}

	void wybor() {
		wymiana* W = new wymiana;
		W->loadData();
		opcje();
		unique_ptr<int> wybor(new int);
		while (true)
		{
			cout << "\nWybor: ";
			cin >> *wybor;
			switch (*wybor)
			{
			case 1: W->exchange();
				break;
			case 2: W->seeCurrencies();
				break;
			case 3: W->dodajWalute();
				break;
			case 4: {
				W->saveData();
				delete W;
				return; }
			default: cout << "Nie ma takiego wyboru!" << endl;

			}
		}
	}
};