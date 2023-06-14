#include "UnionFind.h"

UnionFind::UnionFind(int n) {

    parent.resize(n);
    rank.resize(n, 0);

    // Inicjalizacja każdego elementu jako osobnego zbioru
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int UnionFind::find(int x) {

    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // Kompresja ścieżki
    }
    return parent[x];
}

void UnionFind::merge(int x, int y) {

    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

