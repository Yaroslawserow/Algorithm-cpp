#pragma once
#include <iostream>
#include <fstream>
#include <vector>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to)  = 0;
	virtual int  VerticesCount() const = 0;
	virtual void GetNextVertices(int vertex, std::vector <int>& vertices) const = 0;
	virtual void GetPrevVertices(int vertex, std::vector <int>& vertices) const = 0;
};