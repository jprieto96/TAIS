#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "Grafo.h"


class ColocarGuardias {
private:

	vector<bool> visitado;
	int mini;
	bool esBipartito;
	vector<int> numBlancosYNegros;
	vector<int> colorVertice;

	bool dfs(Grafo const& g, int vertice, int k) {
		visitado[vertice] = true;
		colorVertice[vertice] = k;
		numBlancosYNegros[k]++;
		for (int v : g.ady(vertice)) {
			if (!visitado[v]) {
				if (colorVertice[v] == -1) {
					if (!dfs(g, v, 1 - k))
						return false;
				}
				else if (colorVertice[v] != 1 - k) {
					return false;
				}
			}
			else if (colorVertice[v] != -1 && colorVertice[v] != 1 - k)
				return false;
		}
		return true;
	}

public:

	ColocarGuardias(Grafo const& g) : visitado(g.V(), false), mini(0), colorVertice(g.V(), -1), esBipartito(false), numBlancosYNegros(2, 0) {
		for (int i = 0; i < g.V(); i++) {
			if (!visitado[i]) {
				numBlancosYNegros[0] = 0;
				numBlancosYNegros[1] = 0;
				esBipartito = dfs(g, i, 0);
				if (!esBipartito) break;
				mini += min(numBlancosYNegros[0], numBlancosYNegros[1]);
			}
		}
		
	}

	int minimo() const {
		return mini;
	}

	bool esImposible() const {
		return !esBipartito;
	}
};

bool resuelveCaso() {
	int N, C;
	cin >> N >> C;
	if (!cin) return false;

	Grafo g(N);
	int v, w;
	for (int i = 0; i < C; i++) {
		cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}

	ColocarGuardias a(g);
	if (a.esImposible()) cout << "IMPOSIBLE\n";
	else cout << a.minimo() << '\n';

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