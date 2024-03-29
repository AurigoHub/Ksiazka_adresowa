#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct DaneUzytkownika
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct DaneAdresata
{
    int idAdresata, wlascicielWpisu;
    string imie, nazwisko, adres, telefon, email;
};

void wyswietlHeaderMenu ()
{
    system("cls");
    cout << "**********************************" << endl;
    cout << "*        KSI��KA ADRESOWA        *" << endl;
    cout << "**********************************" << endl << endl;
}

void wyswietlMenuStartowe ()
{
    wyswietlHeaderMenu ();
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zako�cz program" << endl;
    cout << endl;
}

void wyswietlMenuZAdresatami ()
{
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Lista zapisanych adresat�w" << endl;
    cout << "5. Usu� adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "7. Zmie� has�o" << endl;
    cout << "8. Wyloguj" << endl;
    cout << endl;
}

void wyswietlDaneAdresata (vector <DaneAdresata> &adresaci, int i)
{
    cout << "NUMER ID WPISU: " << adresaci[i].idAdresata << endl;
    cout << "IMI�: " << adresaci[i].imie << endl;
    cout << "NAZWISKO: " << adresaci[i].nazwisko << endl;
    cout << "ADRES: " << adresaci[i].adres << endl;
    cout << "TELEFON: " << adresaci[i].telefon << endl;
    cout << "E-MAIL: " << adresaci[i].email << endl << endl;
}

void wyswietlMenuEdycji (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata)
{
    wyswietlHeaderMenu();
    cout << "Aktualne dane wybranego adresata: " << endl << endl;
    wyswietlDaneAdresata (adresaci, indeksWyszukanegoAdresata);

    cout << "Wybierz pole do edycji: " << endl;
    cout << "1. IMI�" << endl;
    cout << "2. NAZWISKO" << endl;
    cout << "3. ADRES" << endl;
    cout << "4. TELEFON" << endl;
    cout << "5. E-MAIL" << endl;
    cout << "6. Zapisz zmiany i zako�cz edycj�" << endl << endl;
}

void wczytajSegmentZLiniiTekstuSpisuUzytkownikow (vector <DaneUzytkownika> &uzytkownicy, int liczbaUzytkownikow, string segmentDanychUzytkownika, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        uzytkownicy[liczbaUzytkownikow].idUzytkownika = atoi(segmentDanychUzytkownika.c_str());
        break;
    case 2:
        uzytkownicy[liczbaUzytkownikow].nazwa = segmentDanychUzytkownika;
        break;
    case 3:
        uzytkownicy[liczbaUzytkownikow].haslo = segmentDanychUzytkownika;
        break;
    }
}

void wczytajUzytkownikowZPliku (vector <DaneUzytkownika> &uzytkownicy)
{
    fstream spisUzytkownikow;
    string liniaTekstuSpisuUzytkownikow;
    int liczbaUzytkownikow = 0;

    spisUzytkownikow.open ("Uzytkownicy.txt", ios::in);
    if (spisUzytkownikow.good() == true)
    {
        while (getline(spisUzytkownikow,liniaTekstuSpisuUzytkownikow))
        {
            uzytkownicy.push_back(DaneUzytkownika());
            stringstream ss (liniaTekstuSpisuUzytkownikow);
            string segmentDanychUzytkownika;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychUzytkownika, '|'))
            {
                wczytajSegmentZLiniiTekstuSpisuUzytkownikow (uzytkownicy, liczbaUzytkownikow, segmentDanychUzytkownika, numerSegmentuWLiniiTekstu);
                numerSegmentuWLiniiTekstu ++;
            }
            liczbaUzytkownikow ++;
        }
    }
    spisUzytkownikow.close();
}

void wczytajPierwszeDwaSegmentyLinii (DaneAdresata &buforAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 1:
        buforAdresatow.idAdresata = atoi(segmentDanychAdresata.c_str());
        break;
    case 2:
        buforAdresatow.wlascicielWpisu = atoi(segmentDanychAdresata.c_str());
        break;
    }
}

void  wczytajPozostaleSegmentyLinii (DaneAdresata &buforAdresatow, string segmentDanychAdresata, int numerSegmentuWLiniiTekstu)
{
    switch (numerSegmentuWLiniiTekstu)
    {
    case 3:
        buforAdresatow.imie = segmentDanychAdresata;
        break;
    case 4:
        buforAdresatow.nazwisko = segmentDanychAdresata;
        break;
    case 5:
        buforAdresatow.adres = segmentDanychAdresata;
        break;
    case 6:
        buforAdresatow.telefon = segmentDanychAdresata;
        break;
    case 7:
        buforAdresatow.email = segmentDanychAdresata;
        break;
    }
}

