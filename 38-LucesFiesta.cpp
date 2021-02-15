#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#include "Matriz.h"

struct bombilla {
	int potencia;
	int coste;
};

int cintaRes(vector<bombilla> const& v, int i, int j, int Pmin, Matriz<int>& c) {
	if (c[i][j] != -1) return c[i][j];
	if (i == 0 || j == 0) c[i][j] = 0;
	else if (v[i - 1].potencia > j) {
		c[i][j] = cintaRes(v, i - 1, j, Pmin, c);
	}
	else if (v[i - 1].potencia <= Pmin) {
		c[i][j] = max(cintaRes(v, i - 1, j, Pmin, c),
			cintaRes(v, i - 1, j - v[i - 1].potencia, Pmin - v[i - 1].potencia, c) + v[i - 1].coste);
	}
	return c[i][j];
}

bombilla sol(vector<bombilla> const& v, int Pmax, int Pmin) {
	int N = v.size();
	Matriz<int> cinta(N + 1, Pmax + 1, -1);
	auto s = cintaRes(v, N, Pmax, Pmin, cinta);
	return { s, 0 };
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin) return false;

	int Pmax, Pmin;
	cin >> Pmax >> Pmin;
	vector<bombilla> v;
	bombilla b;
	for (int i = 0; i < N; i++) {
		int pAux;
		cin >> pAux;
		b.potencia = pAux;
		v.push_back(b);
	}

	for (auto & a : v) {
		int cAux;
		cin >> cAux;
		a.coste = cAux;
	}

	auto s = sol(v, Pmax, Pmin);
	
	cout << s.coste << " " << s.potencia << '\n';

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