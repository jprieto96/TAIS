#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int sol(vector<int> const& alturas, vector<int> const& lEsquis) {
    int difMax = 0;
    for (int i = 0; i < (int)alturas.size(); i++) {
        difMax += abs(alturas[i] - lEsquis[i]);
    }
    return difMax;
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    if (n == 0)
        return false;

    vector<int> alturas(n);
    vector<int> lEsquis(n);

    for (auto& e : alturas) {
        cin >> e;
    }

    for (auto& e : lEsquis) {
        cin >> e;
    }

    sort(alturas.begin(), alturas.end());
    sort(lEsquis.begin(), lEsquis.end());

    std::cout << sol(alturas, lEsquis) << '\n';

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