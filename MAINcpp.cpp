
#pragma once
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"
#include <vector>
#include <algorithm>
#include <cstring>

void make_graph(int type, int N)
{
	switch (type)
	{
	case 1:
	{
		CListGraph Gr(N);
		break;
	}
	case 2:
	{
		CMATRIXGRAPH Gr(N);
		break;
	}
	case 3:
	{
		SetGraph Gr(N);
		break;
	}
	case 4:
	{
		CARCGRAPH Gr(N);
		break;
	}
	default:
		break;
	}
}
int main()
{
	int n = 6;
	int type = 1;
	make_graph(type, n);
	return 0;
}