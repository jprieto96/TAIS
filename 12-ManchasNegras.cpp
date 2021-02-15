#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "Grafo.h"

using Mapa = vector<string>; // lo utilizamos como si fuese un grafo

class ManchasNegras {
private:

	int F, C;
	vector<vector<bool>> visitado;
	int maxi;
	int num;

	const vector<pair<int, int>> adyacentes = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} }; // ejes i, j

	int dfs(Mapa const& m, int i, int j) {
		visitado[i][j] = true;
		int tam = 1;
		for (auto const& d : adyacentes) {
			int ni = i + d.first;
			int nj = j + d.second;
			if (ni < F && ni >= 0 && nj < C && nj >= 0 && !visitado[ni][nj] && m[ni][nj] == '#') {
				tam += dfs(m, ni, nj);
			}
		}
		return tam;
	}

public:

	ManchasNegras(Mapa const& m) : F(m.size()), C(m[0].size()), visitado(F, vector<bool>(C, false)), num(0), maxi(0) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visitado[i][j] && m[i][j] == '#') {
					++num;
					int tam = dfs(m, i, j);
					maxi = max(maxi, tam);
				}
			}
		}
	}

	int maximas() const {
		return maxi;
	}

	int numero() const {
		return num;
	}
};

bool resuelveCaso() {
	int F, C;
	cin >> F >> C;
	if (!cin) return false;

	Mapa mapa(F);
	for (string & l : mapa) {
		cin >> l;
	}

	ManchasNegras m(mapa);
	cout << m.numero() << " " << m.maximas() << '\n';
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