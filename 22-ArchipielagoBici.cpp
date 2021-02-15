#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <functional>
using namespace std;

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

template <typename Valor>
class ARMArchipielago {
private:

	vector<Arista<Valor>> _ARM;
	Valor coste;
	int V;

public:

	ARMArchipielago(GrafoValorado<int> const& g) : coste(0), V(g.V()) {
		PriorityQueue<Arista<Valor>> pq(g.aristas());
		ConjuntosDisjuntos cjto(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjto.unidos(v, w)) {
				cjto.unir(v, w);
				_ARM.push_back(a);
				coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
	}

	Valor costeARM() const {
		return coste;
	}

	vector<Arista<Valor>> const& ARM() {
		return _ARM;
	}

};

bool resuelveCaso() {
	GrafoValorado<int> g(cin, 1);
	if (!cin) return false;

	ARMArchipielago<int> a(g);

	if (a.ARM().size() != g.V() - 1) cout << "No hay puentes suficientes\n";
	else cout << a.costeARM() << '\n';

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