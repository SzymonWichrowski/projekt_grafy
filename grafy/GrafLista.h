#pragma once            //dyrektywa, dzieki ktorej nie nastepuje redefiniowanie klas
#include <vector>
#include <list>
#include <iostream>

using namespace std;

struct zrodlowy {         //struktura potrzebna do implementacji list sasiadow

    int docelowy;
    int waga;

    zrodlowy(int docelowy, int waga) {
        this-> docelowy = docelowy;
        this-> waga = waga;
    }
};

class GrafLista {

    public:
        void nowyGraf(int wierzcholki);             //inicjalizujemy graf o podanej liczbie wierzcholkow w postaci listy

        void nieskierowanyWypisz();             //wyswietlamy listy sasiadow dla grafu nieskierowanego
        void skierowanyWypisz();                //wyswietlamy listy sasiadow dla grafu skierowanego

        void nowaKrawedz(int wierzcholek1, int wierzcholek2, int waga);           //dodajemy nowa krawedz
        void kasujGraf();

        void algorytmPrima();                               //wykonuje algorytm Prima grafu w postaci listy
        void algorytmKruskala();                            //wykonuje algorytm Kruskala grafu w postaci listy
        void algorytmDijkstry(int poczatek);                //wykonuje algorytm Dijkstry grafu w postaci listy
        void algorytmBellmanaForda(int poczatek);           //wykonuje algorytm Bellmana-Forda grafu w postaci listy

        private:
            int wierzcholki;

            list<zrodlowy>* lista_nieskierowany;            //wskazniki na listy struktur
            list<zrodlowy>* lista_skierowany;
};
