#pragma once
#include <vector>

using namespace std;

class UnionFind {

    public:
        UnionFind(int n);
        int find(int x);                    //Znajdowanie reprezentanta zbioru
        void merge(int x, int y);           //Scalenie zbiorów
    private:
        vector<int> parent;
        vector<int> rank;
};