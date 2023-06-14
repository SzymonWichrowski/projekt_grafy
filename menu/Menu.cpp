#include <iostream>
#include <fstream>
#include <sstream>
#include "Menu.h"

using namespace std;

void Menu::menu() {

    cout << "-----------" << endl;
    cout << "MENU GLOWNE" << endl;
    cout << "-----------" << endl;
    cout << "Do wyboru sa ponizsze operacje." << endl;
    cout << "1) Wczytanie grafu z pliku tekstowego" << endl;
    cout << "2) Wyswietlenie grafu listowo i macierzowo" << endl;
    cout << "3) Algorytm Prima" << endl;
    cout << "4) Algorytm Kruskala" << endl;
    cout << "5) Algorytm Dijkstry" << endl;
    cout << "6) Algorytm Bellmana-Forda" << endl;
    cout << "7) Pomiar czasu" << endl;
    cout << "8) Zakoncz program" << endl;
    cout << endl;

    int wybor;
    cout << "Wybierz numer operacji, ktora chcesz wykonac." << endl;
    cout << "Nr operacji: ";
    if(!(cin >> wybor)) blad();
    jakiWybor(wybor);
}

void Menu::jakiWybor(int wybor) {

    switch(wybor) {
        case 1:
            wczytajGraf(jakiPlik());
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 2:
            cout << "---------------------------------------------" << endl;
            cout << "Graf przedstawiony za pomoca list sasiedztwa" <<  endl;
            cout << "---------------------------------------------" << endl;
            cout << "Nieskierowany: " << endl;
            grafLista.nieskierowanyWypisz();
            cout << "Skierowany: " << endl;
            grafLista.skierowanyWypisz();
            cout << "------------------------------------------------" << endl;
            cout << "Graf przedstawiony za pomoca macierzy sasiedztwa" <<  endl;
            cout << "------------------------------------------------" << endl;
            cout << "Nieskierowany: " << endl;
            grafMacierz.nieskierowanyWypisz();
            cout << "Skierowany: " << endl;
            grafMacierz.skierowanyWypisz();
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 3:
            cout << "--------------------------------------------" << endl;
            cout << "Algorytm Prima przy uzyciu list sasiedztwa" <<  endl;
            cout << "--------------------------------------------" << endl;
            grafLista.algorytmPrima();
            cout << "----------------------------------------------" << endl;
            cout << "Algorytm Prima przy uzyciu macierzy sasiedztwa" <<  endl;
            cout << "----------------------------------------------" << endl;
            grafMacierz.algorytmPrima();
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 4:
            cout << "----------------------------------------------" << endl;
            cout << "Algorytm Kruskala przy uzyciu list sasiedztwa" <<  endl;
            cout << "----------------------------------------------" << endl;
            grafLista.algorytmKruskala();
            cout << "-------------------------------------------------" << endl;
            cout << "Algorytm Kruskala przy uzyciu macierzy sasiedztwa" <<  endl;
            cout << "-------------------------------------------------" << endl;
            grafMacierz.algorytmKruskala();
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 5:
            cout << "----------------------------------------------" << endl;
            cout << "Algorytm Dijkstry przy uzyciu list sasiedztwa" <<  endl;
            cout << "----------------------------------------------" << endl;
            grafLista.algorytmDijkstry(startowy);
            cout << "--------------------------------------------------" << endl;
            cout << "Algorytm Dijkstry przy uzyciu macierzy sasiedztwa" <<  endl;
            cout << "--------------------------------------------------" << endl;
            grafMacierz.algorytmDijkstry(startowy);
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 6:
            cout << "----------------------------------------------------" << endl;
            cout << "Algorytm Bellmana-Forda przy uzyciu list sasiedztwa" <<  endl;
            cout << "----------------------------------------------------" << endl;
            grafLista.algorytmBellmanaForda(startowy);
            cout << "-------------------------------------------------------" << endl;
            cout << "Algorytm Bellmana-Forda przy uzyciu macierzy sasiedztwa" <<  endl;
            cout << "-------------------------------------------------------" << endl;
            grafMacierz.algorytmBellmanaForda(startowy);
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 7:
            cout << "-------------" << endl;
            cout << "Pomiar czasu" <<  endl;
            cout << "-------------" << endl;
            pomiary();
            cout << endl;
            cout << "Wybierz numer operacji, ktora chcesz teraz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
        case 8:
            koniec();
            exit(0);
        default:
            cout << "Nie ma takiej operacji! Sprobuj ponownie." << endl;
            cout << "Wybierz numer operacji, ktora chcesz wykonac." << endl;
            cout << "Nr operacji: ";
            if(!(cin >> wybor)) blad();
            jakiWybor(wybor);
            break;
    }
}

void Menu::wczytajGraf(string nazwa_pliku) {

    fstream plik;
    plik.open(nazwa_pliku, ios::in);
    if (!plik.good()) {
        cout << "Nie znaleziono takiego pliku!" << endl;
    }
    else {
        if (plik.is_open()) {
            string s;
            getline(plik, s);
            if (plik.fail() || s.empty()) {
                cout << "Nastapil blad przy odczycie danych z pliku!";
                plik.close();
            }
            else {
                int tab[4];
                istringstream in_ss(s);
                for (int i = 0; i < 4; i++) {
                    in_ss >> tab[i];
                    if (in_ss.fail()) {
                        cout << "Nastapil blad przy odczycie danych z pliku!";
                        plik.close();
                        return;
                    }
                }
                krawedzie = tab[0];
                wierzcholki = tab[1];
                startowy = tab[2];
                koncowy = tab[3];

                grafLista.nowyGraf(wierzcholki);
                grafMacierz.nowyGraf(wierzcholki);

                for (int i = 0; i < krawedzie; i++) {
                    getline(plik, s) ;
                    if (plik.fail() || s.empty()) {
                        cout << "Nastapil blad przy odczycie danych z pliku!";
                        plik.close();
                        return;
                    }
                    else {
                        istringstream in_ss2(s);
                        for (int j = 0; j < 3; j++){
                            in_ss2 >> tab[j];
                            if (in_ss2.fail()) {
                                cout << "Nastapil blad przy odczycie danych z pliku!";
                                plik.close();
                                return;
                            }
                        }
                        int zrodlowy = tab[0];
                        int docelowy = tab[1];
                        int waga = tab[2];

                        grafLista.nowaKrawedz(zrodlowy, docelowy, waga);
                        grafMacierz.nowaKrawedz(zrodlowy, docelowy, waga);
                    }
                }
                cout << "Wczytano graf!" << endl;
            }
        }
        else {
            cout << "Nastapil blad przy otwarciu pliku!" << endl;
        }
    }

}

string Menu::jakiPlik() {
    string nazwa_pliku;
    cout << endl;
    cout << "Wpisz nazwe pliku (wraz z rozszerzeniem!), z ktorego program ma wczytac graf." << endl;
    cout << "Nazwa pliku: ";
    if(!(cin >> nazwa_pliku)) blad();
    return nazwa_pliku;
}

void Menu::blad() {
    koniec();
    cerr << "UWAGA! NASTAPIL BLAD!!! Uruchom program ponownie." << endl;
    exit(0);
}

void Menu::koniec() {
    grafLista.kasujGraf();
    grafMacierz.kasujGraf();
}

void Menu::pomiary() {

    PomiarCzasu pomiarCzasu;
    //metoda klasy pomiarCzasu, ktora chcesz przetestowac
    cout << "Koniec pomiarow";
}