#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream>
#include <string>

using namespace std;

/** element listy jednokierunkowej czytelników */
struct czytelnik
{
	string imie;
	string nazwisko;
	int ic;				///<identyfikator czytelnika
	int ile;			///<ile ksi¹¿ek wypo¿yczy³
	czytelnik * pNext;   ///< wskaznik na nastepnego czytelnika
};  // <--- œrednik jest niezbêdny

/** element listy jednokierunkowej ksi¹¿ek */
struct ksiazka
{
	string tytul;
	string autor;
	int ik;				///<identyfikator ksi¹¿ki
	int rok_wyp;
	int miesiac_wyp;
	int dzien_wyp;
	int ic;				///<identyfikator czytelnika który wypo¿yczy³ ksi¹¿kê
	ksiazka * pNext;   ///< wskaznik na nastepn¹ ksi¹¿kê
};  // <--- œrednik jest niezbêdny

/** element data */
struct elData
{
	int rok;
	int miesiac;
	int dzien;
};

struct wypozyczone
{
	int ic;			///< identyfikator czytelnika, który wypo¿yczy³ ksi¹¿kê
	int ik;			///< identyfikator wypo¿yczonej ksi¹¿ki
	wypozyczone * pNext;	///< wskaznik na nastepn¹ wypo¿yczon¹ ksi¹¿kê
	ksiazka *wsk;		///< wskaznik na ksi¹¿kê z listy wszystkich ksi¹¿ek
};
#endif
