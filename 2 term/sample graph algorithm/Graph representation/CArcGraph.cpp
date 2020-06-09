#pragma once
#include "CArcGraph.h"
#include <vector>
#include <algorithm>

CARCGRAPH::CARCGRAPH(int _verticescount) :
	verticescount(_verticescount),
	Arc(verticescount)
{
}

void CARCGRAPH::AddEdge(int from, int to)
{
	std::pair <int, int> p;
	Arc.push_back(p);
}

void CARCGRAPH::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	for (size_t i = 0; i < Arc.size(); i++)
		if (Arc[i].first == vertex)
			vertices.push_back(Arc[i].second);
}
void CARCGRAPH::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	for (size_t i = 0; i < Arc.size(); i++)
		if (Arc[i].second == vertex)
			vertices.push_back(Arc[i].first);
}
void CARCGRAPH::Override(IGRAPH* Gr)
{
	std::vector <int> Next;
	for (int i = 0; i < verticescount; i++)
	{
		GetNextVertices(i, Next);
		for (int j = 0; j < Next.size(); j++)
			Arc.push_back(std::make_pair(i, Next[j]));
	}
}