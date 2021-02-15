#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

struct tPelis
{
    int duracion;
    int comienzo;
    int fin;
};

int sol(std::vector<tPelis>& v)
{
    std::sort(v.begin(), v.end(),
        [](const tPelis& lhs, const tPelis& rhs) { return lhs.fin < rhs.fin; });

    int s = 1, ult = v[0].fin;

    for (int i = 1; i < v.size(); i++)
    {
        if (ult <= v[i].comienzo)
        {
            s++;
            ult = v[i].fin;
        }
    }

    return s;
}

bool resuelveCaso()
{
    int n;
    std::cin >> n;
    if (n == 0)
        return false;

    std::vector<tPelis> v(n);
    for (auto& e : v)
    {
        int h, m;
        char c;
        std::cin >> h;
        e.comienzo += h * 60;
        std::cin >> c >> m;
        e.comienzo += m;

        std::cin >> e.duracion;
        e.duracion += 10; // necesita descansar 10 min
        e.fin = e.comienzo + e.duracion;
    }

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