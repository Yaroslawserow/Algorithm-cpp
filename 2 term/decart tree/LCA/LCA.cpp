#include <vector>
#include <iostream>
#include <fstream>


long long n, l, m;
std::vector < std::vector<long long> > g;
std::vector<long long> tin, tout;
long long timer;
std::vector < std::vector<long long> > up;

void dfs(long long v, long long p = 0)
{
	tin[v] = ++timer;
	up[v][0] = p;
	for (long long i = 1; i <= l; i++)
		up[v][i] = up[up[v][i - 1]][i - 1];
	for (size_t i = 0; i < g[v].size(); i++) {
		long long to = g[v][i];
		if (to != p)
			dfs(to, v);
	}
	tout[v] = ++timer;
}

bool upper(long long a, long long b)
{
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

long long lca(long long a, long long b)
{
	if (upper(a, b))  return a;
	if (upper(b, a))  return b;
	for (long long i = l; i >= 0; --i)
		if (!upper(up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main()
{
	std::cin >> n >> m;
	g.resize(n);
	long long x;
	for (long long i = 1; i < n; i++)
	{
		std::cin >> x;
		g[x].push_back(i);
	}
	tin.resize(n), tout.resize(n), up.resize(n);
	l = 1;
	while ((1 << l) <= n)
		++l;
	for (long long i = 0; i < n; ++i)
		up[i].resize(l + 1);
	dfs(0);
	long long y, z;
	long long a1, a2;
	std::cin >> a1 >> a2;
	std::cin >> x >> y >> z;
	long long answer = 0;
	long long v = lca(a1, a2);
	answer += v;
	long long lol1 = a2;
	long long lol2 = a1;
	for (int i = 2; i <= m; i++)
	{
		a1 = (x * lol2 + y * lol1 + z) % n;
		a2 = (x * lol1 + y * a1 + z) % n;
		int res = lca((a1 + v) % n, a2);
		answer += res;
		lol1 = a2;
		lol2 = a1;
		v = res;
	}
	std::cout << answer;
}