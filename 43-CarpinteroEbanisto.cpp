#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#include "Matriz.h"

using namespace std;

const int INF = 1000000000;

int tablero(vector<int> const& cortes, int L) {
    int n = cortes.size();
    Matriz<int> M(n, n, 0);
    for (int d = 2; d <= n; d++) {
        for (int i = 0; i < n - d; i++) {
            int j = i + d;
            M[i][j] = INF;
            for (int k = i + 1; k < j; k++) {
                M[i][j] = min(M[i][k] + M[k][j] + (2 * (cortes[j] - cortes[i])), M[i][j]);
            }
        }
    }
    return M[0][n - 1];
}

bool resuelveCaso() {
    int L, N;
    cin >> L >> N;
    if (L == 0 && N == 0) return false;

    vector<int> cortes(N + 2, 0);
    cortes[0] = 0;
    cortes[N + 1] = L;
    for (int i = 1; i < N + 1; i++) {
        int aux;
        cin >> aux;
        cortes[i] = aux;
    }

    cout << tablero(cortes, L) << '\n';

    return true;
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    while (resuelveCaso());
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}