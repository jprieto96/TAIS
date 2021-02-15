#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

std::pair<int, int> sol(const std::vector<std::vector<int>>& v, int N) {
	std::vector<int> juego(N);
	for (int i = 0; i < N; i++) {
		juego[i] = v[0][i];
	}

	for (int i = 1; i < N; i++) {
		int ant = juego[0];
		for (int j = 0; j < N; j++) {
			int actual = juego[j];
			if (j == 0) {
				juego[j] = std::max(juego[j], juego[j + 1]);
			}
			else if (j == N - 1) {
				juego[j] = std::max(juego[j], ant);
			}
			else {
				juego[j] = std::max(std::max(juego[j], juego[j + 1]), ant);
			}

			juego[j] += v[i][j];
			ant = actual;
		}
	}

	int c = 1, max = juego[0];
	for (int i = 1; i < N; i++) {
		if (juego[i] > max) {
			max = juego[i];
			c = i + 1;
		}
	}

	return { max, c };
}

bool resuelveCaso()
{
	int n;
	if (!(std::cin >> n))
		return false;

	std::vector<std::vector<int>> v(n, std::vector<int>(n));
	for (auto& f : v)
		for (auto& e : f)
			std::cin >> e;

	auto s = sol(v, n);
	std::cout << s.first << ' ' << s.second << '\n';

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