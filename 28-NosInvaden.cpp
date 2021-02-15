#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

int resolver(vector<int> const& ataques, vector<int> const& defensas) {
	int num = 0;
	int j = 0;
	for (int i = 0; i < (int)ataques.size() && j < (int)defensas.size(); i++) {
		if (ataques[i] <= defensas[j]) {
			++num;
		}
		else {
			--i;
		}
		++j;
	}
	return num;
}

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!cin) return false;

	vector<int> ataques;
	int aux;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		ataques.push_back(aux);
	}

	vector<int> defensas;
	for (int i = 0; i < N; i++) {
		cin >> aux;
		defensas.push_back(aux);
	}

	sort(ataques.begin(), ataques.end());
	sort(defensas.begin(), defensas.end());

	cout << resolver(ataques, defensas) << '\n';

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