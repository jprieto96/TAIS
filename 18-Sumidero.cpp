#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "Digrafo.h"

class Sumidero {

private:

	pair<bool, int> s;
	vector<bool> descartes;

	void busqueda(Digrafo const& g) { 
		int cont = 0;
		for (int i = 0; i < g.V(); i++) {
			cont = 0;
			for (int j = 0; j < g.V(); j++) {
				if (i != j && !descartes[j]) {
					if (!g.hayArista(i, j)) {
						descartes[j] = true;;
					}
				}
			}
		}
	}

public:

	Sumidero(Digrafo const& g) : descartes(g.V(), false), s({ false, 0 }) {
		busqueda(g);
	}

	pair<bool, int> esSumidero() {
		for (int i = 0; i < descartes.size(); ++i) {
			if (!descartes[i]) {
				s.first = true;
				s.second = i;
				break;
			}
		}
		return s;
	}

};

bool resuelveCaso() {
	Digrafo g(cin);
	if (!cin) return false;

	Sumidero s(g);
	auto sol = s.esSumidero();
	if (sol.first)
		cout << "SI " << sol.second << '\n';
	else
		cout << "NO\n";

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