#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "GrafoValorado.h"

class Camion {

private:

	vector<bool> visitado;
	vector<bool> apilado;
	int _origen;
	int _destino;
	int _anchura;
	bool _puedeCircular;

	void dfs(GrafoValorado<int> const& g, int vertice) {
		visitado[vertice] = true;
		bool ok = false;
		for (auto a : g.ady(vertice)) {
			int w = a.otro(vertice);
			if (!visitado[w] && _anchura <= a.valor()) {
				visitado[w] = true;
				if (w == _destino)
					_puedeCircular = true;
				dfs(g, w);
			}
		}
	}

public:

	Camion(GrafoValorado<int> const& g, int origen, int destino, int anchura) : visitado(g.V(), false), _origen(origen), _destino(destino), _anchura(anchura), _puedeCircular(false) {
		dfs(g, origen);
	}

	bool puedeCircular() const {
		return _puedeCircular;;
	}

};

bool resuelveCaso() {
	GrafoValorado<int> g(cin, 1);
	if (!cin) return false;

	int k, origen, destino, anchura;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> origen >> destino >> anchura;
		Camion c(g, origen - 1, destino - 1, anchura);
		cout << (c.puedeCircular() ? "SI\n" : "NO\n");
	}


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