#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

#include "Matriz.h"

using namespace std;

bool A(string const& X) {
    int n = X.size();
    Matriz<bool> M_a(n, n, false);
    Matriz<bool> M_b(n, n, false);
    Matriz<bool> M_c(n, n, false);
    for (int i = 0; i < n; i++) {
        M_a[i][i] = (X[i] == 'a');
        M_b[i][i] = (X[i] == 'b');
        M_c[i][i] = (X[i] == 'c');
    }
    for (int d = 1; d <= n - 1; d++) {
        for (int i = 0; i < n - d; i++) {
            int j = i + d;
            for (int k = i; k <= j - 1; k++) {
                if (!M_a[i][j]) {
                    M_a[i][j] = (M_a[i][k] && M_c[k + 1][j]) ||
                        (M_b[i][k] && M_c[k + 1][j]) ||
                        (M_c[i][k] && M_a[k + 1][j]);
                }
                if (!M_b[i][j]) {
                    M_b[i][j] = (M_a[i][k] && M_a[k + 1][j]) ||
                        (M_a[i][k] && M_b[k + 1][j]) ||
                        (M_b[i][k] && M_b[k + 1][j]);
                }
                if (!M_c[i][j]) {
                    M_c[i][j] = (M_b[i][k] && M_a[k + 1][j]) ||
                        (M_c[i][k] && M_b[k + 1][j]) ||
                        (M_c[i][k] && M_c[k + 1][j]);
                }
            }
        }
    }
    return M_a[0][n - 1];
}

bool resuelveCaso() {
    string X;
    cin >> X;
    if (!cin) return false;

    if (A(X))
        cout << "SI\n";
    else
        cout << "NO\n";

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