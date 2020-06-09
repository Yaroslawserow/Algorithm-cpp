#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <vector>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void dfs(int x) = 0;
	virtual void dfs_rev(int x) = 0;
	virtual void DFS() = 0;
	virtual void DFS_rev() = 0;
	virtual void search() = 0;
	virtual void printanswer() = 0;
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
	virtual void dfs(int x) override;
	virtual void dfs_rev(int x) override;
	virtual void DFS() override;
	virtual void DFS_rev() override;
	virtual void search() override;
	virtual void printanswer() override;
private:
	int verticescount, cur;
	std::vector < std::vector <int>> out;
	std::vector < std::vector <int>> in;
	std::vector <int> q;
	int* vis;
	int* color;
	bool* ansin, * ansout;
};

CListGraph::CListGraph(int _verticescount) :
	verticescount(_verticescount),
	cur(0),
	in(verticescount),
	out(verticescount)
{
	vis = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		vis[i] = 0;
	color = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		color[i] = 0;
}

void CListGraph::AddEdge(int from, int to)
{
	out[from].push_back(to);
	in[to].push_back(from);
}

void CListGraph::DFS()
{
	for (int i = 0; i < verticescount; i++)
		if (!vis[i])
		{
			dfs(i);
		}
	delete(vis);
	//for (int i = 0; i < q.size(); i++)
	//std::cout << q[i];
}

void CListGraph::DFS_rev()
{
	for (int i = verticescount - 1; i >= 0; i--)
		if (!color[q[i]])
		{
			cur++;
			dfs_rev(q[i]);
		}
	//for (int i = 0; i < verticescount; i++)
	//std::cout << color[i] << ' ';
}

void CListGraph::dfs(int vertex)
{
	vis[vertex] = 1;
	for (int i = 0; i < out[vertex].size(); i++)
		if (!vis[out[vertex][i]])
			dfs(out[vertex][i]);
	q.push_back(vertex);
}

void CListGraph::dfs_rev(int vertex)
{
	color[vertex] = cur;
	for (int i = 0; i < in[vertex].size(); i++)
		if (!color[in[vertex][i]])
			dfs_rev(in[vertex][i]);
}

void CListGraph::search()
{
	ansin = new bool[cur + 1];
	for (int i = 0; i <= cur + 1; i++)
		ansin[i] = 0;
	ansout = new bool[cur + 1];
	for (int i = 0; i <= cur + 1; i++)
		ansout[i] = 0;
	for (int i = 0; i < verticescount; i++)
		for (int j = 0; j < out[i].size(); j++)
			if (color[i] != color[out[i][j]])
				ansout[color[i]] = ansin[color[out[i][j]]] = 1;
	delete(color);
}

void CListGraph::printanswer()
{
	int a = 0, b = 0;
	if (cur == 1)
	{
		std::cout << 0;
		return;
	}
	for (int i = 1; i <= cur; i++)
	{
		a += !ansout[i];
		b += !ansin[i];
	}

	std::cout << std::max(a, b);

}

int main()
{
	int n, m;
	int	x, y, a = 0, b = 0;
	std::cin >> n >> m;
	CListGraph GR(n);
	for (int i = 0; i < m; i++)
	{
		std::cin >> x >> y;
		x--;
		y--;
		GR.AddEdge(x, y);
	}
	GR.DFS();
	GR.DFS_rev();
	GR.search();
	GR.printanswer();
	return 0;
}