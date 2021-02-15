#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "GrafoValorado.h"
#include "IndexPQ.h"

class CaminoCole {
private:

	// primer elemento del par -> distancia
	// segundo elemento del par -> numero de veces que se llega hasta él
	vector<pair<int, int>> dist; 
	IndexPQ<int> pq;
	vector<bool> visit;
	int destino;
	int nCaminos;

	void relajar(Arista<int> const& a, int v, int w) {
		if (!visit[w]) {
			if (dist[w].first > dist[v].first + a.valor()) {
				dist[w].first = dist[v].first + a.valor();
				dist[w].second = dist[v].second;
				pq.update(w, dist[w].first);
			}
			else if (dist[w].first == dist[v].first + a.valor())
				dist[w].second += dist[v].second;
		}
	}

public:
	CaminoCole(GrafoValorado<int> const& g) : dist(g.V(), { numeric_limits<int>::max(), 0 }), pq(g.V()), visit(g.V(), false), destino(g.V() - 1), nCaminos(0) {
		dist[0] = { 0, 1 };
		pq.push(0, 0);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			if (!visit[v]) {
				visit[v] = true;
				for (auto& a : g.ady(v)) {
					int w = a.otro(v);
					relajar(a, v, w);
				}
				if (v == destino) break;
			}
		}
	}

	int caminos() const {
		return dist[destino].second;
	}

};

bool resuelveCaso() {
	GrafoValorado<int> g(cin, 1);
	if (!cin) return false;

	CaminoCole c(g);

	cout << c.caminos() << '\n';

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