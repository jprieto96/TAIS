#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "Digrafo.h"

class OrdenTareas {

private:

	vector<bool> visitado;
	vector<bool> apilado;
	bool hayCiclo;
	deque<int> tareas;

	void dfs(Digrafo const& g, int vertice) {
		visitado[vertice] = true;
		apilado[vertice] = true;
		for (int w : g.ady(vertice)) {
			if (hayCiclo) return;
			if (!visitado[w]) {
				dfs(g, w);
			}
			else if(apilado[w]){
				hayCiclo = true;
			}
		}
		tareas.push_front(vertice + 1);
		apilado[vertice] = false;
	}

public:

	OrdenTareas(Digrafo const& g) : visitado(g.V(), false), apilado(g.V(), false), hayCiclo(false) {
		for (int i = 0; i < g.V(); i++) {
			if (!visitado[i] && !hayCiclo) {
				dfs(g, i);
			}
		}
	}

	bool esImposible() const {
		return hayCiclo;
	}

	vector<int> ordenadas() {
		vector<int> tOrdenadas(tareas.size());
		for (int i = 0; i < tareas.size(); ++i) {
			tOrdenadas[i] = tareas.front();
			tareas.pop_front();
			tareas.push_back(tOrdenadas[i]);
		}
		return tOrdenadas;
	}

};

bool resuelveCaso() {
	Digrafo g(cin, 1);
	if (!cin) return false;

	OrdenTareas ot(g);
	
	if (ot.esImposible()) {
		cout << "Imposible\n";
		return true;
	}
	
	vector<int> tareasOrdenadas = ot.ordenadas();
	for (int const& i : tareasOrdenadas) {
		cout << i << " ";
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