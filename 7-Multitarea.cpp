#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "PriorityQueue.h"

struct intervalo {
	int ini, fin, periodo;
};

bool operator<(intervalo const & i1, intervalo const & i2) {
	return i1.ini < i2.ini;
}

bool seSolapan(intervalo const& i1, intervalo const& i2) {
	if (i1.ini < i2.ini)
		return i1.fin > i2.ini;
	else if (i1.ini == i2.ini)
		return true;
	else
		return seSolapan(i2, i1);
}

bool resuelveCaso() {
	int nUnicas, mPeriodicas, tMinutos;
	bool ok = false;
	cin >> nUnicas >> mPeriodicas >> tMinutos;
	if (!cin) return false;

	intervalo in;
	PriorityQueue<intervalo> queue;
	for (int i = 0; i < nUnicas; i++) {
		cin >> in.ini >> in.fin;
		in.periodo = -1;
		queue.push(in);
	}

	for (int i = 0; i < mPeriodicas; i++) {
		cin >> in.ini >> in.fin >> in.periodo;
		queue.push(in);
	}

	intervalo i1 = queue.top();
	queue.pop();
	if (i1.periodo != -1) {
		queue.push({ i1.ini + i1.periodo, i1.fin + i1.periodo, i1.periodo });
	}
	int tiempo = i1.ini;
	while (tiempo < tMinutos && !ok && !queue.empty()) {
		if (queue.top().ini == tiempo) {
			intervalo i2 = queue.top();
			queue.pop();
			if (seSolapan(i1, i2)) {
				ok = true;
			}
			else {
				i1 = i2;
				if (i1.periodo != -1) {
					queue.push({ i1.ini + i1.periodo, i1.fin + i1.periodo, i1.periodo });
				}
			}
		}
		if (!queue.empty())
			tiempo = queue.top().ini;
	}

	cout << (ok ? "SI\n" : "NO\n");
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