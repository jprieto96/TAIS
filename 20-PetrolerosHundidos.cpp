#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "ConjuntosDisjuntos.h"

using Mapa = vector<vector<char>>; // lo utilizamos como si fuese un grafo

class ManchasNegras {
private:

	int F, C;
	vector<vector<bool>> visitado;
	ConjuntosDisjuntos c;
	int maxi;

	const vector<pair<int, int>> adyacentes = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, 1}, {-1, -1}, {1, 1}, {1, -1} };

	void dfs(Mapa const& m, int i, int j) {
		visitado[i][j] = true;
		for (auto const& d : adyacentes) {
			int ni = i + d.first;
			int nj = j + d.second;
			if (ni < F && ni >= 0 && nj < C && nj >= 0 && !visitado[ni][nj] && m[ni][nj] == '#') {
				c.unir(i * C + j, ni * C + nj);
				dfs(m, ni, nj);
			}
		}
		maxi = max(maxi, c.cardinal(i * C + j));
	}

public:

	ManchasNegras(Mapa const& m) : F(m.size()), C(m[0].size()), visitado(F, vector<bool>(C, false)), maxi(0), c(F * C) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visitado[i][j] && m[i][j] == '#') {
					dfs(m, i, j);
				}
			}
		}
	}

	int maximas() const {
		return maxi;
	}

	void addMancha(int i, int j, Mapa const& m) {
		for (auto const& d : adyacentes) {
			int ni = i + d.first;
			int nj = j + d.second;
			if (ni < F && ni >= 0 && nj < C && nj >= 0 && m[ni][nj] == '#') {
				c.unir(i * C + j, ni * C + nj);
			}
		}
		maxi = max(maxi, c.cardinal(i * C + j));
	}

};

bool resuelveCaso() {
	int F, C;
	cin >> F >> C;
	if (!cin) return false;
	cin.ignore();

	Mapa mapa(F, vector<char>(C));
	for (int i = 0; i < F; i++) {
		for (int j = 0; j < C; j++) {
			char c;
			cin.get(c);
			if(c == '\n') cin.get(c);
			mapa[i][j] = c;
		}
	}
	

	ManchasNegras m(mapa);
	cout << m.maximas() << " ";

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {		
		int f, c;
		cin >> f >> c;
		mapa[f - 1][c - 1] = '#';
		m.addMancha(f - 1, c - 1, mapa);
		cout << m.maximas() << " ";
	}

	cout << '\n';
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