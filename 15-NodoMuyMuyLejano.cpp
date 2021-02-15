#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

#include "Grafo.h"


class NodoLejano {
private:

	vector<bool> visitado;
	vector<int> distancia;
	int s;
	int iniTTL;
	int noAlcanzables;

	int bfs(Grafo const& g) {
		queue<int> q;
		visitado[s] = true;
		distancia[s] = 0;
		q.push(s);
		int nVisitados = 0;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int w : g.ady(v)) {
				if (!visitado[w]) {
					distancia[w] = distancia[v] + 1;
					visitado[w] = true;
					q.push(w);
					if (distancia[w] <= iniTTL)
						++nVisitados;
				}
				
			}
		}
		return nVisitados;
	}

public:

	NodoLejano(Grafo const& g, int const& origen, int const& ttl) : visitado(g.V(), false), s(origen), iniTTL(ttl), noAlcanzables(g.V() - 1), distancia(g.V()) {
		int visitados = bfs(g);
		noAlcanzables -= visitados;
	}

	int nodosInalacanzables() const {
		return noAlcanzables;
	}
};

bool resuelveCaso() {
	Grafo g(cin, 1);
	if (!cin) return false;

	int k, origen, ttl;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> origen >> ttl;
		NodoLejano a(g, origen - 1, ttl);
		cout << a.nodosInalacanzables() << '\n';
	}

	cout << "---\n";
	return true;
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// restablecimiento de cin
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}