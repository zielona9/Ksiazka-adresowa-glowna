#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <algorithm>
using namespace std;
struct Uzytkownicy
{
    int id;
    string login, haslo;
};
struct rekord
{
    int id_adresata,id_uzytkownika;
    string imie, nazwisko, adres, email, nr_tel;
    void print() const
    {
        cout<<id_adresata<< " " << right << setw( 5 )<<id_uzytkownika<< " " << right << setw( 10 )<<imie<< " " << right << setw(20);
        cout<<nazwisko<< " " << right << setw( 20 );
        cout<<nr_tel<< " " << right << setw( 25 );
        cout<<email<<" " << right << setw( 25 );
        cout<<adres<< endl;
    }

};
string pobieranie_pojedynczego_slowa_z_linii(int &poczatek, string linijka)
{
    string slowo;
    int i=poczatek;
    while(linijka[i]!='|')
    {
        slowo.push_back(linijka[i]);
        i++;
    }
    poczatek=i+1;
    return slowo;
}
void pobieranie_danych_z_pliku_uzytkownicy(vector <Uzytkownicy> &osoba)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::in);
    Uzytkownicy uzytkownik;
    if(plik.good()== false)
    {
        cout<<"Nie ma pliku o takiej nazwie"<<endl;
        return;
    }
    else
    {
        string linia;
        while(getline(plik,linia))
        {
            int poczatek=0;
            uzytkownik.id=atoi(pobieranie_pojedynczego_slowa_z_linii(poczatek,linia).c_str());
            uzytkownik.login=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            uzytkownik.haslo=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            osoba.push_back(uzytkownik);
        }
    }
    plik.close();
}
int pobieranie_opcji_od_uzytkownika(int opcja_poczatek, int opcja_koniec)
{
    int wybrana_opcja;
    while(!(cin>>wybrana_opcja) || wybrana_opcja<opcja_poczatek || wybrana_opcja>opcja_koniec)
    {
        cout<<"Nie wybrano zadnej z opcji."<<endl;
        cout<<"Wybierz opcje jeszcze raz"<<endl;
        cin.clear();
        cin.sync();
    }
    cin.sync();
    return wybrana_opcja;
}
int menu_logowania()
{
    int opcja;
    cout<<"Menu logowania:"<<endl;
    cout<<"1. Logowanie"<<endl;
    cout<<"2. Rejestracja"<<endl;
    cout<<"3. Zamknij program"<<endl;
    cout<<"Podaj, ktora opcje wybierasz"<<endl;
    opcja=pobieranie_opcji_od_uzytkownika(1,3);
    return opcja;
}
int sprawdzanie_czy_istnieje_taki_login (vector <Uzytkownicy> osoba, string login)
{
    for(int i=0; i< osoba.size(); i++)
    {
        if(osoba[i].login==login)
            return i;
    }
    return -1;
}
int logowanie(vector <Uzytkownicy> osoba)
{
    string login;
    cout<<"Podaj login"<<endl;
    getline(cin,login);
    int itr;
    itr=sprawdzanie_czy_istnieje_taki_login(osoba,login);
    if(itr==-1)
    {
        cout<<"Nie ma takiego uzytkownika"<<endl;
        system("pause");
        return itr;
    }
    else
    {
        string haslo;
        cout<<"Podaj haslo"<<endl;
        getline(cin, haslo);
        int licz=0;
        while(haslo!=osoba[itr].haslo && licz<2)
        {
            cout<<"Podano bledne haslo"<<endl;
            cin.sync();
            cin.clear();
            licz++;
            cout<<"Podaj haslo jeszcze raz. Masz jeszcze "<<3-licz<<"szans."<<endl;
            getline(cin,haslo);

        }
        if(licz>=2 && haslo!=osoba[itr].haslo)
        {
            cout<<"Podales 3-krotnie bledne haslo."<<endl;
            itr =-1;
        }

        return itr;
    }

}
void zapisywanie_nowego_uzytkownika_plik( Uzytkownicy uzytkownik)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::app|ios::binary|ios::ate);
    if(plik.tellg()!=0)
        plik<<endl;
    plik<< uzytkownik.id<<"|"<<uzytkownik.login<<"|"<<uzytkownik.haslo<<"|";
    plik.close();
}
int rejestracja( vector <Uzytkownicy> &uzytkownik)
{
    string login, haslo1, haslo2;
    int itr;
    do
    {
        cout<<"Podaj login"<<endl;
        getline(cin,login);
        itr=sprawdzanie_czy_istnieje_taki_login(uzytkownik,login);
        if(itr!=-1)
            cout<<"Podany login juz jest w rejestrze. Podaj inny"<<endl;
    }
    while(itr!=-1);
    do
    {
        cout<<"Podaj haslo" <<endl;
        getline(cin, haslo1);
        system("cls");
        cout<<"Podaj ponownie haslo" <<endl;
        getline(cin, haslo2);
        if(haslo1!=haslo2)
        {
            cout<<"Podane hasla sa rozne"<<endl;
            cout<<"Wprowadz hasla jeszcze raz."<<endl;
        }
    }
    while(haslo1!=haslo2);
    Uzytkownicy nowy_uzytkownik;
    nowy_uzytkownik.login=login;
    nowy_uzytkownik.haslo=haslo1;
    nowy_uzytkownik.id=uzytkownik[uzytkownik.size()-1].id+1;
    uzytkownik.push_back(nowy_uzytkownik);
    zapisywanie_nowego_uzytkownika_plik(nowy_uzytkownik);
    itr=uzytkownik.size()-1;
    return itr;
}
int wyswietlanie_menu_glownego()
{
    int opcja;
    cout<<"KSIAZKA ADRESOWA"<<endl;
    cout<<"1. Dodaj adresata"<<endl;
    cout<<"2. Wyszukaj po imieniu"<<endl;
    cout<<"3. Wyszukaj po nazwisku"<<endl;
    cout<<"4. Wyswietl wszystkich adresatow"<<endl;
    cout<<"5. Usun adresata"<<endl;
    cout<<"6. Edytuj adresata"<<endl;
    cout<<"9. Wyloguj się"<<endl;
    cout<<"Twoj wybor:"<<endl;
    opcja=pobieranie_opcji_od_uzytkownika(1,9);
    return opcja;
}

