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
    return e1.C < e2.C;
}

int sol(std::vector<intervalo> const& v) {
    priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int maxi = 0;
    int i = 0;
    while (!pq.empty() || i < v.size()) {
        if (i == v.size()) pq.pop();
        else {
            if (pq.empty()) {
                pq.push(v[i].F);
                i++;
            }
            else {
                if (v[i].C < pq.top()) {
                    pq.push(v[i].F);
                    i++;
                }
                else {
                    pq.pop();
                }
            }
        }
        maxi = max(maxi, (int)pq.size() - 1);
    }
    return maxi;
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    if (n == 0)
        return false;

    std::vector<intervalo> v(n);
    for (auto& e : v) {
        int C, F;
        cin >> C >> F;
        e = { C, F };
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