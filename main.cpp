#include <iostream>

using namespace std;
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
void menu_logowania()
{
    cout<<"Menu logowania:"<<endl;
    cout<<"1. Logowanie"<<endl;
    cout<<"2. Rejestracja"<<endl;
    cout<<"3. Zamknij program"<<endl;
    cout<<"Podaj, ktora opcje wybierasz"<<endl;
    pobieranie_opcji_od_uzytkownika(1,3);
}
int main()
{
    menu_logowania();
    return 0;
}
