#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <queue>
using namespace std;

#include "Grafo.h"


class Noticias {
private:

	vector<bool> visitado;
	vector<int> sol;

	void bfs(const Grafo& g, const int& origen)
	{
		int s = 1;
		vector<int> visitados;
		visitados.push_back(origen);

		queue<int> q;
		visitado[origen] = true;
		q.push(origen);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (const auto& w : g.ady(v)) {
				if (!visitado[w]) {
					visitado[w] = true;
					q.push(w);
					s++;
					visitados.push_back(w);
				}
			}
		}

		for (const auto& e : visitados) {
			sol[e] = s;
		}
	}

public:

	Noticias(Grafo const& g) : sol(g.V()), visitado(g.V(), false) {
		for (int i = 0; i < g.V(); i++) {
			if (!visitado[i])
				bfs(g, i);
		}
	}

	vector<int> expansion() const {
		return sol;
	}
};

bool resuelveCaso() {
	int N, M;
	cin >> N >> M;
	if (!cin) return false;

	int nUsuarios;
	Grafo g(N);
	for (int i = 0; i < M; i++) {
		int tam, v;
		cin >> tam;

		if (tam != 0)
			cin >> v;

		if (tam > 1) {
			for (int i = 0; i < tam - 1; i++) {
				int w;
				cin >> w;
				g.ponArista(v - 1, w - 1);
				v = w;
			}
		}
	}

	Noticias n(g);
	for (auto const& i : n.expansion()) {
		cout << i << " ";
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