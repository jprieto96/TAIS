#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

class Sol {

private:
	int n;
	int k;
	vector<bool> visitados;
	vector<int> dist;

	void bfs(unordered_map<int, int> const& g, int origen) {
		queue<int> q;
		visitados[origen] = true;
		dist[origen] = 0;
		q.push(origen);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int i = 1; i <= k; i++) {
				int w = v + i;
				if (g.count(w)) {
					w = g.at(w);
				}
				if (w <= n * n) {
					if (!visitados[w]) {
						visitados[w] = true;
						dist[w] = dist[v] + 1;
						q.push(w);
					}
				}
			}
		}
	}

public:
	Sol(const std::unordered_map<int, int>& g, const int& N, const int& K)
		: n(N), k(K), visitados(N* N + 1, false), dist(N* N + 1) 
	{
		visitados[0] = true;
		bfs(g, 1);
	}

	int solu() const { return dist[n * n]; }

};

bool resuelveCaso()
{
	int n, k, s, e;
	cin >> n >> k >> s >> e;
	if (n == 0 && k == 0 && s == 0 && e == 0)
		return false;

	// debería ser un mapa
	std::unordered_map<int, int> grafo;
	for (int i = 0; i < s + e; i++) {
		int a, b;
		cin >> a >> b;
		grafo[a] = b;
	}

	Sol sol(grafo, n, k);
	cout << sol.solu() << '\n';

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}