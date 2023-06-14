#pragma once
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class GrafMacierz {

    public:
        void nowyGraf(int wierzcholki);
        void nieskierowanyWypisz();
        void skierowanyWypisz();
        void nowaKrawedz(int wierzcholek1, int wierzcholek2, int waga);
        void kasujGraf();
        void algorytmPrima();
        void algorytmKruskala();
        void algorytmDijkstry(int poczatek);
        void algorytmBellmanaForda(int poczatek);

    private:
        int wierzcholki;
        vector<vector<int>> macierz_nieskierowany;
        vector<vector<int>> macierz_skierowany;
};