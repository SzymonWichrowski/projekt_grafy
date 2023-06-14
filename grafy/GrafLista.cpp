#include <queue>
#include <algorithm>
#include <limits>
#include "GrafLista.h"
#include "../narzedzia/UnionFind.h"

void GrafLista::nowyGraf(int wierzcholki) {

    //liczba wierzcholkow
    this -> wierzcholki = wierzcholki;

    //lista sasiadow dla grafu nieskierowanego
    lista_nieskierowany = new list<zrodlowy>[wierzcholki];
    //lista sasiadow dla grafu skierowanego
    lista_skierowany = new list<zrodlowy>[wierzcholki];
}

void GrafLista::nieskierowanyWypisz() {

    for (int i = 0; i < wierzcholki; i++) {
        cout << i << " -> ";
        for (const auto& element : lista_nieskierowany[i]) {
            cout << "(" << element.docelowy << ", " << element.waga << "); ";
        }
        cout << endl;
    }
}

void GrafLista::skierowanyWypisz() {

    for (int i = 0; i < wierzcholki; i++) {
        cout << i << " -> ";
        for (const auto& element : lista_skierowany[i]) {
            cout << "(" << element.docelowy << ", " << element.waga << "); ";
        }
        cout << endl;
    }
}

void GrafLista::nowaKrawedz(int wierzcholek1, int wierzcholek2, int waga) {

    zrodlowy krawedz1(wierzcholek1, waga);
    zrodlowy krawedz2(wierzcholek2, waga);

    //dla grafu nieskierowanego wierzcholek1 i wierzcholek2 sa dla siebie wzajemnie sasiadami
    lista_nieskierowany[wierzcholek1].push_back(krawedz2);
    lista_nieskierowany[wierzcholek2].push_back(krawedz1);

    //dla grafu skierowanego wierzcholek2 jest sasiadem wierzchoka1, ale nie odwrotnie!!!
    lista_skierowany[wierzcholek1].push_back(krawedz2);
}

void GrafLista::algorytmPrima() {

    // Sprawdzenie, czy graf zostal zainicjalizowany
    if (wierzcholki == 0 || lista_nieskierowany == nullptr) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Inicjalizacja struktur pomocniczych
    vector<bool> odwiedzone(wierzcholki, false);            // Tablica odwiedzonych wierzcholków
    vector<int> koszty(wierzcholki, INT_MAX);               // Tablica kosztow dojscia do wierzcholków
    vector<int> poprzedniki(wierzcholki, -1);               // Tablica poprzedników dla wierzcholków

    // Wybieramy wierzcholek startowy jako pierwszy wierzchołek
    int startowy = 0;
    koszty[startowy] = 0;

    // Petla glowna algorytmu
    for (int i = 0; i < wierzcholki - 1; i++) {
        // Wybor wierzcholka o najmniejszym koszcie sposrod nieodwiedzonych
        int aktualny = -1;
        int najmniejszyKoszt = INT_MAX;

        for (int v = 0; v < wierzcholki; v++) {
            if (!odwiedzone[v] && koszty[v] < najmniejszyKoszt) {
                aktualny = v;
                najmniejszyKoszt = koszty[v];
            }
        }

        // Oznaczamy biezacy wierzcholek jako odwiedzony
        odwiedzone[aktualny] = true;

        // Aktualizacja kosztow dojscia i poprzednikow dla sasiadujacych wierzcholkow
        for (const auto& krawedz : lista_nieskierowany[aktualny]) {
            int docelowy = krawedz.docelowy;
            int waga = krawedz.waga;

            if (!odwiedzone[docelowy] && waga < koszty[docelowy]) {
                koszty[docelowy] = waga;
                poprzedniki[docelowy] = aktualny;
            }
        }
    }

    // Wyswietlanie wynikow
    int sumaWag = 0;
    cout << "Krawedzie tworzace MST:" << endl;
    for (int i = 1; i < wierzcholki; i++) {
        cout << "(" << poprzedniki[i] << " - " << i << ") waga: " << koszty[i] << endl;
        sumaWag += koszty[i];
    }
    cout << "Suma wag krawedzi MST: " << sumaWag << endl;
}