void skopiujBuforDoWektoraAdresatow (DaneAdresata &buforAdresatow, vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    adresaci.push_back(DaneAdresata());
    adresaci[liczbaAdresatow].idAdresata = buforAdresatow.idAdresata;
    adresaci[liczbaAdresatow].wlascicielWpisu = buforAdresatow.wlascicielWpisu;
    adresaci[liczbaAdresatow].imie = buforAdresatow.imie;
    adresaci[liczbaAdresatow].nazwisko = buforAdresatow.nazwisko;
    adresaci[liczbaAdresatow].adres = buforAdresatow.adres;
    adresaci[liczbaAdresatow].telefon = buforAdresatow.telefon;
    adresaci[liczbaAdresatow].email = buforAdresatow.email;
}

int wczytajAdresatowZPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    fstream ksiazkaAdresowa;
    string liniaTekstuSpisuAdresatow;
    DaneAdresata buforAdresatow;
    buforAdresatow.wlascicielWpisu = 0;

    ksiazkaAdresowa.open ("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstuSpisuAdresatow))
        {
            stringstream ss (liniaTekstuSpisuAdresatow);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                if (numerSegmentuWLiniiTekstu <= 2)
                {
                    wczytajPierwszeDwaSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                    if ((numerSegmentuWLiniiTekstu == 2) && (buforAdresatow.wlascicielWpisu != idZalogowanegoUzytkownika))
                        break;
                }
                if ((numerSegmentuWLiniiTekstu > 2) || (buforAdresatow.wlascicielWpisu == idZalogowanegoUzytkownika))
                {
                    wczytajPozostaleSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                }
                numerSegmentuWLiniiTekstu ++;
            }

            if (buforAdresatow.wlascicielWpisu == idZalogowanegoUzytkownika)
            {
                skopiujBuforDoWektoraAdresatow (buforAdresatow, adresaci, liczbaAdresatow);
                liczbaAdresatow ++;
            }
        }
    }
    ksiazkaAdresowa.close();

    return liczbaAdresatow;
}

int sprawdzIdOstatniegoAdresata ()
{
    fstream ksiazkaAdresowa;
    string liniaTekstuSpisuAdresatow;
    int najwiekszeIdAdresata = 0;
    DaneAdresata buforAdresatow;
    buforAdresatow.wlascicielWpisu = 0;

    ksiazkaAdresowa.open ("Adresaci.txt", ios::in);
    if (ksiazkaAdresowa.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstuSpisuAdresatow))
        {
            stringstream ss (liniaTekstuSpisuAdresatow);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                wczytajPierwszeDwaSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                if (numerSegmentuWLiniiTekstu > 2)
                {
                    break;
                }
                numerSegmentuWLiniiTekstu ++;
            }

            if (buforAdresatow.idAdresata > najwiekszeIdAdresata)
                najwiekszeIdAdresata = buforAdresatow.idAdresata;
        }
    }
    ksiazkaAdresowa.close();

    return najwiekszeIdAdresata;
}

void wyczyscPlikTekstowyZUzytkownikami ()
{
    fstream spisUzytkownikow;
    spisUzytkownikow.open("Uzytkownicy.txt", ios::out|ios::trunc);
    spisUzytkownikow.close();
}

void zapiszUzytkownikowWPliku (vector <DaneUzytkownika> &uzytkownicy)
{
    fstream spisUzytkownikow;
    int liczbaUzytkownikow = uzytkownicy.size();

    spisUzytkownikow.open("Uzytkownicy.txt", ios::out|ios::app);
    if (spisUzytkownikow.good() == true)
    {
        for (int i=0; i<liczbaUzytkownikow; i++)
        {
            spisUzytkownikow << uzytkownicy[i].idUzytkownika << '|';
            spisUzytkownikow << uzytkownicy[i].nazwa << '|';
            spisUzytkownikow << uzytkownicy[i].haslo << endl;
        }
        spisUzytkownikow.close();
    }
    else
    {
        cout << "Nie uda�o si� otworzy� pliku i zapisa� danych!" << endl;
        system("pause");
    }
}

