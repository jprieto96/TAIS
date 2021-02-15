#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "bintree_eda.h"

struct sol {
	bool esAVL;
	int min, max, altura;
};

sol esArbolAVL(bintree<int> const& arbol) {
	if (arbol.empty()) return { true, 0, 0, 0 };
	else {
		sol izq = esArbolAVL(arbol.left());
		sol der = esArbolAVL(arbol.right());

		sol s;
		s.min = (arbol.left().empty()) ? arbol.root() : izq.min;
		s.max = (arbol.right().empty()) ? arbol.root() : der.max;

		bool esABB = (arbol.left().empty() || izq.max < arbol.root()) &&
			(arbol.right().empty() || der.min > arbol.root());

		s.esAVL = esABB && izq.esAVL && der.esAVL && abs(izq.altura - der.altura) <= 1;
		s.altura = max(izq.altura, der.altura) + 1;

		return s;
	}
}

void resuelveCaso() {
	bintree<int> arbol = leerArbol(-1);
	sol s = esArbolAVL(arbol);
	if (s.esAVL) cout << "SI\n";
	else cout << "NO\n";
}

int main() {
	// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int nCasos;
	cin >> nCasos;
	for (int i = 0; i < nCasos; i++) resuelveCaso();

	// restablecimiento de cin
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
	system("pause");
#endif
	return 0;
}