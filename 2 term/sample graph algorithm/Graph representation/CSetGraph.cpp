#pragma once
#include "CSetGraph.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

SetGraph::SetGraph(int _verticescount) :
	verticescount(_verticescount),
	Setin(verticescount),
	Setout(verticescount)
{
}

void SetGraph::AddEdge(int from, int to)
{
	Setin[to].insert(from);
	Setout[from].insert(to);
}

void SetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	for (int i = 0; i < verticescount; i++)
		if (std::find(Setout[vertex].begin(), Setout[vertex].end(), vertex) != Setout[vertex].end())
			vertices.push_back(i);
}
void SetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	for (int i = 0; i < verticescount; i++)
		if (std::find(Setin[vertex].begin(), Setin[vertex].end(), vertex) != Setin[vertex].end())
			vertices.push_back(i);
}
void SetGraph::Override(IGRAPH* Gr)
{
	std::vector <int> Next;
	for (int i = 0; i < verticescount; i++)
	{
		GetNextVertices(i, Next);
		for (int j = 0; j < Next.size(); j++)
			Setin[i].insert(Next[j]);
	}
	std::vector <int> Prev;
	for (int i = 0; i < verticescount; i++)
	{
		GetPrevVertices(i, Prev);
		for (int j = 0; j < Prev.size(); j++)
			Setout[i].insert(Prev[j]);
	}
}