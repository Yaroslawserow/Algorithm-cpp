#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>


struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void BFS(int vertexstart, int vertexfinish) = 0;
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
	virtual void BFS(int vertexstart, int vertexfinish) override;
private:
	int verticescount;
	std::vector < std::vector <int>> out;
};

CListGraph::CListGraph(int _verticescount) :
	verticescount(_verticescount),
	out(verticescount)
{
}

void CListGraph::AddEdge(int from, int to)
{
	if (from != to)
	{
		out[from].push_back(to);
		out[to].push_back(from);
	}
}

void CListGraph::BFS(int vertexstart, int vertexfinish)
{
	int ans = 0;
	std::queue <int> Q;
	Q.push(vertexstart);
	int* distance;
	distance = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		distance[i] = 0;
	distance[vertexstart] = 0;
	int* result;
	result = new int[verticescount];
	for (int i = 0; i < verticescount; i++)
		result[i] = 0;
	result[vertexstart] = 1;
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int i = 0; i < out[v].size(); i++)
		{
			int to = out[v][i];
			if (distance[to] == 0)
			{
				Q.push(to);
				distance[to] = distance[v] + 1;
			}
			if (distance[v] + 1 == distance[to])
				result[to] += result[v];
		}
	}
	delete(distance);
	std::cout << result[vertexfinish];
	delete(result);
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	CListGraph Gr(n);
	int x, y;
	for (int i = 0; i < m; i++)
	{
		std::cin >> x >> y;
		Gr.AddEdge(x, y);
	}
	int start, finish;
	std::cin >> start >> finish;
	Gr.BFS(start, finish);
	return(0);
}