void GrafLista::algorytmKruskala() {
    // Sprawdzenie, czy graf został zainicjalizowany
    if (wierzcholki == 0) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Struktura pomocnicza do przechowywania krawędzi
    struct Krawedz {
        int u;
        int v;
        int waga;

        Krawedz(int u, int v, int waga) : u(u), v(v), waga(waga) {}
    };

    // Funkcja porównująca krawędzie na podstawie ich wag
    auto porownajKrawedzie = [](const Krawedz& k1, const Krawedz& k2) {
        return k1.waga < k2.waga;
    };

    // Tworzenie wektora zawierającego wszystkie krawędzie grafu
    vector<Krawedz> krawedzie;
    for (int i = 0; i < wierzcholki; i++) {
        for (const auto& krawedz : lista_nieskierowany[i]) {
            krawedzie.push_back(Krawedz(i, krawedz.docelowy, krawedz.waga));
        }
    }

    // Sortowanie krawędzi rosnąco według wag
    sort(krawedzie.begin(), krawedzie.end(), porownajKrawedzie);

    // Inicjalizacja struktur pomocniczych
    UnionFind zbior(wierzcholki);
    vector<Krawedz> mst;
    int sumaWag = 0;
    int liczbaKrawedzi = 0;

    // Pętla główna algorytmu
    for (const auto& krawedz : krawedzie) {
        int u = krawedz.u;
        int v = krawedz.v;

        int zbiorU = zbior.find(u);
        int zbiorV = zbior.find(v);

        if (zbiorU != zbiorV) {
            mst.push_back(krawedz);
            sumaWag += krawedz.waga;
            liczbaKrawedzi++;

            // Scalanie zbiorów
            zbior.merge(zbiorU, zbiorV);
        }

        // Sprawdzenie warunku zakończenia algorytmu
        if (liczbaKrawedzi == wierzcholki - 1) {
            break;
        }
    }

    // Wyświetlanie wyników
    cout << "Krawedzie tworzace MST:" << endl;
    for (const auto& krawedz : mst) {
        cout << "(" << krawedz.u << " - " << krawedz.v << ") waga: " << krawedz.waga << endl;
    }
    cout << "Suma wag krawedzi MST: " << sumaWag << endl;
}


