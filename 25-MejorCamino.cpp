#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

#include "GrafoValorado.h"
#include "IndexPQ.h"

struct par {
	int coste;
	int dist;
};

bool operator<(const par& p1, const par& p2) {
	return p1.coste < p2.coste || (p1.coste == p2.coste && p1.dist < p2.dist);
}

class BFS {
private:

	// primer elemento del par -> coste
	// segundo elemento del par -> distancia
	vector<int> dist;
	vector<bool> visit;
	int _origen;
	int _destino;

	void bfs(GrafoValorado<int> const& g) {
		queue<int> q;
		dist[_origen] = 0;
		visit[_origen] = true;
		q.push(_origen);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto& a : g.ady(v)) {
				int w = a.otro(v);
				if (!visit[w]) {
					dist[w] = dist[v] + 1;
					visit[w] = true;
					q.push(w);
				}
			}
		}
	}

public:
	BFS(GrafoValorado<int> const& g, int origen, int destino) : dist(g.V()), visit(g.V(), false), _destino(destino - 1), _origen(origen - 1) {
		bfs(g);
	}

	int distanciaDestino() const {
		return dist[_destino];
	}

};

class Dijkstra {
private:

	// primer elemento del par -> coste
	// segundo elemento del par -> distancia
	vector<par> dist;
	IndexPQ<par> pq;
	vector<bool> visit;
	int _origen;
	int _destino;

	void relajar(Arista<int> const& a, int v, int w) {
		if (!visit[w]) {
			if (dist[w].coste > dist[v].coste + a.valor()) {
				dist[w].coste = dist[v].coste + a.valor();
				dist[w].dist = dist[v].dist + 1;
				pq.update(w, dist[w]);
			}
			else if (dist[w].coste == dist[v].coste + a.valor()) {
				if (dist[w].dist > dist[v].dist + 1) {
					dist[w].dist = dist[v].dist + 1;
					pq.update(w, dist[w]);
				}
			}
		}
	}

public:
	Dijkstra(GrafoValorado<int> const& g, int origen, int destino) : dist(g.V(), { numeric_limits<int>::max(), 0 }), pq(g.V()), visit(g.V(), false), _origen(origen - 1), _destino(destino - 1) {
		dist[_origen] = { 0, 0 };
		pq.push(_origen, dist[0]);
		while (!pq.empty()) {
			int v = pq.top().elem; pq.pop();
			if (!visit[v]) {
				visit[v] = true;
				for (auto& a : g.ady(v)) {
					int w = a.otro(v);
					relajar(a, v, w);
				}
			}
		}
	}

	par caminoMinimo() const {
		return dist[_destino];
	}

};

bool resuelveCaso() {
	GrafoValorado<int> g(cin, 1);
	if (!cin) return false;

	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int origen, destino;
		cin >> origen >> destino;
		BFS b(g, origen, destino);
		Dijkstra d(g, origen, destino);
		auto s = d.caminoMinimo();
		if (s.coste == numeric_limits<int>::max())
			cout << "SIN CAMINO\n";
		else {
			bool ok = true;
			if (s.dist > b.distanciaDestino()) 
				ok = false;
			cout << s.coste << " ";
			if (ok) cout << "SI\n";
			else cout << "NO\n";
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