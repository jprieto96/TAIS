#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

struct Objeto {
	double puntuacion, duracion;

	bool operator<(const Objeto& otro) const { return ((double)otro.puntuacion) / otro.duracion < puntuacion / duracion; }
};

struct Nodo {
	// 0 -> se coge cancion en la cara 1
	// 1 -> se coge cancion en la cara 2
	// 2 -> no se coge la cancion
	std::vector<int> sol;
	int k;

	double espacioCara1, espacioCara2;
	double puntuacion, puntuacionEst;

	bool operator<(const Nodo& otro) const { return otro.puntuacionEst > puntuacionEst; }
};

double voraz(const std::vector<Objeto>& obj, const Nodo& x, const int& m) {
	double hueco = 2 * m - (x.espacioCara1 + x.espacioCara2), estimacion = x.puntuacion;
	int i = x.k + 1;

	while (i < obj.size() && obj[i].duracion <= hueco) {
		hueco -= obj[i].duracion;
		estimacion += obj[i].puntuacion;
		i++;
	}

	if (i < obj.size()) {
		estimacion += (hueco / obj[i].duracion) * obj[i].puntuacion;
	}

	return estimacion;
}

void mochila(const std::vector<Objeto>& obj, std::vector<int>& solMejor,
	int& beneficioMejor, const int& m) {
	int n = obj.size();
	Nodo y{ std::vector<int>(n), -1, 0, 0 };
	y.puntuacionEst = voraz(obj, y, m);
	std::priority_queue<Nodo> cola;
	cola.push(y);
	beneficioMejor = -1;

	while (!cola.empty() && cola.top().puntuacionEst > beneficioMejor) {
		y = cola.top(); cola.pop();
		Nodo x{ y };
		x.k++;

		// coger en cara 1
		if (y.espacioCara1 + obj[x.k].duracion <= m){
			x.sol[x.k] = 0;
			x.espacioCara1 = y.espacioCara1 + obj[x.k].duracion;
			x.puntuacion = y.puntuacion + obj[x.k].puntuacion;
			x.puntuacionEst = y.puntuacionEst;
			if (x.k == n - 1) {
				solMejor = x.sol;
				beneficioMejor = x.puntuacion;
			}
			else {
				cola.push(x);
			}
		}

		x.espacioCara1 = y.espacioCara1;
		x.espacioCara2 = y.espacioCara2;
		x.puntuacion = y.puntuacion;
		x.puntuacionEst = y.puntuacionEst;
		// coger en cara 2
		if (y.espacioCara2 + obj[x.k].duracion <= m) {
			x.sol[x.k] = 1;
			x.espacioCara2 = y.espacioCara2 + obj[x.k].duracion;
			x.puntuacion = y.puntuacion + obj[x.k].puntuacion;
			x.puntuacionEst = y.puntuacionEst;
			if (x.k == n - 1) {
				solMejor = x.sol;
				beneficioMejor = x.puntuacion;
			}
			else {
				cola.push(x);
			}
		}
		
		x.espacioCara1 = y.espacioCara1;
		x.espacioCara2 = y.espacioCara2;
		x.puntuacion = y.puntuacion;
		x.puntuacionEst = y.puntuacionEst;
		// no coger cancion en ninguna de las caras
		x.sol[x.k] = 2;
		x.puntuacion = y.puntuacion;
		x.puntuacionEst = voraz(obj, x, m);
		if (x.puntuacionEst > beneficioMejor) {
			if (x.k == n - 1) {
				solMejor = x.sol;
				beneficioMejor = x.puntuacion;
			}
			else {
				cola.push(x);
			}
		}

	}
}

bool resuelveCaso() {
	int n;
	std::cin >> n;
	if (n == 0)
		return false;

	int m;
	std::cin >> m;
	std::vector<Objeto> v(n);
	for (auto& e : v)
	{
		double dur, pun;
		std::cin >> dur >> pun;
		e.duracion = dur;
		e.puntuacion = pun;
	}

	std::sort(v.begin(), v.end());

	std::vector<int> sol(n);
	int solMejor;
	mochila(v, sol, solMejor, m);

	std::cout << solMejor << '\n';

	return true;
}

int main()
{
#ifndef DOMJUDGE
	std::ifstream in("datos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
	while (resuelveCaso());
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}