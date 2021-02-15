#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "PriorityQueue.h"

struct datos {
	string nombre;
	int gravedad;
	int prioridad;
};

bool operator>(datos const& d1, datos const& d2) {
	return d1.gravedad > d2.gravedad ||
		(d1.gravedad == d2.gravedad && d1.prioridad > d2.prioridad);
}

bool resuelveCaso() {
	int nCasos;
	cin >> nCasos;
	if (nCasos == 0) return false;

	datos d;
	string tipo;
	PriorityQueue<datos, greater<datos>> queue;

	// n = numero de casos, k = numero de nodos de la cola de prioridad
	// O(n * log k)
	for (int i = nCasos; i > 0; i--) { // n vueltas segun el numero de casos
		cin >> tipo;
		if (tipo == "A") {
			cout << queue.top().nombre << '\n';
			queue.pop(); // O(log k)
		}
		else if (tipo == "I") {
			cin >> d.nombre >> d.gravedad;
			d.prioridad = i;
			queue.push(d); // O(log k)
		}
	}

	cout << "---\n";
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