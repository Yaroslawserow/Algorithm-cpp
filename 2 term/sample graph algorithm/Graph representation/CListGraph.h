#pragma once

#include "IGRAPH.h"
#include <iostream>
#include <fstream>
#include <vector>

class CListGraph : public IGRAPH
{
public:
	explicit CListGraph(int _verticescount);
	virtual void AddEdge(int from, int out) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
	virtual void GetNextVertices(int vertex, std::vector <int>& vertices) const override;
	virtual void GetPrevVertices(int vertex, std::vector <int>& vertices) const override;
	void Override(IGRAPH* Gr);
private:
	int verticescount;
	std::vector < std::vector <int>> in;
	std::vector < std::vector <int>> out;
};