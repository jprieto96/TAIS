#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "Matriz.h"

struct cofre {
	int profundidad;
	int oro;
	bool cogido;
};

struct solu {
	int nCofres;
	int cont;
};

// descendente
int cofre_rec(vector<cofre> const& v, int i, int j, Matriz<int>& c) {
	if (c[i][j] != -1) return c[i][j];
	if (i == 0 || j == 0) c[i][j] = 0;
	else if (3 * v[i - 1].profundidad > j) {
		c[i][j] = cofre_rec(v, i - 1, j, c);
	}
	else {
		c[i][j] = max(cofre_rec(v, i - 1, j, c), 
						cofre_rec(v, i - 1, j - (3 * v[i - 1].profundidad), c) + v[i - 1].oro);
	}
	return c[i][j];
}

//ascendente
int cofre_rec_as(vector<cofre> const& v, int n, int m, Matriz<int>& c) {
	for (int i = 0; i < n + 1; i++) c[i][0] = 0;
	for (int j = 0; j < m + 1; j++) c[0][j] = 0;

	for (int i = 1; i < n + 1; i++) {
		for (int j = 0; j < m + 1; j++) {
			if (3 * v[i - 1].profundidad > j) c[i][j] = c[i - 1][j];
			else {
				c[i][j] = max(c[i - 1][j], c[i - 1][j - 3 * v[i - 1].profundidad] + v[i - 1].oro);
			}
		}
	}
	return c[n][m];
}

solu sol(vector<cofre>& v, int T) {
	int n = v.size();
	Matriz<int> cofresRecogidos(n + 1, T + 1, -1);
	int nRecogidos = cofre_rec(v, n, T, cofresRecogidos);
	int cont = 0;
	int i = n, j = T;
	while (i > 0 && j > 0) {
		if (cofresRecogidos[i][j] != cofresRecogidos[i - 1][j]) {
			v[i - 1].cogido = true;
			j -= 3 * v[i - 1].profundidad;
			++cont;
		}
		--i;
	}

	return { nRecogidos, cont };
}

bool resuelveCaso() {
	int T;
	cin >> T;
	if (!cin) return false;

	int N;
	cin >> N;
	vector<cofre> v;
	for (int i = 0; i < N; i++) {
		int p, o;
		cin >> p >> o;
		v.push_back({ p, o, false });
	}

	auto s = sol(v, T);
	cout << s.nCofres << '\n';
	cout << s.cont << '\n';

	for (auto const& c : v) {
		if (c.cogido)
			cout << c.profundidad << " " << c.oro << '\n';
	}

	cout << "---\n";
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