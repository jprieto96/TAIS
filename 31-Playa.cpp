#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edificios {
    int W;
    int E;
};

bool operator<(const edificios & e1, const edificios & e2) {
    return e1.W < e2.W || (e1.W == e2.W) && (e1.W - e2.E) < (e2.W - e2.E);
}

int sol(std::vector<edificios> const& v) {
    int puentes = 1, fin = v[0].E;
    for (int i = 1; i < (int) v.size(); i++) {
        if (v[i].W < fin) {
            if (fin > v[i].E) fin = v[i].E;
        }
        else {
            ++puentes;
            fin = v[i].E;
        }
    }
    return puentes;
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    if (n == 0)
        return false;

    std::vector<edificios> v(n);
    for (auto& e : v) {
        int W, E;
        cin >> W >> E;
        e = { W, E };
    }

    sort(v.begin(), v.end());

    std::cout << sol(v) << '\n';

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