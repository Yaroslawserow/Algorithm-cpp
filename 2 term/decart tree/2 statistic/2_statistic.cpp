#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class SparceTable
{
public:
	SparceTable(std::vector <int>& a, int n);
	int min_poss(int L, int R, std::vector <int>& a);
private:
	std::vector <int> logTable;
	std::vector <std::vector<std::pair<int, int>>> RMQ;
};

SparceTable::SparceTable(std::vector <int>& a, int n)
{
	logTable.push_back(0);
	logTable.push_back(0);
	for (int i = 2; i < n + 1; i++)
		logTable.push_back(logTable[i >> 1] + 1);
	RMQ.resize(logTable[n] + 1);
	for (int i = 0; i < logTable[n] + 1; i++)
		RMQ[i].resize(n);
	int INF = 1e9;
	for (int i = 0; i < n; i++)
		RMQ[0][i] = std::make_pair(a[i], INF);
	for (int k = 1; (1 << k) < n; k++)
	{
		for (int i = 0; i + (1 << k) <= n; i++)
		{
			std::pair<int, int> x = RMQ[k - 1][i];

			std::pair<int, int> y = RMQ[k - 1][i + (1 << k - 1)];
			std::pair<int, int> ans;
			if (x.first < y.first)
			{
				ans.first = x.first;
				if (x.second < y.first)
					ans.second = x.second;
				else
					ans.second = y.first;
			}
			if (x.first > y.first)
			{
				ans.first = y.first;
				if (x.first > y.second)
					ans.second = y.second;
				else
					ans.second = x.first;
			}
			if (x.first == y.first)
			{
				ans.first = x.first;
				ans.second = std::min(x.second, y.second);
			}
			RMQ[k][i] = ans;
		}
	}
}

int SparceTable::min_poss(int L, int R, std::vector <int>& a)
{
	int k = logTable[R - L];
	std::pair<int, int> x = RMQ[k][L];
	std::pair<int, int> y = RMQ[k][R - (1 << k) + 1];
	std::pair<int, int> ans;
	if (x.first < y.first)
	{
		ans.first = x.first;
		if (x.second < y.first)
			ans.second = x.second;
		else
			ans.second = y.first;
	}
	if (x.first > y.first)
	{
		ans.first = y.first;
		if (x.first > y.second)
			ans.second = y.second;
		else
			ans.second = x.first;
	}
	if (x.first == y.first)
	{
		ans.first = x.first;
		ans.second = std::min(x.second, y.second);
	}
	return ans.second;
}

int main()
{
	int n, m;
	std::vector <int> a;
	std::cin >> n >> m;
	int x;
	for (int i = 0; i < n; i++)
	{
		std::cin >> x;
		a.push_back(x);
	}
	SparceTable ans(a, n);
	for (int i = 0; i < m; i++)
	{
		int x, y;
		std::cin >> x >> y;
		std::cout << ans.min_poss(x - 1, y - 1, a) << '\n';
	}
}