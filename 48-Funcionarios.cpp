// Jose Ramon Prieto del Prado
// E58

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

struct datosEntrada {
	std::vector<std::vector<int>> tiempos;
	int numFuncionarios, numTareas;
};

struct Nodo {
	std::vector<int> sol;
	std::vector<bool> marcas;
	int k;
	int duracion;
	int duracionEst;

	bool operator<(Nodo const& otro) const {
		return otro.duracionEst < duracionEst;
	}
};

int estimacion(datosEntrada const& d, Nodo const & x, int n) {
	int est = x.duracion;
	for (int i = x.k + 1; i < n; i++) {
		int mini = d.tiempos[i][0];
		int m = 0;
		for (int j = 0; j < n; j++) {
			if (!x.marcas[j] && d.tiempos[i][j] < mini) {
				mini = d.tiempos[i][j];
				m = j;
			}
		}
		est += d.tiempos[i][m];
	}
	return est;
}

// función que resuelve el problema
void calcularSolMejor(datosEntrada const& d, int& duracionMinima) {
	int n = d.numFuncionarios;
	Nodo y{ std::vector<int>(n, -1), std::vector<bool>(n, false), -1, 0, 0 };
	y.duracionEst = estimacion(d, y, n);
	std::priority_queue<Nodo> pq;
	pq.push(y);
	duracionMinima = std::numeric_limits<int>::max();

	while (!pq.empty() && pq.top().duracionEst < duracionMinima) {
		y = pq.top(); pq.pop();
		Nodo x{ y };
		x.k++;
		for (int i = 0; i < n; i++) {
			if (!x.marcas[i]) {
				x.sol[x.k] = i;
				x.duracion = y.duracion + d.tiempos[x.k][i];
				x.duracionEst = estimacion(d, x, n);

				if (x.duracionEst < duracionMinima) { // es solucion mejor
					if (x.k == n - 1) { // es solucion
						duracionMinima = x.duracion;
					}
					else {
						x.marcas[i] = true;
						pq.push(x);
						x.marcas[i] = false;
					}
				}
			}
		}
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	datosEntrada datos;
	int aux = 0;
	std::cin >> datos.numFuncionarios;
	if (datos.numFuncionarios == 0)
		return false;
	datos.numTareas = datos.numFuncionarios;
	datos.tiempos.resize(datos.numFuncionarios);
	std::vector<bool> marcas(datos.numFuncionarios);

	for (int i = 0; i < datos.numFuncionarios; i++) {
		for (int j = 0; j < datos.numTareas; j++) {
			std::cin >> aux;
			datos.tiempos[i].push_back(aux);
		}
	}

	int duracionMinima = std::numeric_limits<int>::max();
	calcularSolMejor(datos, duracionMinima);
	std::cout << duracionMinima << "\n";
	return true;
}

int main() {
	// Para la entrada por fichero.
	// Comentar para acepta el reto
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	//save old buf and redirect std::cin to datos.txt:
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 

	while (resuelveCaso());

	// Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}