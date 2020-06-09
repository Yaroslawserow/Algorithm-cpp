#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void dfs(int vertex) = 0;
	virtual bool check() = 0;

};

class CListGraph : public IGRAPH
{
public:
	explicit CListGraph(int _verticescount);
	virtual void AddEdge(int from, int out) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
	virtual void dfs(int vertex) override;
	virtual bool check()  override;
private:
	int verticescount;
	int* color;
	std::vector < std::vector <int>> out;
};

CListGraph::CListGraph(int _verticescount) :
	verticescount(_verticescount),
	out(verticescount)
{
	color = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		color[i] = 0;
}

void CListGraph::AddEdge(int from, int to)
{
	out[from].push_back(to);
	out[to].push_back(from);
}

void CListGraph::dfs(int vertex)
{
	color[vertex] = 1;
	for (int i = 0; i < out[vertex].size(); i++)
	{
		if (color[out[vertex][i]] == 0)
		{
			dfs(out[vertex][i]);
		}
	}
	color[vertex] = 2;
}

bool CListGraph::check()
{
	if (color[verticescount - 2] == color[verticescount - 1])
	{
		for (int i = 0; i < verticescount; i++)
			color[i] = 0;
		for (int i = 0; i < verticescount; i++)
			out[i].clear();
		return 0;
	}
	else
	{
		for (int i = 0; i < verticescount; i++)
			color[i] = 0;
		for (int i = 0; i < verticescount; i++)
			out[i].clear();
		return 1;
	}
}

int main()
{
	int n;
	double r, wL, wR;
	std::cin >> wL >> wR;
	std::cin >> r >> n;
	CListGraph GR(n + 2);
	double x, y;
	std::vector <std::pair <double, double>> point;
	for (int i = 0; i < n; i++)
	{
		std::cin >> x >> y;
		point.push_back(std::make_pair(x, y));
	}
	double answer;
	double e = 1e-7;
	bool v = true;
	double L = 0.0, R = 100000000, mid;
	while (v)
	{
		mid = (L + R) / 2;
		for (int i = 0; i < point.size(); i++)
			if (point[i].first - wL < r + mid)
			{
				GR.AddEdge(n, i);
			}
		for (int i = 0; i < point.size(); i++)
			for (int j = i; j < point.size(); j++)
				if (i != j)
				{
					if (sqrt((point[i].first - point[j].first) * (point[i].first - point[j].first) + (point[i].second - point[j].second) * (point[i].second - point[j].second)) < mid + r + r)
					{
						GR.AddEdge(i, j);
					}
				}
		for (int i = 0; i < point.size(); i++)
		{
			if (wR - point[i].first < r + mid)
			{
				GR.AddEdge(n + 1, i);
			}
		}
		//GR.print_Graph();
		//std::cout << '\n';
		GR.dfs(n);
		//std::cout << GR.check();
		//std::cout << GR.check(n) << '\n';
		if (GR.check() == 0)
		{
			R = mid;
		}
		else
		{
			L = mid;
		}
		if (std::abs(R - L) < 1e-7)
		{
			answer = mid;
			v = 0;
		}
	}
	answer = std::min(answer, wR - wL);
	std::cout << std::fixed << std::setprecision(3) << answer;
	return 0;
}