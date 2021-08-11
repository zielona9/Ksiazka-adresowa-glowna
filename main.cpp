#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
struct Uzytkownicy
{
    int id;
    string login, haslo;
};
string pobieranie_pojedynczego_slowa_z_pliku(int &poczatek, string linijka)
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
            uzytkownik.id=atoi(pobieranie_pojedynczego_slowa_z_pliku(poczatek,linia).c_str());
            uzytkownik.login=pobieranie_pojedynczego_slowa_z_pliku(poczatek,linia);
            uzytkownik.haslo=pobieranie_pojedynczego_slowa_z_pliku(poczatek,linia);
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
            break;
        }
        case 2:
            break;
        case 3:
            exit(0);
            break;
        }
    }

    return 0;
}
