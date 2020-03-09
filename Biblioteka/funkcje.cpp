#include <iostream>
#include <string>
#include <fstream>
#include <limits>

#include "struktury.h"
#include "funkcje.h"

int wybor_akcji()
{
	cout << "Wybierz akcje: " << endl;
	cout << "u) Usun ksiazke lub czytelnika" << endl;
	cout << "w) Wypozycz ksiazke" << endl;
	cout << "o) Oddaj ksiazke" << endl;
	cout << "g) Wygeneruj liste ksiazek po terminie zwrotu" << endl;
	cout << "r) Wygeneruj raport czytelnika do pliku" << endl;
	cout << "b) Zakoncz" << endl;

	string znak;
	cin >> znak;
	int numerA;

	if (znak == "u")
		numerA = 1;
	else if (znak == "w")
		numerA = 2;
	else if (znak == "o")
		numerA = 3;
	else if (znak == "g")
		numerA = 4;
	else if (znak == "r")
		numerA = 5;
	else if (znak == "b")
		numerA = 6;
	else
		numerA = 0;

	return numerA;
}

void czytaj_z_plikuC(czytelnik * & pHeadC, ifstream & ludzie)
{
	string imie;
	string nazwisko;
	int ic, ile;

	if (ludzie.good())
	{
		while (ludzie >> imie)
		{
			ludzie>> nazwisko >> ic >> ile;
			dodaj_czytelnikow_do_listy(pHeadC, imie, nazwisko, ic, ile);
		}
	}
	else
		cout << "Ten plik z czytelnikami nie istnieje" << endl;
}

void czytaj_z_plikuK(ksiazka * & pHeadK, ifstream & ksiazki)
{
	string tytul;
	string autor;
	int rok, miesiac, dzien, ic, ik;

	if (ksiazki.good())
	{
		while (ksiazki >> tytul)
		{
			ksiazki >> autor >> ik >> rok >> miesiac >> dzien >> ic;
			dodaj_ksiazki_do_listy(pHeadK, tytul, autor, ik, rok, miesiac, dzien, ic);
		}
	}
	else
		cout << "Ten plik z ksiazkami nie istnieje" << endl;
}

void dodaj_ksiazki_do_listy(ksiazka * & pHeadK, string tytul, string autor, int ik, int rok, int miesiac, int dzien, int ic)
{
	if (not pHeadK) // lista pusta
	{
		pHeadK = new ksiazka{ tytul, autor, ik, rok, miesiac, dzien, ic, nullptr };
	}
	else // lista już coś zawiera
	{
		ksiazka * pNowy = new ksiazka{ tytul, autor, ik, rok, miesiac, dzien, ic, nullptr };
		ksiazka * p = pHeadK;
		while (p->pNext)
			p = p->pNext;
		// zatrzymalismy się, tzn. p->pNext == nullptr
		p->pNext = pNowy;
	}
}

void dodaj_czytelnikow_do_listy(czytelnik * & pHeadC, string imie, string nazwisko, int ic, int ile)
{
	if (not pHeadC) // lista pusta
	{
		pHeadC = new czytelnik{ imie,  nazwisko, ic, ile, nullptr };
	}
	else // lista już coś zawiera
	{
		czytelnik * pNowy = new czytelnik{ imie,  nazwisko, ic, ile, nullptr };
		czytelnik * p = pHeadC;
		while (p->pNext)
			p = p->pNext;
		// zatrzymalismy się, tzn. p->pNext == nullptr
		p->pNext = pNowy;
	}
}

void wypisz_ksiazki(ksiazka * pHead, ostream & ss)
{
	if (pHead)
	{
		ss << pHead->tytul << " " << pHead->autor << " " << pHead->ik << endl;  // wypisz mnie
		wypisz_ksiazki(pHead->pNext, ss);   // wypisz ogon
	}
}

void wypisz_plik_ksiazki(ksiazka * pHead, ostream & ss)
{
	for (unsigned i = 1; pHead; pHead = pHead->pNext)
		ss << pHead->tytul << " " << pHead->autor << " " << pHead->ik << " " << pHead->rok_wyp << " " << pHead->miesiac_wyp << " " << pHead->dzien_wyp << " " << pHead->ic << endl;
}

