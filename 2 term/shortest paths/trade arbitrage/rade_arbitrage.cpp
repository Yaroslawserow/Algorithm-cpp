#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to, double weight) = 0;
	virtual int  VerticesCount() const = 0;
};

class CMATRIXGRAPH : public IGRAPH
{
public:
	explicit CMATRIXGRAPH(int _verticescount);
	virtual void AddEdge(int from, int out, double weight) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
protected:
	int verticescount;
	double **MATRIX;
};

CMATRIXGRAPH::CMATRIXGRAPH(int _verticescount) :
	verticescount(_verticescount)
{
	MATRIX = new double *[verticescount];
	for (int i = 0; i < verticescount; i++)
		MATRIX[i] = new double[verticescount];
}

void CMATRIXGRAPH::AddEdge(int from, int to, double weight)
{
	MATRIX[from][to] = weight;
}

class Counselor : public CMATRIXGRAPH
{
public:
	explicit Counselor(int vertex) : CMATRIXGRAPH(vertex) {};
	void Floyd();
	void check();
};

void Counselor::Floyd()
{

	for (int k = 0; k < verticescount; k++)
		for (int i = 0; i < verticescount; i++)
			for (int j = 0; j < verticescount; j++)
				//if (MATRIX[i][j] != -1 && MATRIX[i][k] != -1 && MATRIX[k][j] != -1)
				MATRIX[i][j] = std::max(MATRIX[i][j], MATRIX[i][k] * MATRIX[k][j]);
	/*for (int i = 0; i < verticescount; i++)
	{
		for (int j = 0; j < verticescount; j++)
			std::cout << MATRIX[i][j] << ' ';
		std::cout << '\n';
	}*/
}

void Counselor::check()
{
	double eps = 1e-7;
	for (int i = 0; i < verticescount; i++)
		if (MATRIX[i][i] > 1.0)
		{
			std::cout << "YES";
			return;
		}
	std::cout << "NO";
	return;

}

int main()
{
	int N;
	std::cin >> N;
	Counselor Graph(N);
	double x;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			if (i == j)
				Graph.AddEdge(i, j, 1.0);
			else
			{
				std::cin >> x;
				Graph.AddEdge(i, j, x);
			}
		}
	Graph.Floyd();
	Graph.check();
	return 0;
}