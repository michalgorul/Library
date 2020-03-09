#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <iostream>
#include <string>

#include "struktury.h"

using namespace std;

/** Funkcja pobiera znak od uzytkownika, który wybiera jaką akcje chce podjąć
@return Konkretny numer czytany przez program
*/
int wybor_akcji();

/** Funkcja czyta z pliku
@param pHeadC wskaźnik na początek listy czytelników
@param ludzie plik z czytelnikami
*/
void czytaj_z_plikuC(czytelnik * & pHeadC, ifstream & ludzie);

/** Funkcja czyta z pliku
@param pHeadK wskaźnik na początek listy książek
@param ksiazki plik z książkami
*/
void czytaj_z_plikuK(ksiazka * & pHeadK, ifstream & ksiazki);

/** Funkcja dodaje książki do listy jednokierunkowej.
@param pHeadK wskaznik na pierwszy element listy czytelników
@param tytul tytuł książki
@param autor autor książki
@param ik identyfikator książki
@param rok rok wypożyczenia
@param miesiac miesiac wypożyczenia
@param dzien dzień wypożyczenia
@param ic ew. identyfikator wypożyczającego, jeżeli wolna ic==0
*/
void dodaj_ksiazki_do_listy(ksiazka * & pHeadK, string tytul, string autor, int ik, int rok, int miesiac, int dzien, int ic);

/** Funkcja dodaje czytelnikow do listy jednokierunkowej.
@param pHeadC wskaznik na pierwszy element listy czytelników
@param imie imie czytelnika
@param nazwisko nazwisko czytelnika
@param ic identyfikator czytelnika
@param ile ile książek wypożyczył
*/
void dodaj_czytelnikow_do_listy(czytelnik * & pHeadC, string imie, string nazwisko, int ic, int ile);

/** Funkcja wypisuje listę książek z identyfikatorem(rekurencyjnie).
@param pHead wskaznik na pierwszy element listy
@param[in, out] ss strumień do wypisania
*/
void wypisz_ksiazki(ksiazka * pHead, ostream & ss);

/** Funkcja wypisuje listę książek ze wszystkimi danymi z pliku(z użyciem listy jednokierunkowej).
@param pHead wskaznik na pierwszy element listy
@param[in, out] ss strumień do wypisania
*/
void wypisz_plik_ksiazki(ksiazka * pHead, ostream & ss);

/** Funkcja wypisuje listę czytelników(rekurencyjnie).
@param pHead wskaznik na pierwszy element listy czytelników
@param[in, out] ss strumień do wypisania
*/
void wypisz_czytelnikow(czytelnik * pHead, ostream & ss);

/** Funkcja wypisuje listę czytelników ze wszystkimi danymi z pliku(z użyciem listy jednokierunkowej).
@param pHead wskaznik na pierwszy element listy czytelników
@param[in, out] ss strumień do wypisania
*/
void wypisz_plik_czytelnikow(czytelnik * pHead, ostream & ss);

/** Funkcja usuwa listę czytelników rekurencyjnie.
@param pHead wskaźnik na pierwszy element listy – po usunięciu listy jest równy nullptr.
*/
void usun_liste_czytelnikow(czytelnik * & pHead);

/** Funkcja usuwa listę książek rekurencyjnie.
@param pHead wskaźnik na pierwszy element listy – po usunięciu listy jest równy nullptr.
*/
void usun_liste_ksiazek(ksiazka * & pHead);

/** Funkcja wybiera książkę
@param pHead wskaźnik na pierwszy element listy
@return wskaźnik na wybranegą książkę
*/
ksiazka *wybierz_ksiazke(ksiazka * &pHead);

/** Funkcja wybiera czytelnika
@param pHead wskaźnik na pierwszy element listy
@return wskaźnik na wybranego czytelnika
*/
czytelnik *wybierz_czytelnika(czytelnik * &pHead);

/** Funkcja zwraca wybraną przez urzytkownika
@return element data
*/
elData podaj_date();

/** Funkcja dodaje miesiąc do wyznaczonej daty
@param data podana data
@return element data
*/
elData dodaj_miesiac(elData data);

/** Funkcja usuwa książkę
@param pHead wskaźnik na pierwszy element listy
@param e wybrany przez nas element do usunięcia z listy książek
*/
void usun_ksiazke(ksiazka * & pHead, ksiazka * e);

