#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
#include <deque>
using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

class Navegando {
private:

	vector<int> espera;
	IndexPQ<int> pq;
	vector<int> _milisegundosCarga;
	int destino;

	void relajar(AristaDirigida<int> const& a) {
		int v = a.desde(), w = a.hasta();
		if (espera[w] > espera[v] + a.valor() + _milisegundosCarga[w]) {
			espera[w] = espera[v] + a.valor() + _milisegundosCarga[w];
			pq.update(w, espera[w]);
		}
	}

public:
	Navegando(DigrafoValorado<int> const& g, vector<int> milisegundosCarga) : espera(g.V(), numeric_limits<int>::max()), pq(g.V()), _milisegundosCarga(milisegundosCarga), destino(g.V() - 1) {
		espera[0] = milisegundosCarga[0];
		pq.push(0, milisegundosCarga[0]);
		bool salir = false;
		while (!pq.empty() && !salir) {
			int v = pq.top().elem; pq.pop();
			if (v == destino) salir = true;
			for (auto& a : g.ady(v)) {
				relajar(a);
			}
		}
	}

	int carga() const {
		return espera[destino];
	}

};

bool resuelveCaso() {
	int N;
	cin >> N;
	if (N == 0) return false;

	vector<int> milisegundos(N);
	for (int & m : milisegundos)
		cin >> m;

	int M;
	cin >> M;

	DigrafoValorado<int> g(N);
	for (int i = 0; i < M; i++) {
		int v, w, c;
		cin >> v >> w >> c;
		g.ponArista({ v - 1, w - 1, c });
	}

	Navegando n(g, milisegundos);

	int c = n.carga();
	if (c == numeric_limits<int>::max()) cout << "IMPOSIBLE\n";
	else cout << c << '\n';

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