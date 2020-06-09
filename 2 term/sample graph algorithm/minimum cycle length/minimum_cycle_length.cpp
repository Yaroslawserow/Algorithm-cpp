#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void BFS(int vertex) = 0;
	virtual void print() const = 0;
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
	virtual void BFS(int vertex) override;
	virtual void print() const override;
	int cycle;
private:
	int verticescount;
	std::vector < std::vector <int>> out;
};

CListGraph::CListGraph(int _verticescount) :
	verticescount(_verticescount),
	out(verticescount),
	cycle(0)
{
}

void CListGraph::AddEdge(int from, int to)
{
	if (from == to)
		cycle = 1;
	else
		if (std::find(out[from].begin(), out[from].end(), to) != out[from].end())
			cycle = 2;
		else
		{
			out[from].push_back(to);
			out[to].push_back(from);
		}
}

void CListGraph::BFS(int vertex)
{
	std::queue <int> Q;
	Q.push(vertex);
	int* distance;
	int* pred;
	pred = new int[verticescount];
	distance = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		distance[i] = 0;
	pred[vertex] = -1;
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int i = 0; i < out[v].size(); i++)
		{
			int to = out[v][i];
			if (distance[to] == 0 && to != vertex)
			{
				Q.push(to);
				pred[to] = v;
				distance[to] = distance[v] + 1;
			}
			else
				if (pred[v] != to)
				{
					if (cycle == 0)
					{
						cycle = distance[v] + distance[to] + 1;
					}
					else
						if (distance[v] + distance[to] + 1 < cycle)
						{
							cycle = distance[v] + distance[to] + 1;
						}
					delete(pred);
					delete(distance);
					return;
				}
		}
	}
	delete(pred);
	delete(distance);
}

void CListGraph::print() const
{
	if (cycle == 0)
		std::cout << -1;
	else
		std::cout << cycle;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	CListGraph gr(n);
	int x, y;
	for (int i = 0; i < m; i++)
	{
		std::cin >> x >> y;
		gr.AddEdge(x, y);
	}
	for (int i = 0; i < n; i++)
		gr.BFS(i);
	gr.print();
}