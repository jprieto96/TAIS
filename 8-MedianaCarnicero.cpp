#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "PriorityQueue.h"

class ColasMediana {

	PriorityQueue<int> der;
	PriorityQueue<int, greater<int>> izq;
	int med;
	int nElems;

public:

	ColasMediana() : nElems(0) {}

	void insertar(int x) {
		if (nElems == 0) {
			med = x;
		}
		else {
			if (x < med) {
				izq.push(x);
			}
			else {
				der.push(x);
			}
			calcularNuevaMediana();
		}
		++nElems;
	}

	bool vacia() {
		return nElems == 0;
	}

	int mediana() {
		return med;
	}

	void eliminarMediana() {
		if (der.size() > izq.size()) {
			med = der.top();
			der.pop();
		}
		else {
			if (izq.empty()) med = -1;
			else {
				med = izq.top();
				izq.pop();
			}
		}
		--nElems;
	}
private:
	void calcularNuevaMediana() {
		if (izq.size() > der.size()) {
			der.push(med);
			med = izq.top();
			izq.pop();
		}
		else if (der.size() > izq.size() + 1) {
			izq.push(med);
			med = der.top();
			der.pop();
		}
	}

};

bool resuelveCaso() {
	int n, x;
	cin >> n;
	if (!cin) return false;
	ColasMediana pq;
	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x == 0) {
			if (pq.vacia()) cout << "ECSA ";
			else {
				int mediana = pq.mediana();
				cout << mediana << " ";
				pq.eliminarMediana();
			}
		}
		else {
			pq.insertar(x);
		}
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