int pobieranie_danych_z_pliku(fstream &plik,vector <rekord> &osoba)
{
    int ile=0;
    rekord persona;
    if(plik.good()== false)
        return ile;
    else
    {
        string linia;
        while(getline(plik,linia))
        {
            int poczatek=0;
            persona.id_adresata=atoi(pobieranie_pojedynczego_slowa_z_linii(poczatek,linia).c_str());
            persona.id_uzytkownika=atoi(pobieranie_pojedynczego_slowa_z_linii(poczatek,linia).c_str());
            persona.imie=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            persona.nazwisko=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            persona.nr_tel=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            persona.email=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            persona.adres=pobieranie_pojedynczego_slowa_z_linii(poczatek,linia);
            osoba.push_back(persona);
            ile++;
        }
        return ile;
    }
}
void wypisywanie_danych_na_ekran(vector <rekord> osoba,int id, int nr_linii_do_wyswietlenia)
{
    if(nr_linii_do_wyswietlenia==0)
    {
        cout<< "id adresata" << right << setw( 6 )<<"id uzytkownika" << right << setw( 10 )<<"imie"<< " " << right << setw( 20 );
        cout<< "nazwisko"<< " " << right << setw( 20 );
        cout<<"numer telefonu" << " " << right << setw( 25 );
        cout<< "adres e-mail"<< " " << right << setw( 25 );
        cout<< "adres"<<endl;
    }
    osoba[id].print();
}
void wypisywanie_wszystkich_rekordow_na_ekran(vector <rekord> osoba)
{
    system("cls");
    for(int i=0; i<osoba.size(); i++)
    {
        wypisywanie_danych_na_ekran(osoba,i,i);
    }
    system("pause");
}
bool sprawdzenie_poprawnosci_wprowadzenia_tekstu(string tekst)
{
    for(int i=0; i<tekst.length(); i++)
    {
        if(!isalpha(tekst[i]) && tekst[i]!=' ' && tekst[i]!='.' && tekst[i]!='-')
            return false;
    }
    return true;
}
string pobieranie_imienia_od_uzytkownika()
{
    string imie;
    cout<<"Podaj imie: ";
    getline(cin,imie);
    while(!(sprawdzenie_poprawnosci_wprowadzenia_tekstu(imie)))
    {
        cout<<"Podano bledne imie."<<endl;
        cout<<"Podaj imie jeszcze raz."<<endl;
        cin.clear();
        cin.sync();
        getline(cin,imie);
    }
    return imie;
}
string pobieranie_nazwiska_od_uzytkownika()
{
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    getline(cin,nazwisko);
    while(!(sprawdzenie_poprawnosci_wprowadzenia_tekstu(nazwisko)))
    {
        cout<<"Podano bledne nazwisko."<<endl;
        cout<<"Podaj nazwisko jeszcze raz."<<endl;
        cin.clear();
        cin.sync();
        getline(cin,nazwisko);
    }
    return nazwisko;
}
string pobieranie_tel_od_uzytkownika()
{
    string nr_tel;
    cout<<"Podaj numer telefonu: ";
    int czy_powtorzyc=0;
    do
    {
        czy_powtorzyc=0;
        getline(cin,nr_tel);
        for(int i=0; i<nr_tel.size(); i++)
        {
            if(!isdigit(nr_tel[i]) && nr_tel[i]!=' ')
            {
                czy_powtorzyc=1;
                cout<<"Podano bledny numer telefonu."<<endl;
                cout<<"Podaj numer telefonu jeszcze raz."<<endl;
                nr_tel="";
                cin.clear();
                cin.sync();
                break;
            }

        }
    }
    while (czy_powtorzyc==1);

    return nr_tel;
}
string pobieranie_adresu_od_uzytkownika()
{
    string adres;
    cout<<"Podaj adres: ";
    getline(cin,adres);
    return adres;
}
string pobieranie_email_od_uzytkownika()
{
    string email;
    cout<<"Podaj adres e-mail: ";
    getline (cin, email);
    return email;
}
int sprawdzenie_czy_istnieje_podane_id(vector <rekord> osoba,int szukane_id)
{
    for(int i=0; i<osoba.size(); i++)
    {
        if(osoba[i].id_adresata==szukane_id)
        {
            return i;
        }
    }
    return -1;
}
bool podjecie_decyzji_przez_uzytkownika_o_ponownym_powtorzeniu_danych()
{
    char pobrany_znak;
    cout<<"Czy chcesz podac dane jeszcze raz?[T/N]"<<endl;
    cin.clear();
    cin.sync();
    pobrany_znak=getchar();

    if(pobrany_znak=='T' || pobrany_znak=='t')
        return true;
    else
        return false;
}
void zapisywanie_rekordu_do_pliku( rekord persona)
{
    fstream zapis;
    zapis.open("Ksiazka_adresowa.txt",ios::app|ios::binary|ios::ate);
    if(zapis.tellg()!=0)
        zapis<<endl;
    zapis<<persona.id_adresata<<"|"<<persona.id_uzytkownika<<"|"<<persona.imie<<"|"<<persona.nazwisko<<"|"<<persona.nr_tel<<"|"<<persona.email<<"|"<<persona.adres<<"|";
    zapis.close();
}
bool pobranie_decyzji_o_braku_aktualizacji_od_uzytkownika(string pobrany_tekst, string poprzedni_tekst)
{

    bool akceptacja;
    if(pobrany_tekst==poprzedni_tekst)
    {
        cout<<"Podane dane nie zostaly zmienione"<<endl;
        akceptacja=podjecie_decyzji_przez_uzytkownika_o_ponownym_powtorzeniu_danych();
    }
    else
        akceptacja=false;
    return akceptacja;
}
void wyswietl_menu_atualizacja_danych()
{
    system("cls");
    cout<<"1. Imie"<<endl;
    cout<<"2. Nazwisko"<<endl;
    cout<<"3. Numer telefonu"<<endl;
    cout<<"4. Email"<<endl;
    cout<<"5. Adres"<<endl;
    cout<<"6. Powrot do menu"<<endl;
    cout<<"Ktore dane nalezy zaktualizowac"<<endl;
}
string pobranie_wczesniejszego_tekstu(vector <rekord> osoba,int nr_linii, int typ_danej)
{
    string tekst_poprzedni;
    switch(typ_danej)
    {
    case 1:
        tekst_poprzedni=osoba[nr_linii].imie;
        break;
    case 2:
        tekst_poprzedni= osoba[nr_linii].nazwisko;
        break;
    case 3:
        tekst_poprzedni=osoba[nr_linii].nr_tel;
        break;
    case 4:
        tekst_poprzedni=osoba[nr_linii].email;
        break;
    case 5:
        tekst_poprzedni=osoba[nr_linii].adres;
        break;
    }
    return tekst_poprzedni;
}
string ponowne_pobranie_danej(int typ_danej)
{
    string tekst;
     cin.clear();
            cin.sync();
         switch(typ_danej)
    {
    case 1:
        tekst=pobieranie_imienia_od_uzytkownika();
        break;
    case 2:
        tekst=pobieranie_nazwiska_od_uzytkownika();
        break;
    case 3:
        tekst=pobieranie_tel_od_uzytkownika();
        break;
    case 4:
        tekst=pobieranie_email_od_uzytkownika();
        break;
    case 5:
        tekst=pobieranie_adresu_od_uzytkownika();
        break;
    }
    return tekst;
}
void ostateczna_edycja_danej(vector <rekord> &osoba, string tekst,int nr_linii, int typ_danej)
{
     switch(typ_danej)
        {
        case 1:
            osoba[nr_linii].imie=tekst;
            break;
        case 2:
            osoba[nr_linii].nazwisko=tekst;
            break;
        case 3:
            osoba[nr_linii].nr_tel=tekst;
            break;
        case 4:
            osoba[nr_linii].email=tekst;
            break;
        case 5:
            osoba[nr_linii].adres=tekst;
            break;
        }
}
void aktualizacja_danej_zmiennej(vector <rekord> &osoba, int nr_id,int nr_linii, int typ_danej, string tekst)
{
    string tekst_poprzedni=pobranie_wczesniejszego_tekstu(osoba,nr_linii,typ_danej);
    if(pobranie_decyzji_o_braku_aktualizacji_od_uzytkownika(tekst,osoba[nr_linii].imie)==true)
        {
           tekst=ponowne_pobranie_danej(typ_danej);
        aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,typ_danej,tekst);
        }

    else
    {
       ostateczna_edycja_danej(osoba,tekst,nr_linii,typ_danej);
        remove("Ksiazka_adresowa.txt");
        for(int i=0; i<osoba.size(); i++)
        {
            zapisywanie_rekordu_do_pliku(osoba[i]);
        }
    }

}
void aktualizacja_danych(int nr_id, vector <rekord> &osoba, int nr_linii)
{
    int wybor;
    do
    {
        wyswietl_menu_atualizacja_danych();
        wybor=pobieranie_opcji_od_uzytkownika(1,6);
        switch(wybor)
        {
        case 1:
        {
            string imie;
            imie=pobieranie_imienia_od_uzytkownika();
            aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,1,imie);
            break;
        }

        case 2:
        {
            string nazwisko;
            nazwisko=pobieranie_nazwiska_od_uzytkownika();
            aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,2,nazwisko);
            break;
        }
        case 3:
        {
            string nr_tel;
            nr_tel=pobieranie_tel_od_uzytkownika();
            aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,3,nr_tel);
            break;
        }
        case 4:
        {
            string email;
            email=pobieranie_email_od_uzytkownika();
            aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,4,email);
            break;
        }
        case 5:
        {
            string adres;
            adres=pobieranie_adresu_od_uzytkownika();
            aktualizacja_danej_zmiennej(osoba,nr_id,nr_linii,5,adres);
            break;
        }
        case 6:
            break;
        }
    }
    while(wybor!=6);
    cout<<"Dane po aktualizacji wygladaja nastepujaco"<<endl;
    wypisywanie_danych_na_ekran(osoba,nr_linii,0);
    system("pause");
}
int wyswietlanie_menu_przy_powtarzaniu_danych()
{
    cout<<"Wybierz opcje"<<endl;
    cout<<"1. Zapisz nowa osobe o tych samych danych osobowych "<<endl;
    cout<<"2. Podaj dane jeszcze raz "<<endl;
    cout<<"3. Powrot do menu glownego"<<endl;
    int wybor;
    wybor=pobieranie_opcji_od_uzytkownika(1,3);
    return wybor;
}
int szukanie_id_po_imieniu_nazwisku(vector <rekord> osoba, string imie, string nazwisko)
{
    int i=0;
    while(i<osoba.size())
    {
        if(osoba[i].imie==imie && osoba[i].nazwisko==nazwisko)
        {
            cout<<"Osoba o podanym imieniu i nazwisku jest juz zapisana w ksiazce adresowej."<<endl;
            return i;
        }
        i++;
    }
    return -1;
}
int szukanie_id_po_nr_telefonu(vector <rekord> osoba, string nr_tel)
{
    int i=0;
    while(i<osoba.size())
    {
        if(osoba[i].nr_tel==nr_tel)
        {
            cout<<"Osoba o podanym numerze telefonu jest juz zapisana w ksiazce adresowej."<<endl;
            return i;

        }
        i++;
    }
    return -1;
}
int szukanie_id_po_email(vector <rekord> osoba, string email)
{
    int i=0;
    while(i<osoba.size())
    {
        if(osoba[i].email==email)
        {
            cout<<"Osoba o podanym adresie email jest juz zapisana w ksiazce adresowej."<<endl;
            return i;
        }
        i++;
    }
    return -1;
}
int najwieksze_id(vector <rekord> osoba)
{
    int maksimum=0;
    for(int i=0;i<osoba.size();i++)
    {
        if(maksimum<osoba[i].id_adresata)
            maksimum=osoba[i].id_adresata;
    }
    return maksimum;
}
void dodawanie_nowego_rekordu_wektor( rekord &persona, vector <rekord> &osoba)
{
    fstream zapis;
    zapis.open("Ksiazka_adresowa.txt",ios::app);
    persona.id_adresata=najwieksze_id(osoba)+1;
    osoba.push_back(persona);
    cout<<"Nowe dane wygladaja nastepujaco"<<endl;
    wypisywanie_danych_na_ekran(osoba,osoba.size()-1,0);
    system("pause");
    zapis.close();
}
int sprawdzenie_powtorzenia_danych_przy_ich_pobieraniu(vector <rekord> osoba, int id_powtorzone, rekord &persona)
{
    int id=-1;
    if(id_powtorzone==-1)
    {
        persona.imie=pobieranie_imienia_od_uzytkownika();
        persona.nazwisko=pobieranie_nazwiska_od_uzytkownika();
        id=szukanie_id_po_imieniu_nazwisku(osoba,persona.imie,persona.nazwisko);
    }
    if(id!=-1 && id!=id_powtorzone)
        return id;
    else
    {
        persona.nr_tel=pobieranie_tel_od_uzytkownika();
        id=szukanie_id_po_nr_telefonu(osoba,persona.nr_tel);
    }
    if(id!=-1 && id!=id_powtorzone)
        return id;
    else
    {
        persona.adres=pobieranie_adresu_od_uzytkownika();
        persona.email=pobieranie_email_od_uzytkownika();
        id=szukanie_id_po_email(osoba,persona.email);
    }
    return id;

}
void dodanie_nowego_adresata(vector <rekord> &osoba)
{
    rekord persona;
    long int nr_tel;
    int id=-1;
    id=sprawdzenie_powtorzenia_danych_przy_ich_pobieraniu(osoba,id, persona);
    if(id==-1)
    {
        dodawanie_nowego_rekordu_wektor(persona,osoba);
        zapisywanie_rekordu_do_pliku(persona);
        return;
    }
    else
    {
        system("cls");
        int numer_wyboru;
        numer_wyboru=wyswietlanie_menu_przy_powtarzaniu_danych();
        if(numer_wyboru==1)
        {
            id=sprawdzenie_powtorzenia_danych_przy_ich_pobieraniu(osoba,id,persona);
            dodawanie_nowego_rekordu_wektor(persona,osoba);
            zapisywanie_rekordu_do_pliku(persona);
        }
        else if(numer_wyboru==2)
            dodanie_nowego_adresata(osoba);
            else if(numer_wyboru==3)
                return;

    }
    system("cls");

}
void aktualizacja_danych_konkretnej_osoby(vector <rekord> &osoba)
{
    int szukane_id;
    cout<<"Kogo dane chcesz edytowac"<<endl;
    cout<<"Podaj id"<<endl;
    cin>>szukane_id;
    int nr_linii_o_szukanym_id;
    nr_linii_o_szukanym_id=sprawdzenie_czy_istnieje_podane_id(osoba,szukane_id);

    if(nr_linii_o_szukanym_id!=-1)
        aktualizacja_danych(szukane_id,osoba,nr_linii_o_szukanym_id);
    else
    {
        cout<<"W rejestrze nie ma osoby o takich danych"<<endl;
        if(podjecie_decyzji_przez_uzytkownika_o_ponownym_powtorzeniu_danych()==true)
            aktualizacja_danych_konkretnej_osoby(osoba);
    }
}
void usuniecie_danych_z_wektora(vector <rekord> &osoba, int nr_linii)
{
    osoba.erase(osoba.begin()+nr_linii);
}
void usuniecie_osoby_z_pliku(int nr_id, vector<rekord> osoba)
{
    remove("Ksiazka_adresowa.txt");
    for(int i=0; i<osoba.size(); i++)
    {
        if(osoba[i].id_adresata!=nr_id)
            zapisywanie_rekordu_do_pliku(osoba[i]);
    }
}
bool czy_uzytkownik_chce_usunac_ta_osobe(int nr_id, vector <rekord> osoba)
{
    cout<<"Czy na pewno chcesz usunac dane tej osoby? [T/N]"<<endl;
    wypisywanie_danych_na_ekran(osoba,nr_id,0);
    char znak;
    cin.clear();
    cin.sync();
    znak=getchar();
    if(znak=='T' || znak=='t')
        return true;
    else
        return false;
}
void usuniecie_osoby_o_zadanym_id(vector <rekord>&osoba)
{
    int szukane_id;
    cout<<"Kogo dane chcesz usunac"<<endl;
    cout<<"Podaj id"<<endl;
    cin>>szukane_id;
    int nr_linii_o_szukanym_id;
    nr_linii_o_szukanym_id=sprawdzenie_czy_istnieje_podane_id(osoba,szukane_id);

    if(nr_linii_o_szukanym_id!=-1)
    {
        if(czy_uzytkownik_chce_usunac_ta_osobe(nr_linii_o_szukanym_id,osoba)==true)
        {
        usuniecie_danych_z_wektora(osoba,nr_linii_o_szukanym_id);
        usuniecie_osoby_z_pliku(szukane_id,osoba);
        }
        else
            cout<<"Danych nie usunieto"<<endl;
            system("pause");
    }
    else
    {
        cout<<"W rejestrze nie ma osoby o takich danych"<<endl;
        if(podjecie_decyzji_przez_uzytkownika_o_ponownym_powtorzeniu_danych()==true)
            usuniecie_osoby_o_zadanym_id(osoba);
               system("pause");
    }
}
void wyszukiwanie_rekordow_po_imieniu(string imie, vector <rekord> osoba)
{
    int liczba_szukanych_rekordow=0;
    for(int i=0; i<osoba.size(); i++)
    {
        if(osoba[i].imie==imie)
        {
            wypisywanie_danych_na_ekran(osoba, i,liczba_szukanych_rekordow);
            liczba_szukanych_rekordow++;
        }
    }
    if(liczba_szukanych_rekordow==0)
        cout<<"W ksiazce adresowej nie ma osoby o takich danych"<<endl;
    system("Pause");
}
void wyszukiwanie_rekordow_po_nazwisku(string nazwisko, vector <rekord> osoba)
{
    int liczba_szukanych_rekordow=0;
    for(int i=0; i<osoba.size(); i++)
    {
        if(osoba[i].nazwisko==nazwisko)
        {
            wypisywanie_danych_na_ekran(osoba,i,liczba_szukanych_rekordow);
            liczba_szukanych_rekordow++;
        }
    }
    if(liczba_szukanych_rekordow==0)
        cout<<"W ksiazce adresowej nie ma osoby o takim nazwisku"<<endl;
    system("pause");
}