void zapiszDanegoAdresataWPliku (fstream &ksiazkaAdresowaTemp, vector <DaneAdresata> &adresaci, int indeks)
{
    ksiazkaAdresowaTemp << adresaci[indeks].idAdresata << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].wlascicielWpisu << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].imie << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].nazwisko << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].adres << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].telefon << '|';
    ksiazkaAdresowaTemp << adresaci[indeks].email << endl;
}

void zapiszAdresatowWPliku (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika)
{
    fstream ksiazkaAdresowa, ksiazkaAdresowaTemp;
    string liniaTekstuSpisuAdresatow;
    int liczbaAdresatowZapisanychWpliku = 0;
    DaneAdresata buforAdresatow;

    ksiazkaAdresowa.open("Adresaci.txt", ios::in);
    ksiazkaAdresowaTemp.open("Adresaci_temp.txt", ios::out|ios::app);

    if (ksiazkaAdresowaTemp.good() == true)
    {
        while (getline(ksiazkaAdresowa,liniaTekstuSpisuAdresatow))
        {
            stringstream ss (liniaTekstuSpisuAdresatow);
            string segmentDanychAdresata;
            int numerSegmentuWLiniiTekstu = 1;

            while (getline(ss, segmentDanychAdresata, '|'))
            {
                wczytajPierwszeDwaSegmentyLinii (buforAdresatow, segmentDanychAdresata, numerSegmentuWLiniiTekstu);
                numerSegmentuWLiniiTekstu ++;
            }

            if (buforAdresatow.wlascicielWpisu == idZalogowanegoUzytkownika)
            {
                for (int i=0; i<liczbaAdresatow; i++)
                {
                    if (adresaci[i].idAdresata == buforAdresatow.idAdresata)
                        zapiszDanegoAdresataWPliku (ksiazkaAdresowaTemp, adresaci, i);
                }
                liczbaAdresatowZapisanychWpliku ++;
            }
            else
                ksiazkaAdresowaTemp << liniaTekstuSpisuAdresatow << endl;
        }

        if (liczbaAdresatow > liczbaAdresatowZapisanychWpliku)
        {
            int indeksNowegoAdresata = liczbaAdresatow - 1;
            zapiszDanegoAdresataWPliku (ksiazkaAdresowaTemp, adresaci, indeksNowegoAdresata);
        }
    }
    else
    {
        cout << "Nie uda�o si� otworzy� pliku i zapisa� danych!" << endl;
        system("pause");
    }

    ksiazkaAdresowa.close();
    ksiazkaAdresowaTemp.close();
    remove("Adresaci.txt");
    rename("Adresaci_temp.txt","Adresaci.txt");
}

int dodajAdresataDoKsiazki (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idZalogowanegoUzytkownika, int idOstatniegoAdresataWKsiazce)
{
    string imie, nazwisko, adres, telefon, email;
    int indeksNowegoAdresata = 0, idNowegoAdresata;

    cout << "Wpisz imi� adresata: ";
    cin.sync();
    getline(cin,imie);
    cout << "Wpisz nazwisko adresata: ";
    cin.sync();
    getline (cin,nazwisko);
    cout << "Wpisz adres adresata (w jednej linii tekstu): ";
    cin.sync();
    getline(cin,adres);
    cout << "Wpisz numer telefonu adresata: ";
    cin.sync();
    getline(cin,telefon);
    cout << "Wpisz adres e-mail adresata: ";
    cin >> email;

    indeksNowegoAdresata = adresaci.size();
    idNowegoAdresata = idOstatniegoAdresataWKsiazce + 1;

    adresaci.push_back(DaneAdresata());
    adresaci[indeksNowegoAdresata].imie = imie;
    adresaci[indeksNowegoAdresata].nazwisko = nazwisko;
    adresaci[indeksNowegoAdresata].adres = adres;
    adresaci[indeksNowegoAdresata].telefon = telefon;
    adresaci[indeksNowegoAdresata].email = email;
    adresaci[indeksNowegoAdresata].idAdresata = idNowegoAdresata;
    adresaci[indeksNowegoAdresata].wlascicielWpisu = idZalogowanegoUzytkownika;
    liczbaAdresatow++;

    zapiszAdresatowWPliku (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
    cout << endl << "Zapisano." << endl;
    Sleep(1000);

    return liczbaAdresatow;
}

void wyswietlWszystkichAdresatow (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    if (liczbaAdresatow == 0)
    {
        cout << "Ksi��ka adresowa jest pusta." << endl << endl;
        system("pause");
    }
    else
    {
        cout << "Liczba adresat�w zapisanych w ksi��ce adresowej: " << liczbaAdresatow << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            wyswietlDaneAdresata (adresaci, i);
        }
        system("pause");
    }
}

