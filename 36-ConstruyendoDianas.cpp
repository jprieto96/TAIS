#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

vector<int> solucion(vector<int> const& v, int C) {
    int n = v.size();
    vector<EntInf> dardos(C + 1, Infinito);
    dardos[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = v[i - 1]; j <= C; j++) {
            dardos[j] = min(dardos[j], dardos[j - v[i - 1]] + 1);
        }
    }

    vector<int> sol;
    if (dardos[C] != Infinito) {
        int i = n, j = C;
        while (j > 0) {
            if (v[i - 1] <= j && dardos[j] == dardos[j - v[i - 1]] + 1) {
                sol.push_back(v[i - 1]); // tomamos dardo i
                j -= v[i - 1];
            }
            else
                --i; // no tomamos dardo de tipo i
        }
    }
    return sol;
}

bool resuelveCaso() {
    int nPuntos;
    cin >> nPuntos;
    if (!cin) return false;

    int nSectores;
    cin >> nSectores;

    vector<int> puntuacion(nSectores);
    for (int i = 0; i < nSectores; i++) {
        int aux;
        cin >> aux;
        puntuacion[i] = aux;
    }

    vector<int> sectoresDados = solucion(puntuacion, nPuntos);

    if (sectoresDados.empty()) {
        cout << "Imposible\n";
    }
    else {
        sort(sectoresDados.begin(), sectoresDados.end(), greater<int>());
        cout << sectoresDados.size() << ": ";
        for (int w : sectoresDados) {
            cout << w << " ";
        }
        cout << '\n';
    }

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