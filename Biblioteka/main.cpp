#include <iostream>
#include <string>
#include <fstream>
#include <vld.h>

#include "struktury.h"
#include "funkcje.h"

using namespace std;

int main(int ile, char *params[])
{

	czytelnik * pGlowaC = nullptr;
	ksiazka * pGlowaK = nullptr;
	wypozyczone * pGlowa = nullptr;
	ifstream ludzie;
	ifstream ksiazki;

	ludzie.open("czytelnicy.txt", ios::in);
	ksiazki.open("ksiazki.txt", ios::in);

	czytaj_z_plikuK(pGlowaK, ksiazki);
	czytaj_z_plikuC(pGlowaC, ludzie);
	dodaj_wypozyczone_do_listy(pGlowaK, pGlowa);

	for (int i = 1; i < ile; i++)
	{
		if (pGlowaC == nullptr or pGlowaK == nullptr)
		{
			cout << "lista czytelnikow lub ksiazek jest pusta" << endl;
			break;
		}
		
		string s = params[i];

		if (s == "-k")
			wypisz_plik_ksiazki(pGlowaK, cout);

		else if (s == "-c")
			wypisz_plik_czytelnikow(pGlowaC, cout);

		else if (s == "-ic")
			wypisz_czytelnikow(pGlowaC, cout);

		else if (s == "-ik")
			wypisz_ksiazki(pGlowaK, cout);

		else if (s == "-r")
		{
			ifstream ludzie_wyj;
			ifstream ksiazki_wyj;

			ludzie_wyj.open("czytelnicy_wyj.txt", ios::in);
			ksiazki_wyj.open("ksiazki_wyj.txt", ios::in);
			
			if (ludzie_wyj.good())
			{
				cout << "Plik wyjsciowy z czytelnikami: " << endl;
				wypisz_plikC(ludzie_wyj);
			}
			else
				cout << "Ten plik wyjsciowy z czytelnikami nie istnieje" << endl;
			
			if (ksiazki_wyj.good())
			{
				cout << endl << "Plik wyjsciowy z ksiazkami:" << endl;
				wypisz_plikK(ksiazki_wyj);
			}
			else
				cout << "Ten plik wyjsciowy z ksiazkami nie istnieje" << endl;

			ludzie_wyj.close();
			ksiazki_wyj.close();
		}

		else if (s == "-a")
		{
			int numerA = wybor_akcji();
			switch (numerA)
			{
			case 1:
			{
				string wybor;
				cout << "Wybierz co chcesz usunac. Ksiazke lub czytelnika [k/c]" << endl;
				cin >> wybor;

				if (wybor == "k")
				{
					ksiazka *Kdo_usuniecia = wybierz_ksiazke(pGlowaK);
					usun_ksiazke(pGlowaK, Kdo_usuniecia);
				}
				else if (wybor == "c")
				{
					czytelnik *Cdo_usuniecia = wybierz_czytelnika(pGlowaC);
					usun_czytelnika(pGlowaC, Cdo_usuniecia);
				}
				else
					cout << "niepoprawne dane" << endl;
			}break;

			case 2:
				wypozycz(pGlowaC, pGlowaK, pGlowa);
				break;

			case 3:
				oddaj(pGlowaK, pGlowa, pGlowaC);
				break;

			case 4:
				po_terminie(pGlowa, pGlowaC, cout);
				break;

			case 5:
				raport_czytelnika(pGlowaK, pGlowaC, pGlowa);
				break;

			case 0:
				cout << "nie ma dostepnej takiej akcji" << endl;
				break;
			}
		}
		else
			cout << "nieprawidlowy parametr" << endl;
	}

	zapisz_do_plikow(pGlowaK, pGlowaC);
	usun_liste_ksiazek(pGlowaK);
	usun_liste_czytelnikow(pGlowaC);
	usun_liste_wypozyczonych(pGlowa);
	ludzie.close();
	ksiazki.close();

	return 0;
}