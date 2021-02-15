#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

struct UCMregister {
	int order; // To know when its his turn
	int id;
	int period;
};

bool operator<(UCMregister const& a, UCMregister const& b) {
	return b.order < a.order || (a.order == b.order && b.id < a.id);
}

bool resuelveCaso() {
	int nUsers, id, period, k;
	cin >> nUsers;
	if (nUsers == 0) return false;

	priority_queue<UCMregister> queue;
	for (int i = 0; i < nUsers; i++) {
		cin >> id >> period;
		queue.push({ period, id, period });
	}

	cin >> k;
	while (k) {
		UCMregister act = queue.top();
		queue.pop();
		cout << act.id << '\n';
		act.order += act.period;
		queue.push(act);
		--k;
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