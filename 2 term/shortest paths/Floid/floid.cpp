#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to, int weight) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void Floyd() = 0;
};

class CMATRIXGRAPH : public IGRAPH
{
public:
	explicit CMATRIXGRAPH(int _verticescount);
	virtual void AddEdge(int from, int out, int weight) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
	virtual void Floyd() override;
private:
	int verticescount;
	int** MATRIX;
};

CMATRIXGRAPH::CMATRIXGRAPH(int _verticescount) :
	verticescount(_verticescount)
{
	MATRIX = new int* [verticescount];
	for (int i = 0; i < verticescount; i++)
		MATRIX[i] = new int[verticescount];
}

void CMATRIXGRAPH::AddEdge(int from, int to, int weight)
{
	MATRIX[from][to] = weight;
}

void CMATRIXGRAPH::Floyd()
{
	for (int k = 0; k < verticescount; k++)
		for (int i = 0; i < verticescount; i++)
			for (int j = 0; j < verticescount; j++)
				MATRIX[i][j] = std::min(MATRIX[i][j], MATRIX[i][k] + MATRIX[k][j]);
	for (int i = 0; i < verticescount; i++)
	{
		for (int j = 0; j < verticescount; j++)
			std::cout << MATRIX[i][j] << ' ';
		std::cout << '\n';
	}
}
int main()
{
	freopen("floyd.in", "r", stdin);
	freopen("floyd.out", "w", stdout);
	int N;
	std::cin >> N;
	CMATRIXGRAPH Graph(N);
	int x;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			std::cin >> x;
			Graph.AddEdge(i, j, x);
		}
	Graph.Floyd();
	return 0;
}