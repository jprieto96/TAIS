#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

#include "Digrafo.h"

const int MAX = 10000;
const int INF = 1000000000;

int adyacente(int vertice, int num) {
	switch (num) {
		case 0: return (vertice + 1) % MAX;
		case 1: return (vertice * 2) % MAX;
		case 2: return vertice / 3;
	}
}

int bfs(int origen, int destino) {
	if (origen == destino) return 0;
	vector<int> distancia(MAX, INF);
	distancia[origen] = 0;
	queue<int> q;
	q.push(origen);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < 3; i++) {
			int w = adyacente(v, i);
			if (distancia[w] == INF) {
				distancia[w] = distancia[v] + 1;
				if (w == destino) return distancia[w];
				else q.push(w);
			}
		}
	}
}

bool resuelveCaso() {
	int numOrigen, numDesitino;
	cin >> numOrigen >> numDesitino;
	if (!cin) return false;

	cout << bfs(numOrigen, numDesitino) << '\n';

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