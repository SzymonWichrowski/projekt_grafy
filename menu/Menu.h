#pragma once            //dyrektywa, dzieki ktorej nie nastepuje redefiniowanie klas

#include "../grafy/GrafLista.h"
#include "../grafy/GrafMacierz.h"
#include "../narzedzia/PomiarCzasu.h"

class Menu {

    public:
        void menu();            //wyswietla menu glowne programu
        void wczytajGraf(string nazwa_pliku);

        int krawedzie;
        int wierzcholki;
        int startowy;
        int koncowy;            //wierzcholek koncowy nie bedzie stosowany w zadnym z zaimplementowanych algorytmow


        GrafLista grafLista;
        GrafMacierz grafMacierz;

    private:
        void jakiWybor(int wybor);           //ta funkcja obsluguje wybor uzytkownika
        void blad();            //funkcja wywolywana w przypadku powaznych bledow
        void koniec();          //funkcja wywolywana przed zakonczeniem programu
        void pomiary();
        string jakiPlik();
};
