#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

int agujerosManguera(vector<int> const& posiciones, int L) {
	int parches = 0;
	int largo = posiciones[0] + L;
	++parches;
	for (int i = 1; i < (int) posiciones.size(); i++) {
		if (largo < posiciones[i]) {
			largo = posiciones[i] + L;
			++parches;
		}
	}
	return parches;
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin) return false;

	int L;
	cin >> L;

	vector<int> posiciones;
	for (int i = 0; i < N; i++) {
		int p;
		cin >> p;
		posiciones.push_back(p);
	}

	cout << agujerosManguera(posiciones, L) << '\n';

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