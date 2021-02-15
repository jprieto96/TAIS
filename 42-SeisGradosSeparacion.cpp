/////
//
// El problema se resuelve utilizando el algoritmo de Floyd para calcular recursivamente
// el camino minimo desde i hasta j pasando por los vertices desde 1 hasta k, siendo:
// Para todo i,j,k <= n:
// Matriz[i][j] = 0     Si i == j.
// Matriz[i][j] = Matriz[i][k] + Matriz[k][j];   Si Matriz[i][k] + Matriz[k][j] < Matriz[i][j]   Si hay arista de i a j.
// Matriz[i][j] = infinito   En otro caso.
//
// Finalmente se recorre la solucion para buscar el camino mas largo, que sera el 
// mayor grado de separación.
//
// El coste de la función es O(n^3) en tiempo y O(1) en espacio
// adicional, siendo n el número de personas en la red.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits> 
#include <climits>
#include <string>
#include <array>
#include <unordered_map>

#include "Matriz.h"

using namespace std;

const int INF = 1000000000;

void floyd(Matriz<int> const& G, Matriz<int> & C) {
	int V = G.numfils();
	C = G;

	// actualizaciones de la matriz
	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j) {
				int temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) { // es mejor pasar por k
					C[i][j] = temp;
				}
			}
		}
	}

}

bool resuelveCaso() {
	int P, R;
	cin >> P >> R;
	if (!cin)
		return false;

	Matriz<int> grafo(P, P, INF);

	unordered_map<string, int> nombres(P);
	int u, v;
	int k = 0;
	for (int i = 1; i <= R; ++i) { // leer aristas
		string n1, n2;
		cin >> n1 >> n2;
		
		auto p = nombres.insert({ n1, k });
		if (p.second) ++k;
		auto p2 = nombres.insert({ n2, k });
		if (p2.second) ++k;

		u = nombres.at(n1);
		v = nombres.at(n2);
		grafo[u][v] = 1;
		grafo[v][u] = 1;
	}

	Matriz<int> C;
	floyd(grafo, C);

	int V = grafo.numfils();
	int maximoCamino = 0;
	bool conectado = true;
	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			if (i != j && C[i][j] < INF) {
				if (C[i][j] > maximoCamino) {
					maximoCamino = C[i][j];
				}
			}
			if (j > i && C[i][j] >= INF) conectado = false;
		}
	}

	if (conectado) {
		cout << maximoCamino << '\n';
	}
	else {
		cout << "DESCONECTADA" << '\n';
	}


	return true;
}



int main() {

#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}