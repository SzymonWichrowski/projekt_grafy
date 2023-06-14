#include <set>
#include <algorithm>
#include <limits>
#include <queue>
#include "GrafMacierz.h"
#include "../narzedzia/UnionFind.h"

void GrafMacierz::nowyGraf(int wierzcholki) {

    this -> wierzcholki = wierzcholki;
    macierz_nieskierowany.resize(wierzcholki, vector<int>(wierzcholki, INT_MIN));
    macierz_skierowany.resize(wierzcholki, vector<int>(wierzcholki, INT_MIN));
}

void GrafMacierz::nieskierowanyWypisz() {

    cout << "V:  ";
    for (int i = 0; i < wierzcholki; i++) {
        cout << "V" << i << "    ";
    }
    cout << endl;
    for (int i = 0; i < wierzcholki; i++) {
        cout << "V" << i << ": ";
        for (int j = 0; j < wierzcholki; j++) {
            cout << macierz_nieskierowany[i][j] << "     ";
        }
        cout << endl;
    }
}

void GrafMacierz::skierowanyWypisz() {

    cout << "V:  ";
    for (int i = 0; i < wierzcholki; i++) {
        cout << "V" << i << "    ";
    }
    cout << endl;
    for (int i = 0; i < wierzcholki; i++) {
        cout << "V" << i << ": ";
        for (int j = 0; j < wierzcholki; j++) {
            cout << macierz_skierowany[i][j] << "     ";
        }
        cout << endl;
    }
}

void GrafMacierz::nowaKrawedz(int wierzcholek1, int wierzcholek2, int waga) {

    //dla grafu nieskierowanego
    if (wierzcholek1 >= 0 && wierzcholek1 < wierzcholki &&
        wierzcholek2 >= 0 && wierzcholek2 < wierzcholki) {
        if (macierz_nieskierowany[wierzcholek1][wierzcholek2] == INT_MIN) {
            macierz_nieskierowany[wierzcholek1][wierzcholek2] = waga;
            macierz_nieskierowany[wierzcholek2][wierzcholek1] = waga;
        }
        else {
            if (waga < macierz_nieskierowany[wierzcholek1][wierzcholek2]) {
                macierz_nieskierowany[wierzcholek1][wierzcholek2] = waga;
                macierz_nieskierowany[wierzcholek2][wierzcholek1] = waga;
            }
        }
    }

    //dla grafu skierowanego
    if (wierzcholek1 >= 0 && wierzcholek1 < wierzcholki &&
        wierzcholek2 >= 0 && wierzcholek2 < wierzcholki) {
        if (macierz_skierowany[wierzcholek1][wierzcholek2] == INT_MIN) {
            macierz_skierowany[wierzcholek1][wierzcholek2] = waga;
        }
        else if (waga < macierz_skierowany[wierzcholek1][wierzcholek2]) {
                macierz_skierowany[wierzcholek1][wierzcholek2] = waga;
            }
    }
}

void GrafMacierz::algorytmPrima() {

    if (wierzcholki == 0) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    vector<bool> odwiedzone(wierzcholki, false);  // Tablica odwiedzonych wierzchołków
    vector<int> koszty(wierzcholki, INT_MAX);  // Tablica kosztów dojścia do wierzchołków
    vector<int> poprzedniki(wierzcholki, INT_MIN);  // Tablica poprzedników dla wierzchołków
    koszty[0] = 0;  // Koszt dojścia do pierwszego wierzchołka jest zerowy

    // Zbiór krawędzi MST
    set<pair<int, int>> mst;

    for (int i = 0; i < wierzcholki - 1; i++) {
        int aktualny = INT_MIN;  // Aktualnie wybrany wierzchołek
        int najmniejszyKoszt = INT_MAX;  // Najmniejszy koszt dojścia

        // Wybór wierzchołka o najmniejszym koszcie spośród nieodwiedzonych
        for (int v = 0; v < wierzcholki; v++) {
            if (!odwiedzone[v] && koszty[v] < najmniejszyKoszt) {
                aktualny = v;
                najmniejszyKoszt = koszty[v];
            }
        }

        odwiedzone[aktualny] = true;  // Oznaczanie bieżącego wierzchołka jako odwiedzony

        // Dodawanie krawędzi do MST
        if (poprzedniki[aktualny] != INT_MIN)
            mst.insert({aktualny, poprzedniki[aktualny]});

        // Aktualizacja kosztów dojścia i poprzedników dla sąsiadujących wierzchołków
        for (int v = 0; v < wierzcholki; v++) {
            if (!odwiedzone[v] && macierz_nieskierowany[aktualny][v] != INT_MIN && macierz_nieskierowany[aktualny][v] < koszty[v]) {
                koszty[v] = macierz_nieskierowany[aktualny][v];
                poprzedniki[v] = aktualny;
            }
        }
    }

    // Suma wag krawędzi MST
    int sumaWag = 0;
    cout << "Krawedzie tworzace MST:" << endl;
    for (int i = 1; i < wierzcholki; i++) {
        cout << "(" << poprzedniki[i] << " - " << i << ") waga: " << macierz_nieskierowany[i][poprzedniki[i]] << endl;
        sumaWag += macierz_nieskierowany[i][poprzedniki[i]];
    }
    cout << "Suma wag krawedzi MST: " << sumaWag << endl;
}

