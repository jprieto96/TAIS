#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

bool resuelveCaso() {
	int n;
	long num;
	cin >> n;
	if (n == 0) return false;

	priority_queue<long, vector<long>, greater<long>> queue;
	for (int i = 0; i < n; i++) {
		cin >> num;
		queue.push(num);
	}
	
	long sol = 0;

	while (queue.size() > 1) {
		long act = queue.top();
		queue.pop();
		act += queue.top();
		queue.pop();
		queue.push(act);
		sol += act;
	}
	
	cout << sol << '\n';
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