#include iostream
#include fstream
#include vector
#include algorithm
#include queue
#include set

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to, int price) = 0;
	virtual int  VerticesCount() const = 0;
};

class CListGraph  public IGRAPH
{
public
	explicit CListGraph(int _verticescount);
	virtual void AddEdge(int from, int outm, int price) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
protected
	int verticescount;
	stdvector  stdvector stdpairint, int out;
};

CListGraphCListGraph(int _verticescount) 
	verticescount(_verticescount),
	out(verticescount)
{
}

void CListGraphAddEdge(int from, int to, int price)
{
	out[from].push_back(stdmake_pair(to, price));
	out[to].push_back(stdmake_pair(from, price));
}

class Djiecstra  public CListGraph
{
public
	explicit Djiecstra(int vertex)  CListGraph(vertex) 
	{
		distance.reserve(vertex);
		distance.assign(vertex, INF);
	};
	void Djiecstraset(int start, int finish);
private
	const int INF = 1e9;
	stdvector int distance;
	stdset stdpair int, int heap;
};

void DjiecstraDjiecstraset(int start, int finish)
{
	distance[start] = 0;
	heap.insert(stdmake_pair(distance[start], start));
	while (!heap.empty())
	{
		
		int v = heap.begin() - second;
		heap.erase(heap.begin());
		for (int i = 0; i  out[v].size(); i++)
		{
			int to = out[v][i].first,
				len = out[v][i].second;
			if (distance[v] + len  distance[to]) 
			{
				heap.erase(stdmake_pair(distance[to], to));
				distance[to] = distance[v] + len;
				heap.insert(stdmake_pair(distance[to], to));
			}
		}
	}
	stdcout  distance[finish];
}

int main()
{
	int N, M;
	stdcin  N  M;
	Djiecstra gr(N);
	for (int i = 0; i  M; i++)
	{
		int x, y, z;
		stdcin  x  y  z;
		gr.AddEdge(x, y, z);
	}
	int st, fn;
	stdcin  st  fn;
	gr.Djiecstraset(st, fn);
}