/** Funkcja usuwa czytelnika
@param pHead wskaźnik na pierwszy element listy
@param e wybrany przez nas element do usunięcia z listy czytelników
*/
void usun_czytelnika(czytelnik * & pHead, czytelnik * e);

/** Funkcja wypożycza książkę czytelnikowi + zapisuje date wypożyczenia
@param pHeadC wskażnik na pierwszy element listy czytelników
@param pHeadC wskażnik na pierwszy element listy książek
@param pHead wskażnik na pierwszy element listy wypożyczonych książek czytelnika
*/
void wypozycz(czytelnik * & pHeadC, ksiazka * & pHeadK, wypozyczone * & pHead);

/** Funkcja wypisuje listę książek wypożyczonych przez wybranego czytelnika
@param pHeadK wskaznik na pierwszy element listy książek
@param pHead wskaznik na pierwszy element listy wypożyczonych książek
@param pHeadC wskaznik na pierwszy element listy czytelników
*/
void wypisz_wypozyczone(ksiazka * & pHeadK, wypozyczone * & pHead, czytelnik * & czlowiek);

/** Funkcja oddaje książkę wypożyczoną przez czytelnika
@param pHeadK wskaznik na pierwszy element listy książek
@param pHead wskaznik na pierwszy element listy wypożyczonych książek
@param pHeadC wskaznik na pierwszy element listy czytelników
*/
void oddaj(ksiazka * & pHeadK, wypozyczone * & pHead, czytelnik * & pHeadC);

/** Funkcja generuje liste książek po terminie zwrotu (+ informacje o czytelnikach którzy je wypożyczyli)
@param pHead wskaźnik na liste książek wypożyczonych
@param pHeadK wskaźnik na liste książek
@param[in, out] s strumień do wypisania
*/
void po_terminie(wypozyczone * & pHead, czytelnik * & pHeadC, ostream & ss);

/** Funkcja generuje plik-raport: informacje o książkach które wypożyczył czytelnik
@param pHeadK wskaźnik na liste książek
@param pHeadC wskaźnik na liste czytelników
@param pHead wskaźnik na liste wypożyczonych książek

*/
void raport_czytelnika(ksiazka * & pHeadK, czytelnik * & pHeadC, wypozyczone * & pHead);

/** Funkcja zapisuje zmiany dokonane w programie do pliku wyjściowego
@param pHeadK wskaźnik na liste książek
@param pHeadC wskaźnik na liste czytelników
*/
void zapisz_do_plikow(ksiazka * & pHeadK, czytelnik * & pHeadC);

/** Funkcja czyta z pliku i wypisuje w konsoli(bez list jednokierunkowych)
@param ludzie plik z książkami
*/
void wypisz_plikC(ifstream & ludzie);

/** Funkcja czyta z pliku i wypisuje w konsoli(bez list jednokierunkowych)
@param ksiazki plik z książkami
*/
void wypisz_plikK(ifstream & ksiazki);

/** Funkcja usuwa listę wypożyczonych książek rekurencyjnie.
@param pHead wskaźnik na pierwszy element listy – po usunięciu listy jest równy nullptr.
*/
void usun_liste_wypozyczonych(wypozyczone * & pHead);

/** Funkcja zwraca wskaźnik na wypożyczoną książkę
@param pHead wskaźnik na pierwszy element listy wypożyczonych
@param k element książka
@return wskaźnik na wybraną wypożyczoną książkę
*/
wypozyczone *wsk_na_wypozyczona(ksiazka * & k, wypozyczone * & pHead);

/** Funkcja usuwa wypożyczoną książkę
@param pHead wskaźnik na pierwszy element listy
@param e wybrany przez nas element do usunięcia z listy wypożyczonych książek
*/
void usun_wypozyczona(wypozyczone * & pHead, wypozyczone * e);

/** Funkcja dodaje książki wypożyczone do listy jednokierunkowej.
@param pHeadk wskaznik na pierwszy element listy książek
@param pHead wskaznik na pierwszy element listy wypożyczonych książek
*/
void dodaj_wypozyczone_do_listy(ksiazka * & pHeadK, wypozyczone * & pHead);

#endif
