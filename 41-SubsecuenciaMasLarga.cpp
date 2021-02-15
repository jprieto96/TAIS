#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

int sol(const std::string & a, const std::string & b, const int & i, const int & j,
	std::vector<std::vector<int>> & matriz)
{
	if (matriz[i][j] != -1)
	{
		return matriz[i][j];
	}
	else
	{
		if (i == a.size() || j == b.size())
		{
			matriz[i][j] = 0;
		}
		else if (a[i] == b[j])
		{
			matriz[i][j] = 1 + sol(a, b, i + 1, j + 1, matriz);
		}
		else
		{
			matriz[i][j] = std::max(sol(a, b, i + 1, j, matriz),
				sol(a, b, i, j + 1, matriz));
		}
		return matriz[i][j];
	}
}

bool resuelveCaso()
{
	std::string a, b;
	if (!(std::cin >> a >> b))
		return false;

	std::vector<std::vector<int>> matriz(a.size() + 1, std::vector<int>(b.size() + 1, -1));
	int l = sol(a, b, 0, 0, matriz);

	std::string s;
	int i = 0, j = 0;
	while(i < a.size() && j < b.size())
	{
		if (a[i] == b[j])
		{
			s.push_back(a[i]);
			i++;
			j++;
		}
		else
		{
			if (matriz[i][j + 1] == matriz[i][j])
			{
				j++;
			}
			else if(matriz[i + 1][j] == matriz[i][j])
			{
				i++;
			}
		}
	}

	std::cout << s << '\n';

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