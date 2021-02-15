#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "TreeSet_AVL.h"

bool resuelveCaso() {
	int n, m, num;
	Set<int> set;
	cin >> n;
	if (n == 0) return false;

	for (int i = 0; i < n; i++) {
		cin >> num;
		set.insert(num);
	}

	cin >> m;
	for (size_t i = 0; i < m; i++) {
		cin >> num;
		try {
			cout << set.kesimo(num) << '\n';
		}
		catch (domain_error const& e) {
			cout << "??\n";
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