void wypisz_czytelnikow(czytelnik * pHead, ostream & ss)
{
	if (pHead)
	{
		ss << pHead->imie << " " << pHead->nazwisko <<" "<< pHead->ic << endl;  // wypisz mnie
		wypisz_czytelnikow(pHead->pNext, ss);   // wypisz ogon
	}
}

void wypisz_plik_czytelnikow(czytelnik * pHead, ostream & ss)
{
	for (unsigned i = 1; pHead; pHead = pHead->pNext)
		ss << pHead->imie << " " << pHead->nazwisko << " " << pHead->ic << " " << pHead->ile << endl; 
}

void usun_liste_czytelnikow(czytelnik * & pHead)
{
	if (pHead)
	{
		czytelnik * p = pHead->pNext;
		delete pHead;
		usun_liste_czytelnikow(p);
		pHead = nullptr;
	}
}

void usun_liste_ksiazek(ksiazka * & pHead)
{
	if (pHead)
	{
		ksiazka * p = pHead->pNext;
		delete pHead;
		usun_liste_ksiazek(p);
		pHead = nullptr;
	}
}

czytelnik *wybierz_czytelnika(czytelnik * &pHead)
{
	cout << "Wybierz numer id czytelnika" << endl;
	wypisz_czytelnikow(pHead, cout);
	cout << endl;
	int id;

	czytelnik *e = nullptr;
	czytelnik *p = pHead;

	bool czy_jest = false;

	while (!(cin >> id))
	{
		cout << "podales litere, sprobuj ponownie" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	while (!czy_jest)
	{
		czytelnik *s = pHead;
		while (s)
		{
			if (s->ic == id)
				break;
			else
				s = s->pNext;
		}
		if (s == nullptr)
		{
			cout << "nie ma takiego czytelnika, sprobuj ponownie" << endl;

			while (!(cin >> id))
			{
				cout << "podales litere, sprobuj ponownie" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else
			czy_jest = true;
	}

	for (unsigned i = 1; p; p = p->pNext)
	{
		if (p->ic == id)
			e = p;
	}
	return e;
}

ksiazka *wybierz_ksiazke(ksiazka * &pHead)
{
	cout << "Wybierz numer id ksiazki" << endl << endl;
	wypisz_ksiazki(pHead, cout);
	cout << endl;
	int id;

	ksiazka *e = nullptr;
	ksiazka *p = pHead;
	
	bool czy_jest = false;

	while (!(cin >> id))
	{
		cout << "podales litere, sprobuj ponownie" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	while (!czy_jest)
	{
		ksiazka *s = pHead;
		while (s)
		{
			if (s->ik == id)
				break;
			else
				s = s->pNext;
		}
		if (s == nullptr)
		{
			cout << "nie ma takiej ksiazki, sprobuj ponownie" << endl;
			while (!(cin >> id))
			{
				cout << "podales litere, sprobuj ponownie" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else
			czy_jest = true;
	}
	
	for (unsigned i = 1; p; p = p->pNext)
	{
		if (p->ik == id)
			e = p;
	}
	return e;
}

elData podaj_date()
{
	elData data_wypozyczenia;
	int rok;
	int miesiac;
	int dzien;

	do
	{
		cout << "Podaj rok: ";
		while (!(cin >> rok))
		{
			cout << "podales litere, sprobuj ponownie" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (rok < 0)
			cout << "Rok nie moze byc liczba ujemna, sprobuj ponownie" << endl;
	} while (rok < 0);

	cout << endl;

	do
	{
		cout << "Podaj miesiac: ";
		while (!(cin >> miesiac))
		{
			cout << "podales litere, sprobuj ponownie" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << endl;

		if (miesiac > 12 or miesiac < 0)
			cout << "blad" << endl;
	} while (miesiac > 12 or miesiac < 0);

	if (miesiac == 1 or miesiac == 3 or miesiac == 5 or miesiac == 7 or miesiac == 8 or miesiac == 10 or miesiac == 12)
	{
		do
		{
			cout << "Podaj dzien: ";
			while (!(cin >> dzien))
			{
				cout << "podales litere, sprobuj ponownie" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl;

			if (dzien > 31 or dzien < 0)
				cout << "blad" << endl;
		} while (dzien > 31 or dzien < 0);
	}

	else if (miesiac == 2)
	{
		if ((rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0)
		{
			do
			{
				cout << "Podaj dzien: ";
				while (!(cin >> dzien))
				{
					cout << "podales litere, sprobuj ponownie" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << endl;

				if (dzien > 29 or dzien < 0)
					cout << "blad" << endl;
			} while (dzien > 29 or dzien < 0);
		}
		else
		{
			do
			{
				cout << "Podaj dzien: ";
				while (!(cin >> dzien))
				{
					cout << "podales litere, sprobuj ponownie" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << endl;

				if (dzien > 28 or dzien < 0)
					cout << "blad" << endl;
			} while (dzien > 28 or dzien < 0);
		}
	}
	else
	{
		do
		{
			cout << "Podaj dzien: ";
			while (!(cin >> dzien))
			{
				cout << "podales litere, sprobuj ponownie" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << endl;

			if (dzien > 30 or dzien < 0)
				cout << "blad" << endl;
		} while (dzien > 30 or dzien < 0);
	}

	cout << "Data to: " << dzien << "." << miesiac << "." << rok << "r." << endl;

	data_wypozyczenia.rok = rok;
	data_wypozyczenia.miesiac = miesiac;
	data_wypozyczenia.dzien = dzien;

	return data_wypozyczenia;
}

elData dodaj_miesiac(elData data)
{
	data.miesiac += 1;

	if (data.miesiac > 12)
	{
		data.rok += 1;
		data.miesiac = 1;
	}

	else if (data.miesiac == 4 or data.miesiac == 6 or data.miesiac == 9 or data.miesiac == 11)
	{
		if (data.dzien == 31)
		{
			data.miesiac += 1;
			data.dzien = 1;
		}
	}

	else if (data.miesiac == 2)
	{
		if ((data.rok % 4 == 0 && data.rok % 100 != 0) || data.rok % 400 == 0)
		{
			if (data.dzien > 29)
			{
				data.miesiac += 1;
				data.dzien = data.dzien - 29;
			}
		}
		else
		{
			if (data.dzien > 28)
			{
				data.miesiac += 1;
				data.dzien = data.dzien - 28;
			}
		}
	}
	return data;
}

void usun_czytelnika(czytelnik * & pHead, czytelnik * e)
{
	czytelnik * p;

	if (e->ile != 0)
		cout << "Ten czytelnik ma wypozyczona ksiazke i nie mozna go usunac" << endl;

	else
	{
		cout << "usunieto czytelnika o numerze id: " << e->ic << endl;
		if (pHead == e)  //jeśli wybrany element znajduje sie na początku listy
		{
			p = pHead; // zapamiętujemy początek

			if (p)
			{
				pHead = p->pNext;   // nowy początek
				delete p;         // usuń element z pamięci
			}
		}
		else // jeśli gdzies indziej
		{
			p = pHead;
			while (p->pNext != e) p = p->pNext;
			p->pNext = e->pNext;
			delete e;
		}
	}
	
}

void usun_ksiazke(ksiazka * & pHead, ksiazka * e)
{
	ksiazka * p;

	if (e->ic == 0)
	{
		cout << "usunieto ksiazke o numerze id: " << e->ik << endl;
		if (pHead == e)  //jeśli wybrany element znajduje się na początku listy
		{
			ksiazka * p = pHead; // zapamiętujemy początek

			if (p)
			{
				pHead = p->pNext;   // nowy początek
				delete p;         // usuń element z pamięci
			}
		}
		else // jeśli gdzieś indziej
		{
			p = pHead;
			while (p->pNext != e)
				p = p->pNext;
			p->pNext = e->pNext;
			delete e;
		}
	}
	else
	{
		cout << "Ta ksiazka jest wypozyczona i nie mozna jej usunac" << endl;
	}
	
}

void wypozycz(czytelnik * & pHeadC, ksiazka * & pHeadK, wypozyczone * & pHead)
{
	ksiazka *wypozyczona_ksiazka;
	elData data_wypozyczenia;
	string takczynie;
	ksiazka * k = pHeadK;
	wypozyczone * w = pHead;

	data_wypozyczenia = podaj_date();

	cout << "Ktory czytelnik chce wypozyczyc ksiazke? Wybierz id" << endl;
	cout << endl;

	do
	{
		ksiazka *p = pHeadK;
		czytelnik *czlowiek = pHeadC;
		//na początku pętli wskaźnik wskazuje na głowe listy książek
		czlowiek = wybierz_czytelnika(czlowiek);

		if (czlowiek->ile >= 5)  //sprawdzanie czy czytelnik ma więcej ni 5 wypożyczonych książek
		{
			cout << "Ten czytelnik ma wypozyczonych wiecej niz 5 ksiazek i nie moze juz nic wiecej wypozyczyc" << endl;
			break;
		}

		cout << "Jaka ksiazke chce wypozyczyc? Wybierz id" << endl;
		cout << endl;

		do
		{
			wypozyczona_ksiazka = wybierz_ksiazke(p);

			if (wypozyczona_ksiazka->ic != 0)
				cout << "Ta ksiazka jest juz wypozyczona" << endl << "Prosze sprobowac ponownie" << endl << endl;

		} while (wypozyczona_ksiazka->ic != 0);

		czlowiek->ile += 1;
		wypozyczona_ksiazka->ic = czlowiek->ic;
		wypozyczona_ksiazka->rok_wyp = data_wypozyczenia.rok;
		wypozyczona_ksiazka->miesiac_wyp = data_wypozyczenia.miesiac;
		wypozyczona_ksiazka->dzien_wyp = data_wypozyczenia.dzien;

		if (not pHead) // lista pusta
		{
			pHead = new wypozyczone{ czlowiek->ic, wypozyczona_ksiazka->ik, nullptr, wypozyczona_ksiazka};
		}
		else // lista już coś zawiera
		{
			wypozyczone * pNowy = new wypozyczone{ czlowiek->ic, wypozyczona_ksiazka->ik, nullptr, wypozyczona_ksiazka };
			wypozyczone * p = pHead;
			while (p->pNext)
				p = p->pNext;
			// zatrzymalismy się, tzn. p->pNext == nullptr
			p->pNext = pNowy;
		}
		cout << "Czy chce wypozyczyc jeszcze jedna ksiazke? [t/n]" << endl;
		do
		{
			cin >> takczynie;
			if (takczynie != "t" and takczynie != "n")
				cout << "wybierz [t] lub [n]" << endl;
		} while (takczynie != "t" and takczynie != "n");
		
	} while (takczynie == "t");
}

void wypisz_wypozyczone(ksiazka * & pHeadK, wypozyczone * & pHead, czytelnik * & czlowiek)
{
	wypozyczone *w=pHead;
	ksiazka *k = pHeadK;

	cout << "lista ksiazek " << czlowiek->imie << " " << czlowiek->nazwisko << " " << czlowiek->ic<< " :" << endl;

	for (unsigned i = 1; w; w = w->pNext)
	{
		if (w->ic == czlowiek->ic)
			cout << w->wsk->tytul << " " << w->wsk->autor << " " << w->wsk->ik << endl;
	}
}

void oddaj(ksiazka * & pHeadK, wypozyczone * & pHead, czytelnik * & pHeadC)
{
	czytelnik *czlowiek = pHeadC;
	wypozyczone *e;
	czytelnik *c = pHeadC;
	string takczynie;

	do
	{
		ksiazka *do_oddania = pHeadK;
		ksiazka * ks = pHeadK;
		czytelnik *c1 = pHeadC;

		cout << "Kto chce oddac ksiazke?: " << endl;
		cout << "Wybierz czytelnika: " << endl;
		czlowiek = wybierz_czytelnika(c);
		wypisz_wypozyczone(ks, pHead, czlowiek);

		if (czlowiek->ile == 0)
		{
			cout << "Ten czytelnik nie ma ksiazek" << endl;
			break;
		}

		ks = pHeadK;
		do_oddania = wybierz_ksiazke(ks);

		if (do_oddania->ic != czlowiek->ic)
		{
			cout << "blad" << endl;
			break;
		}
		else
		{
			do_oddania->ic = 0;		//książka oddana
			do_oddania->dzien_wyp = 0;
			do_oddania->miesiac_wyp = 0;
			do_oddania->rok_wyp = 0;
			czlowiek->ile = czlowiek->ile - 1;
			cout << "oddano ksiazke o numerze id: " << do_oddania->ik << endl;
			e = wsk_na_wypozyczona(do_oddania, pHead);
			usun_wypozyczona(pHead, e);
		}

		cout << "Czy chcesz oddac jeszcze jedna ksiazke? [t/n]" << endl;
		do
		{
			cin >> takczynie;
			if (takczynie != "t" and takczynie != "n")
				cout << "wybierz [t] lub [n]" << endl;
		} while (takczynie != "t" and takczynie != "n");

	} while (takczynie == "t");
}

void po_terminie(wypozyczone * & pHead,czytelnik * & pHeadC, ostream & ss)
{
	czytelnik * czlowiek = pHeadC;
	wypozyczone * k = pHead;
	elData kiedy_wypozyczona;
	elData termin;
	elData plus_miesiac;

	termin = podaj_date();
	cout << endl;
	cout << "Lista ksiazek, ktorych termin oddania minal: " << endl << endl;
	for (unsigned i = 1; k; k = k->pNext)
	{
		if (k->ic != 0)
		{
			kiedy_wypozyczona.rok = k->wsk->rok_wyp;
			kiedy_wypozyczona.miesiac = k->wsk->miesiac_wyp;
			kiedy_wypozyczona.dzien = k->wsk->dzien_wyp;

			plus_miesiac = dodaj_miesiac(kiedy_wypozyczona);	

			if (plus_miesiac.rok < termin.rok)
			{
				while (czlowiek->ic != k->ic)
					czlowiek = czlowiek->pNext;
				cout << czlowiek->imie << " " << czlowiek->nazwisko << " id czyt: "<< czlowiek->ic<<" "<< k->wsk->tytul <<" - "<< k->wsk->autor << " id ks: " << k->ik<< endl;
			}

			else if (plus_miesiac.miesiac < termin.miesiac)
			{
				while (czlowiek->ic != k->ic)
					czlowiek = czlowiek->pNext;
				cout << czlowiek->imie << " " << czlowiek->nazwisko << " id czyt: " << czlowiek->ic << " " << k->wsk->tytul << " - " << k->wsk->autor << " id ks: " << k->ik << endl;
			}

			else if (plus_miesiac.dzien < termin.dzien)
			{
				while (czlowiek->ic != k->ic)
					czlowiek = czlowiek->pNext;
				cout << czlowiek->imie << " " << czlowiek->nazwisko << " id czyt: " << czlowiek->ic << " " << k->wsk->tytul << " - " << k->wsk->autor << " id ks: " << k->ik << endl;
			}
		}
	}
}

void raport_czytelnika(ksiazka * & pHeadK, czytelnik * & pHeadC, wypozyczone * & pHead)
{
	czytelnik *czlowiek =pHeadC;
	ksiazka * k = pHeadK;
	wypozyczone * w = pHead;
	ofstream zapis("raport.txt");

	cout << "Wybierz czytelnika ktorego raport chcesz zapisac do pliku: " << endl;
	czlowiek = wybierz_czytelnika(pHeadC);

	zapis << "ksiazki " << czlowiek->imie <<" "<< czlowiek->nazwisko <<  ":" << endl;

	for (unsigned i = 1; w; w = w->pNext)
	{
		if (czlowiek->ic == w->wsk->ic)
			zapis << "TYTUŁ: " << " " << w->wsk->tytul << " AUTOR: " << w->wsk->autor << " ID KSIĄŻKI: " << w->wsk->ik << " DATA WYPOŻYCZENIA: " << w->wsk->dzien_wyp << "." << w->wsk->miesiac_wyp << "." << w->wsk->rok_wyp << "r." << endl;
	}	
	zapis.close();
}

void zapisz_do_plikow(ksiazka * & pHeadK, czytelnik * & pHeadC)
{
	ksiazka * k = pHeadK;
	czytelnik * c = pHeadC;
	ofstream zapisK("ksiazki.txt");
	ofstream zapisC("czytelnicy.txt");
	ofstream zapisK_wyj("ksiazki_wyj.txt");
	ofstream zapisC_wyj("czytelnicy_wyj.txt");

	for (unsigned i = 1; k; k = k->pNext)
		zapisK << k->tytul << " " << k->autor << " " << k->ik << " " << k->rok_wyp << " " << k->miesiac_wyp<< " " <<k->dzien_wyp << " "<< k->ic << endl;

	for (unsigned l = 1; c; c = c->pNext)
		zapisC << c->imie<< " " << c->nazwisko << " " << c->ic << " " << c->ile << endl;

	k = pHeadK;
	c = pHeadC;

	for (unsigned i = 1; k; k = k->pNext)
		zapisK_wyj << k->tytul << " " << k->autor << " " << k->ik << " " << k->rok_wyp << " " << k->miesiac_wyp << " " << k->dzien_wyp << " " << k->ic << endl;

	for (unsigned l = 1; c; c = c->pNext)
		zapisC_wyj << c->imie << " " << c->nazwisko << " " << c->ic << " " << c->ile << endl;

	zapisK_wyj.close();
	zapisC_wyj.close();
	zapisK.close();
	zapisC.close();
}

void wypisz_plikC(ifstream & ludzie)
{
	string imie;
	string nazwisko;
	int ic, ile;

	if (ludzie.good())
	{
		while (ludzie >> imie)
		{
			ludzie >> nazwisko >> ic >> ile;
			cout << imie << " " << nazwisko << " " << ic << " " << ile << endl;	
		}
	}
}

void wypisz_plikK(ifstream & ksiazki)
{
	string tytul;
	string autor;
	int rok, miesiac, dzien, ic, ik;

	if (ksiazki.good())
	{
		while (ksiazki>>tytul)
		{
			ksiazki >> autor >> ik >> rok >> miesiac >> dzien >> ic;
			cout << tytul << " " << autor << " " << ik << " " << rok << " " << miesiac<< " " << dzien << " " << ic << endl;		
		}
	}
}

void usun_liste_wypozyczonych(wypozyczone * & pHead)
{
	if (pHead)
	{
		wypozyczone * p = pHead->pNext;
		delete pHead;
		usun_liste_wypozyczonych(p);
		pHead = nullptr;
	}
}

wypozyczone *wsk_na_wypozyczona(ksiazka * & k, wypozyczone * & pHead )
{
	wypozyczone *e = nullptr;
	wypozyczone *p = pHead;

	for (unsigned i = 1; p; p = p->pNext)
	{
		if (p->ik == k->ik)
			e = p;
	}
	return e;
}

void usun_wypozyczona(wypozyczone * & pHead, wypozyczone * e)
{
	wypozyczone * p;

	if (e->wsk != nullptr)
	{
		cout << "usunieto ksiazke wypozyczona o numerze id: " << e->ik << endl;
		if (pHead == e)  //jeśli wybrany element znajduje się na początku listy
		{
			wypozyczone * p = pHead; // zapamiętujemy początek

			if (p)
			{
				pHead = p->pNext;   // nowy początek
				delete p;         // usuń element z pamięci
			}
		}
		else // jeśli gdzieś indziej
		{
			p = pHead;
			while (p->pNext != e)
				p = p->pNext;
			p->pNext = e->pNext;
			delete e;
		}
	}
	else
	{
		cout << "Ta ksiazka nie jest wypozyczona i nie mozna jej usunac" << endl;
	}
}

void dodaj_wypozyczone_do_listy(ksiazka * & pHeadK, wypozyczone * & pHead)
{
	ksiazka *k = pHeadK;

	for (unsigned i = 1; k; k = k->pNext)
	{
		if (k->ic != 0)
		{
			if (not pHead) // lista pusta
			{
				pHead = new wypozyczone{ k->ic, k->ik,  nullptr, k };
			}
			else // lista już coś zawiera
			{
				wypozyczone * pNowy = new wypozyczone{ k->ic, k->ik, nullptr, k };
				wypozyczone * p = pHead;
				while (p->pNext)
					p = p->pNext;
				// zatrzymalismy się, tzn. p->pNext == nullptr
				p->pNext = pNowy;
			}
		}
	}	
}

