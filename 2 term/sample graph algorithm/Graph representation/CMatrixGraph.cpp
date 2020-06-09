#pragma once
#include "CMatrixGraph.h"
#include <algorithm>
#include <vector>

CMATRIXGRAPH::CMATRIXGRAPH(int _verticescount) :
	verticescount(_verticescount)
{
	MATRIX = new int *[verticescount];
	for (int i = 0; i < verticescount; i++)
		MATRIX[i] = new int[verticescount];
}

void CMATRIXGRAPH::AddEdge(int from, int to)
{
	MATRIX[from][to] = 1;
}
void CMATRIXGRAPH::GetNextVertices(int vertex, std::vector <int>& vertices) const
{
	for (int i = 0; i < verticescount; i++)
		if (MATRIX[vertex][i] == 1)
			vertices.push_back(i);
}
void CMATRIXGRAPH::GetPrevVertices(int vertex, std::vector <int>& vertices) const
{
	for (int i = 0; i < verticescount; i++)
		if (MATRIX[i][vertex] == 1)
			vertices.push_back(i);
}

void CMATRIXGRAPH::Override(IGRAPH* Gr)
{
	std::vector <int> Next;
	for (int i = 0; i < verticescount; i++)
	{
		GetNextVertices(i, Next);
		for (int j = 0; j < Next.size(); j++)
			MATRIX[i][Next[j]] = 1;
	}
}