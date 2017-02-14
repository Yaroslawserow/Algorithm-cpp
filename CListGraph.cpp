#pragma once
#include "CListGraph.h"
#include <vector>
#include <algorithm>

CListGraph::CListGraph(int _verticescount) :
	verticescount(_verticescount),
	in( verticescount),
	out( verticescount)
{
}

void CListGraph::AddEdge(int from, int to)
{
	in[to].push_back(from);
	out[from].push_back(to);
}

void CListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	vertices = out[vertex];
}
void CListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	vertices = in[vertex];
}
void CListGraph::Override(IGRAPH* Gr)
{
	std::vector <int> Next;
	for (int i = 0; i < verticescount; i++)
	{
		GetNextVertices(i, Next);
		out[i] = Next;
	}
	std::vector <int> Prev;
	for (int i = 0; i < verticescount; i++)
	{
		GetPrevVertices(i, Prev);
		in[i] = Prev;
	}
}

	