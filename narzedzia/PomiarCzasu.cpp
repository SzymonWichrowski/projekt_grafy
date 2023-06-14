#include <ntdef.h>
#include <profileapi.h>
#include <random>
#include <fstream>
#include <iomanip>
#include "PomiarCzasu.h"

using namespace std;

long long PomiarCzasu::read_QPC() {

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

void PomiarCzasu::primaLista() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafLista.algorytmPrima();
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafLista.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::kruskalaLista() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafLista.algorytmKruskala();
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafLista.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::dijkstryLista() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafLista.algorytmDijkstry(menu.startowy);
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafLista.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::bellmanafordaLista() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafLista.algorytmBellmanaForda(menu.startowy);
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafLista.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::primaMacierz() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafMacierz.algorytmPrima();
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafMacierz.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::kruskalaMacierz() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafMacierz.algorytmKruskala();
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafMacierz.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::dijkstryMacierz() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafMacierz.algorytmDijkstry(menu.startowy);
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafMacierz.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::bellmanafordaMacierz() {

    //inicjalizacja pomiaru
    //pomiar sklada sie ze 100 wywolan!
    int liczba_wywolan = 100;
    long long int czestotliwosc, start, stop, czas, czas_finalnie = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&czestotliwosc);
    //petla glowna pomiaru
    for (int i = 0; i < liczba_wywolan; i++) {
        czas = 0;
        Menu menu;
        grafTestowy();
        menu.wczytajGraf(plik_pomiary);
        start = read_QPC();
        //algorytm ktorego czas mierzymy
        menu.grafMacierz.algorytmBellmanaForda(menu.startowy);
        stop = read_QPC() - start;
        czas = czas + stop;                         //czas bedziemy zerowac
        czas_finalnie = czas_finalnie + czas;       //czas_finalnie nie bedziemy zzerowac
        menu.grafMacierz.kasujGraf();
    }
    double srednia = (1000000.0 * czas_finalnie) / (czestotliwosc * liczba_wywolan);
    cout << endl;
    cout << "usredniony pomiar czasu (w [us]): " << setprecision(3) << srednia << endl;
}

void PomiarCzasu::grafTestowy() {

    //inicjalizacja
    int wierzcholki = 100;
    double gestosc = 0.25;
    ofstream plik(plik_pomiary);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distPoczatkowy(0, wierzcholki - 1);
    uniform_int_distribution<> distDocelowy(0, wierzcholki - 1);
    uniform_int_distribution<> distWaga(0, wierzcholki - 1);
    int poczatkowy, docelowy, krawedzie, krawedzie_max;
    poczatkowy = distPoczatkowy(gen);
    docelowy = distDocelowy(gen);
    krawedzie = floor(gestosc * (wierzcholki * (wierzcholki - 1)) / 2);
    krawedzie_max = floor((wierzcholki * (wierzcholki - 1) ) / 2);

    //warunek poprawnej inicjalizacji
    if (krawedzie > krawedzie_max) {
        cout << "Wylosowano za duza liczbe krawedzi!!! Sprobuj ponownie." << endl;
        plik.close();
        return;
    }

    //jesli warunek zostanie spelniony
    uniform_int_distribution<> distWierzcholek(0, wierzcholki - 1);
    //pierwsza linia w pliku
    plik << krawedzie << " " << wierzcholki << " " << poczatkowy << " " << docelowy << endl;
    //reszta pliku
    int aktualne_krawedzie = 0;
    int zrodlo, docel, waga;
    while (aktualne_krawedzie < krawedzie) {
        zrodlo = distWierzcholek(gen);
        docel = distWierzcholek(gen);
        waga = distWaga(gen);
        //warunek wstawienia krawedzi
        if (zrodlo != docel) {
            plik << zrodlo << " " << docel << " " << waga << endl;
            aktualne_krawedzie++;
        }
    }
    plik.close();
}

