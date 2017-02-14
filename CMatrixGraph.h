#pragma once
#include "IGRAPH.h"
#include <iostream>
#include <vector>

class CMATRIXGRAPH : public IGRAPH
{
public:
	explicit CMATRIXGRAPH(int _verticescount);
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
	int **MATRIX;
};