void menu_po_logowaniu(vector <rekord> &osoba)
{
        int wybrana_opcja=1;
    while(wybrana_opcja!=9)
    {
        system("cls");
        wybrana_opcja=wyswietlanie_menu_glownego();
        switch(wybrana_opcja)
        {
        case 1:
            dodanie_nowego_adresata(osoba);
            break;
        case 2:
        {
            string imie;
            imie=pobieranie_imienia_od_uzytkownika();
            wyszukiwanie_rekordow_po_imieniu(imie,osoba);
            break;
        }
        case 3:
        {
            string nazwisko;
            nazwisko=pobieranie_nazwiska_od_uzytkownika();
            wyszukiwanie_rekordow_po_nazwisku(nazwisko,osoba);
            break;
        }
        case 4:
            wypisywanie_wszystkich_rekordow_na_ekran(osoba);
            break;
        case 5:
            usuniecie_osoby_o_zadanym_id(osoba);
            break;
        case 6:
            aktualizacja_danych_konkretnej_osoby(osoba);
            break;
        case 9:
            cout<<"Poprawnie Cie wylogowano"<<endl;
            break;
        default:
            cout<<"Nie wybrano zadnej z opcji"<<endl;
            break;
        }
    }
}
int main()
{
    int opcja;

    vector <Uzytkownicy> uzytkownik;
    pobieranie_danych_z_pliku_uzytkownicy(uzytkownik);

    while(1)
    {
        opcja=menu_logowania();
        switch(opcja)
        {
        case 1:
        {
                int itr;
                itr=logowanie(uzytkownik);
                vector <rekord> osoba;
                fstream plik;
                plik.open("Ksiazka_adresowa.txt",ios::in);
                pobieranie_danych_z_pliku(plik,osoba);
                plik.close();
                pobieranie_danych_z_pliku(plik,osoba);
                plik.close();
                menu_po_logowaniu(osoba);
                system("cls");
                break;
            }
        case 2:
        {
            int itr;
            rejestracja(uzytkownik);
             system("cls");
            break;
        }

        case 3:
            exit(0);
            break;
        }
    }

    return 0;
}
