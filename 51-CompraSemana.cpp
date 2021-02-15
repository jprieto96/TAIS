// Jose Ramon Prieto del Prado
// TAIS62

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct Nodo {
	std::vector<int> sol;
	std::vector<int> marcas;
	int k;
	int coste;
	int costeEst;

	bool operator<(Nodo const& otro) const {
		return otro.costeEst < costeEst;
	}
};

int estimacion(vector<vector<int>> const& v, Nodo const& x) {
	int costeEst = x.coste;
	int m = v.size();
	int n = v[0].size();
	for (int j = x.k + 1; j < n; j++) {
		int mini = v[0][j];
		for (int i = 0; i < m; i++) {
			if (x.marcas[i] < 3 && v[i][j] < mini) {
				mini = v[i][j];
			}
		}
		costeEst += mini;
	}
	
	return costeEst;
}

// función que resuelve el problema
void calcularSolMejor(vector<vector<int>> const& v, int& costeMinimo) {
	int m = v.size();
	int n = v[0].size();
	Nodo y{ vector<int>(n, -1), vector<int> (m, 0), -1, 0, 0 };
	y.costeEst = estimacion(v, y);
	priority_queue<Nodo> pq;
	pq.push(y);
	costeMinimo = numeric_limits<int>::max();

	while (!pq.empty() && pq.top().costeEst < costeMinimo) {
		y = pq.top(); pq.pop();
		Nodo x{ y };
		x.k++;
		for (int i = 0; i < m; i++) {
			if (x.marcas[i] < 3) {
				x.sol[x.k] = i;
				x.coste = y.coste + v[i][x.k];
				x.costeEst = estimacion(v, x);
				if (x.costeEst < costeMinimo) {
					if (x.k == n - 1) {
						costeMinimo = x.coste;
					}
					else {
						++x.marcas[i];
						pq.push(x);
						--x.marcas[i];
					}
				}
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int M, N;
	cin >> M >> N;
	
	vector<vector<int>> v(M);
	int aux = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> aux;
			v[i].push_back(aux);
		}
	}

	int costeMinimo = numeric_limits<int>::max();
	calcularSolMejor(v, costeMinimo);
	cout << costeMinimo << '\n';
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	//save old buf and redirect std::cin to datos.txt:
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

	int nCasos;
	cin >> nCasos;
	for (int i = 0; i < nCasos; i++) {
		resuelveCaso();
	}

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}