int wyszukajId (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int idSzukanegoAdresata, int idZalogowanegoUzytkownika)
{
    const int NIE_ZNALEZIONO_WYNIKOW = -1;
    int indeksWyszukanegoAdresata;
    int liczbaWynikow = 0;

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if ((adresaci[i].idAdresata == idSzukanegoAdresata) && (adresaci[i].wlascicielWpisu == idZalogowanegoUzytkownika))
        {
            indeksWyszukanegoAdresata = i;
            liczbaWynikow ++;
        }
    }

    if (liczbaWynikow == 0)
    {
        cout << endl << "Nie znaleziono �adnych adresat�w." << endl << endl;
        system("pause");
        return NIE_ZNALEZIONO_WYNIKOW;
    }
    else
        return indeksWyszukanegoAdresata;
}

void wyszukajImie (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string szukaneImie;
    int liczbaWynikow = 0;

    cout << "Wpisz imi� do wyszukania: ";
    cin.sync();
    getline(cin,szukaneImie);

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (adresaci[i].imie == szukaneImie)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono �adnych adresat�w." << endl << endl;
    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat�w w ksi��ce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (adresaci[i].imie == szukaneImie)
                wyswietlDaneAdresata (adresaci, i);
        }
    }
    system("pause");
}

void wyszukajNazwisko (vector <DaneAdresata> &adresaci, int liczbaAdresatow)
{
    string szukaneNazwisko;
    int liczbaWynikow = 0;

    cout << "Wpisz nazwisko do wyszukania: ";
    cin.sync();
    getline(cin,szukaneNazwisko);

    for (int i=0; i<liczbaAdresatow; i++)
    {
        if (adresaci[i].nazwisko == szukaneNazwisko)
            liczbaWynikow ++;
    }

    if (liczbaWynikow == 0)
        cout << endl << "Nie znaleziono �adnych adresat�w." << endl << endl;
    else
    {
        cout << endl << "Znaleziono " << liczbaWynikow << " adresat�w w ksi��ce:" << endl << endl;
        for (int i=0; i<liczbaAdresatow; i++)
        {
            if (adresaci[i].nazwisko == szukaneNazwisko)
                wyswietlDaneAdresata (adresaci, i);
        }
    }
    system("pause");
}

void edytujWybranePole (vector <DaneAdresata> &adresaci, int indeksWyszukanegoAdresata, char wybranyZnakWMenuEdycji)
{
    string nowaWartoscPola;
    cin.clear();
    cin.sync();

    switch (wybranyZnakWMenuEdycji)
    {
    case '1':
        cout << "Wpisz nowe imi� adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].imie = nowaWartoscPola;
        break;
    case '2':
        cout << "Wpisz nowe nazwisko adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].nazwisko = nowaWartoscPola;
        break;
    case '3':
        cout << "Wpisz nowy adres adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].adres = nowaWartoscPola;
        break;
    case '4':
        cout << "Wpisz nowy telefon adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].telefon = nowaWartoscPola;
        break;
    case '5':
        cout << "Wpisz nowy e-mail adresata: ";
        getline(cin,nowaWartoscPola);
        adresaci[indeksWyszukanegoAdresata].email = nowaWartoscPola;
        break;
    }

    cout << endl << "Zaktualizowano." << endl;
    Sleep(1000);
}

int edytujWybranegoAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata, int idZalogowanegoUzytkownika)
{
    char wybranyZnakWMenuEdycji;

    do
    {
        wyswietlMenuEdycji (adresaci, indeksWyszukanegoAdresata);
        cin.clear();
        cin.sync();
        wybranyZnakWMenuEdycji = getch();

        switch (wybranyZnakWMenuEdycji)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
            edytujWybranePole (adresaci, indeksWyszukanegoAdresata, wybranyZnakWMenuEdycji);
            break;
        case '6':
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
            cout << endl << "Zapisano." << endl;
            Sleep(1000);
            return liczbaAdresatow;
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1000);
        }
    }
    while (wybranyZnakWMenuEdycji != '6');
}

int usunWybranegoAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata)
{
    int idAdresataDoUsuniecia = adresaci[indeksWyszukanegoAdresata].idAdresata;

    for (vector <DaneAdresata>::iterator it = adresaci.begin(); it != adresaci.end(); it++)
    {
        if (it->idAdresata == idAdresataDoUsuniecia)
        {
            it = adresaci.erase(it);
            liczbaAdresatow--;
            break;
        }
    }
    return liczbaAdresatow;
}

int potwierdzUsuniecieAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, int indeksWyszukanegoAdresata, int idZalogowanegoUzytkownika)
{
    char wybranyZnakWMenuUsuwania;

    do
    {
        wyswietlHeaderMenu();
        cout << "Aktualne dane wybranego adresata: " << endl << endl;
        wyswietlDaneAdresata (adresaci, indeksWyszukanegoAdresata);
        cout << "Usun�� wybranego adresata z ksi��ki?" << endl << endl;
        cout << "Wybierz TAK (t) lub NIE (n): ";

        cin.clear();
        cin.sync();
        wybranyZnakWMenuUsuwania = getch();

        switch (wybranyZnakWMenuUsuwania)
        {
        case 't':
        case 'T':
            liczbaAdresatow = usunWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata);
            zapiszAdresatowWPliku (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
            cout << endl << endl << "Adresat usuni�ty." << endl;
            Sleep(1000);
            return liczbaAdresatow;
        case 'n':
        case 'N':
            return liczbaAdresatow;
        default:
            cout << endl << endl << "Nie ma takiej opcji!" << endl;
            cout << "Wybierz TAK (t) lub NIE (n)." << endl;
            Sleep(2000);
        }
    }
    while (wybranyZnakWMenuUsuwania != ('n' | 'N'));
}

int modyfikujDaneAdresata (vector <DaneAdresata> &adresaci, int liczbaAdresatow, char wybranyZnak, int idZalogowanegoUzytkownika)
{
    int idSzukanegoAdresata, indeksWyszukanegoAdresata;

    if (wybranyZnak == '5')
        cout << "Wpisz ID adresata do usuni�cia: ";
    else if (wybranyZnak == '6')
        cout << "Wpisz ID adresata do edycji: ";

    cin >> idSzukanegoAdresata;
    indeksWyszukanegoAdresata = wyszukajId (adresaci, liczbaAdresatow, idSzukanegoAdresata, idZalogowanegoUzytkownika);

    if (indeksWyszukanegoAdresata >= 0)
    {
        if (wybranyZnak == '5') // remove address
            liczbaAdresatow = potwierdzUsuniecieAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata, idZalogowanegoUzytkownika);
        else if (wybranyZnak == '6') // edit address
            liczbaAdresatow = edytujWybranegoAdresata (adresaci, liczbaAdresatow, indeksWyszukanegoAdresata, idZalogowanegoUzytkownika);
    }
    return liczbaAdresatow;
}

int zalogujUzytkownika (vector <DaneUzytkownika> &uzytkownicy)
{
    string wpisanaNazwa, wpisaneHaslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Wpisz nazw� u�ytkownika: ";
    cin.sync();
    getline(cin,wpisanaNazwa);

    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].nazwa == wpisanaNazwa)
        {
            for (int j=0; j<3; j++)
            {
                cout << "Podaj has�o (pozosta�o " << 3-j << " pr�b): ";
                cin.sync();
                getline(cin,wpisaneHaslo);

                if (uzytkownicy[i].haslo == wpisaneHaslo)
                {
                    cout << endl << "Zalogowano." << endl;
                    Sleep (1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << endl << "Trzykrotnie wpisano b��dne has�o. Poczekaj 3 sekundy przed kolejn� pr�b�." << endl;
            Sleep (3000);
            return 0;
        }
    }

    cout << endl << "Nie ma takiego u�ytkownika." << endl;
    Sleep(1500);
    return 0;
}

void zarejestrujUzytkownika (vector <DaneUzytkownika> &uzytkownicy)
{
    string nazwa, haslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Wpisz nazw� u�ytkownika: ";
    cin.sync();
    getline(cin,nazwa);

    int i = 0;
    while (i<liczbaUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki u�ytkownik ju� istnieje. Wpisz inn� nazw� u�ytkownika: ";
            cin.sync();
            getline(cin,nazwa);
            i = 0;
        }
        else
            i++;
    }

    cout << "Wpisz has�o: ";
    cin.sync();
    getline (cin,haslo);

    uzytkownicy.push_back(DaneUzytkownika());
    uzytkownicy[liczbaUzytkownikow].nazwa = nazwa;
    uzytkownicy[liczbaUzytkownikow].haslo = haslo;
    uzytkownicy[liczbaUzytkownikow].idUzytkownika = liczbaUzytkownikow + 1;

    wyczyscPlikTekstowyZUzytkownikami ();
    zapiszUzytkownikowWPliku (uzytkownicy);
    cout << endl << "Konto utworzone." << endl;
    Sleep(1000);
}