void GrafMacierz::algorytmKruskala() {
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
        for (int j = 0; j < wierzcholki; j++) {
            if (macierz_nieskierowany[i][j] != INT_MIN) {
                krawedzie.push_back(Krawedz(i, j, macierz_nieskierowany[i][j]));
            }
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

void GrafMacierz::algorytmDijkstry(int poczatek) {

    // Sprawdzenie, czy graf został zainicjalizowany
    if (wierzcholki == 0 || macierz_skierowany.empty()) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Inicjalizacja tablic odległości i poprzedników
    vector<int> odleglosci(wierzcholki, numeric_limits<int>::max());
    vector<int> poprzednicy(wierzcholki, INT_MIN);

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

        // Przejście przez wiersz macierzy dla aktualnego wierzchołka
        for (int sasiad = 0; sasiad < wierzcholki; sasiad++) {
            int waga = macierz_skierowany[aktualnyWierzcholek][sasiad];

            // Sprawdzenie, czy istnieje krawędź między wierzchołkami
            if (waga != INT_MIN) {
                // Sprawdzenie, czy nowa odległość jest mniejsza od dotychczasowej
                if (odleglosci[aktualnyWierzcholek] + waga < odleglosci[sasiad]) {
                    if(waga < 0) {
                        cout << "Waga ujemna znaleziona! Algorytm zostanie przerwany." << endl;
                        return;
                    }

                    odleglosci[sasiad] = odleglosci[aktualnyWierzcholek] + waga;
                    poprzednicy[sasiad] = aktualnyWierzcholek;

                    // Dodanie sąsiada do kolejki
                    kolejka.push(make_pair(odleglosci[sasiad], sasiad));
                }
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
            while (wierzcholek != INT_MIN) {
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

void GrafMacierz::algorytmBellmanaForda(int poczatek) {

    // Sprawdzenie, czy graf został zainicjalizowany
    if (wierzcholki == 0 || macierz_skierowany.empty()) {
        cout << "Graf nie zostal zainicjalizowany." << endl;
        return;
    }

    // Inicjalizacja tablic odległości i poprzedników
    vector<int> odleglosci(wierzcholki, numeric_limits<int>::max());
    vector<int> poprzednicy(wierzcholki, INT_MIN);

    // Ustawienie odległości wierzchołka początkowego na 0
    odleglosci[poczatek] = 0;

    // Relaksacja krawędzi w grafie
    for (int i = 0; i < wierzcholki - 1; ++i) {
        for (int j = 0; j < wierzcholki; ++j) {
            for (int k = 0; k < wierzcholki; ++k) {
                int waga = macierz_skierowany[j][k];

                // Sprawdzenie, czy można zrelaksować krawędź
                if (odleglosci[j] != numeric_limits<int>::max() && waga != INT_MIN && odleglosci[j] + waga < odleglosci[k]) {
                    odleglosci[k] = odleglosci[j] + waga;
                    poprzednicy[k] = j;
                }
            }
        }
    }

    // Sprawdzenie czy występują ujemne cykle
    for (int j = 0; j < wierzcholki; ++j) {
        for (int k = 0; k < wierzcholki; ++k) {
            int waga = macierz_skierowany[j][k];

            // Sprawdzenie, czy można zrelaksować krawędź
            if (odleglosci[j] != numeric_limits<int>::max() && waga != INT_MIN && odleglosci[j] + waga < odleglosci[k]) {
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
            while (wierzcholek != INT_MIN) {
                cout << " <- " << wierzcholek;
                wierzcholek = poprzednicy[wierzcholek];
            }
            cout << endl;
        }
    }
}

void GrafMacierz::kasujGraf() {

    //dzieki zastosowaniu zmiennych wektorowych kasowanie grafu nie jest skomplikowane
    macierz_nieskierowany.clear();
    macierz_skierowany.clear();
    wierzcholki = 0;
}



