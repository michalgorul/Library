#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream>
#include <string>

using namespace std;

/** element listy jednokierunkowej czytelnik�w */
struct czytelnik
{
	string imie;
	string nazwisko;
	int ic;				///<identyfikator czytelnika
	int ile;			///<ile ksi��ek wypo�yczy�
	czytelnik * pNext;   ///< wskaznik na nastepnego czytelnika
};  // <--- �rednik jest niezb�dny

/** element listy jednokierunkowej ksi��ek */
struct ksiazka
{
	string tytul;
	string autor;
	int ik;				///<identyfikator ksi��ki
	int rok_wyp;
	int miesiac_wyp;
	int dzien_wyp;
	int ic;				///<identyfikator czytelnika kt�ry wypo�yczy� ksi��k�
	ksiazka * pNext;   ///< wskaznik na nastepn� ksi��k�
};  // <--- �rednik jest niezb�dny

/** element data */
struct elData
{
	int rok;
	int miesiac;
	int dzien;
};

struct wypozyczone
{
	int ic;			///< identyfikator czytelnika, kt�ry wypo�yczy� ksi��k�
	int ik;			///< identyfikator wypo�yczonej ksi��ki
	wypozyczone * pNext;	///< wskaznik na nastepn� wypo�yczon� ksi��k�
	ksiazka *wsk;		///< wskaznik na ksi��k� z listy wszystkich ksi��ek
};
#endif