void GrafLista::algorytmDijkstry(int poczatek) {

    // Sprawdzenie, czy graf został zainicjalizowany
    if (wierzcholki == 0 || lista_skierowany == nullptr) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Inicjalizacja tablic odległości i poprzedników
    vector<int> odleglosci(wierzcholki, numeric_limits<int>::max());
    vector<int> poprzednicy(wierzcholki, -1);

    // Ustawienie odległości wierzchołka początkowego na 0
    odleglosci[poczatek] = 0;

    // Kolejka priorytetowa przechowująca pary (odległość, wierzchołek)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> kolejka;

    // Dodanie wierzchołka początkowego do kolejki
    kolejka.push(make_pair(0, poczatek));

    // Główna pętla algorytmu
    while (!kolejka.empty()) {
        // Pobranie wierzchołka o najmniejszej odległości z kolejki
        int aktualnyWierzcholek = kolejka.top().second;
        int aktualnaOdleglosc = kolejka.top().first;
        kolejka.pop();

        // Sprawdzenie, czy aktualny wierzchołek został już odwiedzony
        if (aktualnaOdleglosc > odleglosci[aktualnyWierzcholek]) {
            continue; // Przejdź do kolejnego wierzchołka w kolejce
        }

        // Przejście przez listę sąsiadów aktualnego wierzchołka
        for (const auto& krawedz : lista_skierowany[aktualnyWierzcholek]) {
            int sasiad = krawedz.docelowy;
            int waga = krawedz.waga;

            // Sprawdzenie, czy nowa odległość jest mniejsza od dotychczasowej
            if (odleglosci[aktualnyWierzcholek] + waga < odleglosci[sasiad]) {
                if (waga < 0) {
                    cout << "Waga ujemna znaleziona! Algorytm zostanie przerwany" << endl;
                    return;
                }

                odleglosci[sasiad] = odleglosci[aktualnyWierzcholek] + waga;
                poprzednicy[sasiad] = aktualnyWierzcholek;

                // Dodanie sąsiada do kolejki
                kolejka.push(make_pair(odleglosci[sasiad], sasiad));
            }
        }
    }

    // Wyświetlanie wyników
    cout << "Wierzcholek startowy: " << poczatek << endl;
    cout << "Odleglosci: " << endl;
    for (int i = 0; i < wierzcholki; i++) {
        cout << "Wierzcholek: " << i << ", Odleglosc: " << odleglosci[i] << endl;
    }

    cout << "Sciezki:" << endl;
    for (int i = 0; i < wierzcholki; i++) {
        if (odleglosci[i] == numeric_limits<int>::max()) {
            cout << "Brak sciezki do wierzcholka " << i << endl;
        } else {
            cout << "Sciezka do wierzcholka " << i << ": ";
            vector<int> sciezka;
            int wierzcholek = i;
            while (wierzcholek != -1) {
                sciezka.push_back(wierzcholek);
                wierzcholek = poprzednicy[wierzcholek];
            }
            for (int j = sciezka.size() - 1; j >= 0; j--) {
                cout << sciezka[j];
                if (j > 0) {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }
}

void GrafLista::algorytmBellmanaForda(int poczatek) {

    // Sprawdzenie, czy graf został zainicjalizowany
    if (wierzcholki == 0 || lista_skierowany == nullptr) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Inicjalizacja tablic odległości i poprzedników
    vector<int> odleglosci(wierzcholki, numeric_limits<int>::max());
    vector<int> poprzednicy(wierzcholki, -1);

    // Ustawienie odległości wierzchołka początkowego na 0
    odleglosci[poczatek] = 0;

    // Relaksacja krawędzi w grafie
    for (int i = 0; i < wierzcholki - 1; ++i) {
        for (int j = 0; j < wierzcholki; ++j) {
            for (const auto& krawedz : lista_skierowany[j]) {
                int sasiad = krawedz.docelowy;
                int waga = krawedz.waga;

                // Sprawdzenie, czy można zrelaksować krawędź
                if (odleglosci[j] != numeric_limits<int>::max() && odleglosci[j] + waga < odleglosci[sasiad]) {
                    odleglosci[sasiad] = odleglosci[j] + waga;
                    poprzednicy[sasiad] = j;
                }
            }
        }
    }

    // Sprawdzenie czy występują ujemne cykle
    for (int j = 0; j < wierzcholki; ++j) {
        for (const auto& krawedz : lista_skierowany[j]) {
            int sasiad = krawedz.docelowy;
            int waga = krawedz.waga;

            // Sprawdzenie, czy można zrelaksować krawędź
            if (odleglosci[j] != numeric_limits<int>::max() && odleglosci[j] + waga < odleglosci[sasiad]) {
                cout << "Graf zawiera ujemny cykl." << endl;
                return;
            }
        }
    }

    // Wyświetlanie wyników
    cout << "Wierzcholek startowy: " << poczatek << endl;
    cout << "Odleglosci: " << endl;
    for (int i = 0; i < wierzcholki; ++i) {
        cout << "Wierzcholek: " << i << ", Odleglosc: " << odleglosci[i] << endl;
    }

    cout << "Sciezki:" << endl;
    for (int i = 0; i < wierzcholki; ++i) {
        if (odleglosci[i] == numeric_limits<int>::max()) {
            cout << "Brak sciezki do wierzcholka " << i << endl;
        } else {
            cout << "Sciezka do wierzcholka " << i << ": " << i;
            int wierzcholek = poprzednicy[i];
            while (wierzcholek != -1) {
                cout << " <- " << wierzcholek;
                wierzcholek = poprzednicy[wierzcholek];
            }
            cout << endl;
        }
    }
}


void GrafLista::kasujGraf() {

    // czyscimy kazda liste sasiadow
    for (int i = 0; i < wierzcholki; i++) {
        lista_nieskierowany[i].clear();
        lista_skierowany[i].clear();
    }

    //czyscimy listy list sasiadow
    delete[] lista_nieskierowany;
    delete[] lista_skierowany;
    lista_nieskierowany = nullptr;
    lista_skierowany = nullptr;

    //resetujemy liczbe wierzcholkow
    wierzcholki = 0;
}