void zmienHasloZalogowanegoUzytkownika (vector <DaneUzytkownika> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string noweHaslo;
    int liczbaUzytkownikow = uzytkownicy.size();

    wyswietlHeaderMenu ();
    cout << "Podaj nowe has�o: ";
    cin.sync();
    getline (cin,noweHaslo);

    for (int i=0; i<liczbaUzytkownikow; i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
            uzytkownicy[i].haslo = noweHaslo;
    }

    wyczyscPlikTekstowyZUzytkownikami ();
    zapiszUzytkownikowWPliku (uzytkownicy);
    cout << endl << "Has�o zmienione." << endl;
    Sleep(1000);
}

int uruchomObslugeUzytkownikow (vector <DaneUzytkownika> &uzytkownicy)
{
    char wybranyZnak;

    do
    {
        wyswietlMenuStartowe ();
        cin.clear();
        cin.sync();
        wybranyZnak = getch();

        switch (wybranyZnak)
        {
        case '1':
            return zalogujUzytkownika (uzytkownicy);
            break;
        case '2':
            zarejestrujUzytkownika (uzytkownicy);
            break;
        case '3':
            cout << "Do nast�pnego razu!" << endl;
            Sleep(1000);
            exit (0);
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1000);
        }
    }
    while (wybranyZnak !=3);
}

int uruchomKsiazkeAdresowa (vector <DaneUzytkownika> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    vector <DaneAdresata> adresaci;
    int liczbaAdresatow = 0, idOstatniegoAdresataWKsiazce = 0;
    char wybranyZnak;

    liczbaAdresatow = wczytajAdresatowZPliku (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika);
    idOstatniegoAdresataWKsiazce = sprawdzIdOstatniegoAdresata();

    do
    {
        wyswietlHeaderMenu();
        cout << "Witaj, " << uzytkownicy[idZalogowanegoUzytkownika-1].nazwa << ". Wybierz opcj�:" << endl << endl;
        wyswietlMenuZAdresatami ();

        cin.clear();
        cin.sync();
        wybranyZnak = getch();

        switch (wybranyZnak)
        {
        case '1':
            liczbaAdresatow = dodajAdresataDoKsiazki (adresaci, liczbaAdresatow, idZalogowanegoUzytkownika, idOstatniegoAdresataWKsiazce);
            idOstatniegoAdresataWKsiazce ++;
            break;
        case '2':
            wyszukajImie (adresaci, liczbaAdresatow);
            break;
        case '3':
            wyszukajNazwisko (adresaci, liczbaAdresatow);
            break;
        case '4':
            wyswietlWszystkichAdresatow (adresaci, liczbaAdresatow);
            break;
        case '5':
            liczbaAdresatow = modyfikujDaneAdresata (adresaci, liczbaAdresatow, wybranyZnak, idZalogowanegoUzytkownika); // remove address
            idOstatniegoAdresataWKsiazce = sprawdzIdOstatniegoAdresata();
            break;
        case '6':
            liczbaAdresatow = modyfikujDaneAdresata (adresaci, liczbaAdresatow, wybranyZnak, idZalogowanegoUzytkownika); // edit address
            break;
        case '7':
            zmienHasloZalogowanegoUzytkownika (uzytkownicy, idZalogowanegoUzytkownika);
            break;
        case '8':
            adresaci.clear();
            cout << " * Wylogowano! *" << endl;
            Sleep(1000);
            return 0;
        default:
            cout << "Nie ma takiej opcji w menu!";
            Sleep(1000);
        }
    }
    while (wybranyZnak != 8);
}

int main ()
{
    vector <DaneUzytkownika> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    wczytajUzytkownikowZPliku (uzytkownicy);

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
            idZalogowanegoUzytkownika = uruchomObslugeUzytkownikow (uzytkownicy);
        else
            idZalogowanegoUzytkownika = uruchomKsiazkeAdresowa (uzytkownicy, idZalogowanegoUzytkownika);
    }

    return 0;
}
