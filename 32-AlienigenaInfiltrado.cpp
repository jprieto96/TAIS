#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct intervalo {
    int C;
    int F;
};

bool operator<(const intervalo& e1, const intervalo& e2) {
    return e1.C < e2.C || (e1.C == e2.C) && (e1.C < e1.F) < (e2.C - e2.F);
}

pair<bool, int> sol(std::vector<intervalo> const& v, int C, int F) {
    int nTrabajos = 0;
    int i = 0;
    bool posible = true;
    while (posible && C < F) {
        int maxi = -1;
        while (i < (int) v.size() && v[i].C <= C) {
            maxi = max(maxi, v[i].F);
            ++i;
        }
        if (maxi == -1) posible = false;
        ++nTrabajos;
        C = maxi;
    }
    return { posible, nTrabajos };
}

bool resuelveCaso() {
    int C, F, N;
    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)
        return false;

    vector<intervalo> v(N);
    for (auto& e : v) {
        int c, f;
        cin >> c >> f;
        e = { c, f };
    }

    sort(v.begin(), v.end());

    auto s = sol(v, C, F);
    if (!s.first) cout << "Imposible\n";
    else cout << s.second << '\n';

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