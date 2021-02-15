#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "PriorityQueue.h"

struct cliente {
	int tiempo;
	int numCaja;
};

bool operator<(cliente const& c1, cliente const& c2) {
	return c1.tiempo < c2.tiempo || (c1.tiempo == c2.tiempo && c1.numCaja < c2.numCaja);
}

bool resuelveCaso() {
	int nCajas, nClientes;
	cin >> nCajas >> nClientes;
	if (nCajas == 0 && nClientes == 0) return false;

	cliente c;
	PriorityQueue<cliente> queue;

	int j = nClientes;
	for (int i = 1; i <= nCajas && j > 0; i++) {
		cin >> c.tiempo;
		c.numCaja = i;
		queue.push(c);
		--j;
	}

	if (queue.size() < nCajas) {
		cout << nClientes + 1 << '\n';
		return true;
	}

	while (j > 0) {
		cliente cli1 = queue.top(); queue.pop();
		cin >> c.tiempo;
		c.tiempo += cli1.tiempo;
		c.numCaja = cli1.numCaja;
		queue.push(c);
		--j;
	}

	
	cout << queue.top().numCaja << '\n';
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