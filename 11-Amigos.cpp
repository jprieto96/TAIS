#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "Grafo.h"

class Amigos {
private:

	vector<bool> visitado;
	int maxi;

	int dfs(Grafo const& g, int vertice) {
		visitado[vertice] = true;
		int tam = 1;
		for (int v : g.ady(vertice)) {
			if (!visitado[v]) {
				tam += dfs(g, v);
			}
		}
		return tam;
	}

public:

	Amigos(Grafo const& g) : visitado(g.V(), false), maxi(0){
		for (int i = 0; i < g.V(); i++) { // se recorre hace una dfs para cad vertice para encontrar la maxima componente conexa
			if (!visitado[i]) {
				int tam = dfs(g, i);
				maxi = max(maxi, tam);
			}
		}
	}

	int maximo() const {
		return maxi;
	}
};

void resuelveCaso() {
	int N, M;
	cin >> N >> M;

	Grafo g(N);
	int v, w;
	for (int i = 0; i < M; i++) {
		cin >> v >> w;
		g.ponArista(v - 1, w - 1);
	}

	Amigos a(g);
	cout << a.maximo() << '\n';
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int nCasos;
	cin >> nCasos;
	for (int i = 0; i < nCasos; i++) {
		resuelveCaso();
	}

	// restablecimiento de cin
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}