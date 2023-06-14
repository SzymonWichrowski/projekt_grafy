#pragma once

#include "../menu/Menu.h"

class PomiarCzasu {

    public:

        long long int read_QPC();           //funkcja do pomiaru czasu

        //pomiary dla list sasiedztwa
        void primaLista();
        void kruskalaLista();
        void dijkstryLista();
        void bellmanafordaLista();

        //pomiary dla macierzy sasiedztwa
        void primaMacierz();
        void kruskalaMacierz();
        void dijkstryMacierz();
        void bellmanafordaMacierz();

        //tworzenie grafu do pomiaru
        void grafTestowy();

    private:
        string plik_pomiary = "pomiary.txt";
};