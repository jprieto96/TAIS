#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "Grafo.h"

class ArbolLibre {
private:
	vector<bool> visitado;
	bool aciclico, conexo, libre;

	bool esCiclico(Grafo const& g, int vertice, int parent) {
		visitado[vertice] = true;
		for (int v : g.ady(vertice)) {
			if (!visitado[v]) {
				if (esCiclico(g, v, vertice)) return true;
			}
			else if(v != parent) {
				return true;
			}
		}
		return false;
	}

public:

	ArbolLibre(Grafo const& g) : visitado(g.V(), false), conexo(true), aciclico(false), libre(false) {
		// Solo compruebo si es ciclico suponiendo que el grafo es conexo porque en caso de que no sea conexo ya no seria arbol libre
		aciclico = !esCiclico(g, 0, -1);
		conexo = esConexo();
		libre = aciclico && conexo;
	}

	bool esConexo() {
		for (int i = 0; i < visitado.size() && conexo; i++)
			conexo = visitado[i];
		return conexo;
	}

	bool esArbolLibre() {
		return libre;
	}
};

bool resuelveCaso() {
	int V, A;
	cin >> V >> A;
	if (!cin) return false;

	Grafo g(V);
	int v, w;
	for (int i = 0; i < A; i++) {
		cin >> v >> w;
		g.ponArista(v, w);
	}

	ArbolLibre a(g);
	cout << (a.esArbolLibre() ? "SI\n" : "NO\n");
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