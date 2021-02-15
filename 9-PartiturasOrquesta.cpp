#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "PriorityQueue.h"

struct datos {
	int numPart = 1;
	int ins;
};

bool operator>(datos const& d1, datos const& d2) {
	int n1 = d1.ins / d1.numPart;
	int n2 = d2.ins / d2.numPart;
	if (d1.ins % d1.numPart != 0) n1++;
	if (d2.ins % d2.numPart != 0) n2++;
	return n1 > n2;
}

bool resuelveCaso() {
	int p, n;
	cin >> p >> n;
	if (!cin) return false;

	datos d;
	PriorityQueue<datos, greater<datos>> pq;
	for (int i = 0; i < n; i++) {
		cin >> d.ins;
		pq.push(d);
		--p;
	}

	while (p > 0) {
		datos da = pq.top();
		pq.pop();
		++da.numPart;
		pq.push(da);
		--p;
	}

	auto v = pq.top();
	int atrilMasCompartido = v.ins / v.numPart;
	if (v.ins % v.numPart != 0) ++atrilMasCompartido;
	cout << atrilMasCompartido << '\n';
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