#pragma once
#include "IGRAPH.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

class SetGraph : public IGRAPH
{
public:
	explicit SetGraph(int _verticescount);
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
	std::vector < std::unordered_set <int>> Setin;
	std::vector < std::unordered_set <int>> Setout;
	
};