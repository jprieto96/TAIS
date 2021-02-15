#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#include "Matriz.h"

using namespace std;

const int INF = 1000000000;

int vacas(vector<int> const& cubos, Matriz<int> & M) {
    int N = cubos.size();
    int i = 0, j = N - 1;
    while (i > j) {
        for (int k = i; k <= j; k++) {
            M[i][j] = max(M[i][j], cubos[k])
        }
    }
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) return false;

    vector<int> cubos(N);
    for (int& i : cubos) {
        cin >> i;
    }

    Matriz<int> M(N, N, -1);
    vacas(cubos, M, 0, N - 1) << '\n';
    cout << M[0][N - 1] << '\n';

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