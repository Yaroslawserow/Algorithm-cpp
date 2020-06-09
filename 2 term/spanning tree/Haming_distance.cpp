#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <algorithm>
#include <map>

struct IGRAPH
{
	virtual ~IGRAPH() {};
	virtual void AddEdge(int from, int to, int weight) = 0;
	virtual int  VerticesCount() const = 0;
	virtual void print() = 0;
};

class CMATRIXGRAPH : public IGRAPH
{
public:
	explicit CMATRIXGRAPH(int _verticescount);
	virtual void AddEdge(int from, int out, int weight) override;
	virtual int VerticesCount() const override
	{
		return verticescount;
	}
	virtual void print() override;
protected:
	int verticescount;
	int** MATRIX;
};

CMATRIXGRAPH::CMATRIXGRAPH(int _verticescount) :
	verticescount(_verticescount)
{
	MATRIX = new int* [verticescount];
	for (int i = 0; i < verticescount; i++)
		MATRIX[i] = new int[verticescount];
	for (int i = 0; i < _verticescount; i++)
	{
		for (int j = 0; j < _verticescount; j++)
			MATRIX[i][j] = 0;
	}
}

void CMATRIXGRAPH::AddEdge(int from, int to, int weight)
{
	MATRIX[from][to] += weight;
}

void CMATRIXGRAPH::print()
{
	for (int i = 0; i < verticescount; i++)
	{
		for (int j = 0; j < verticescount; j++)
			std::cout << MATRIX[i][j] << ' ';
		std::cout << '\n';
	}

}

class DINIC : public CMATRIXGRAPH
{
public:
	explicit DINIC(int vertex, int s1, int t1) : CMATRIXGRAPH(vertex)
	{
		flow = new int* [vertex];
		for (int i = 0; i < vertex; i++)
			flow[i] = new int[vertex];
		for (int i = 0; i < vertex; i++)
		{
			for (int j = 0; j < vertex; j++)
			{
				flow[i][j] = 0;
			}
		}
		distance.reserve(vertex);
		ptr.reserve(vertex);
		s = s1;
		t = t1;
	}
	bool BFS();
	int DFS(int v, int flow);
	std::vector<int> findMaxFlow();
private:
	int** flow;
	int s, t;
	std::vector <int> distance, ptr;
	std::queue <int> q;
};

bool DINIC::BFS()
{
	int INF = 10e9;
	distance.assign(verticescount, INF);
	q.push(s);
	distance[s] = 0;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < verticescount; i++)
		{
			if (distance[i] == INF && flow[v][i] < MATRIX[v][i])
			{
				distance[i] = distance[v] + 1;
				q.push(i);
			}
		}
	}
	return distance[t] != INF;
}
int DINIC::DFS(int v, int f)
{
	if (!f)
		return 0;
	if (v == t)
		return f;
	for (int& i = ptr[v]; i < verticescount; i++)
	{
		if (distance[i] != distance[v] + 1)
			continue;
		int pushed = DFS(i, std::min(f, MATRIX[v][i] - flow[v][i]));
		if (pushed)
		{
			flow[v][i] += pushed;
			flow[i][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}

std::vector <int> DINIC::findMaxFlow()
{
	int Maxflow = 0;
	while (BFS())
	{
		ptr.assign(verticescount, 0);
		while (int pushed = DFS(s, 10e9))
		{
			Maxflow += pushed;
		}
	}
	return distance;
}

int main()
{
	std::string s, p;
	std::cin >> s >> p;
	std::map <int, int> inputs;
	std::map <int, int> inputp;
	std::map <int, std::pair<int, int>> answer;
	int k = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '?')
		{
			inputs.insert(std::pair<int, int>(i, k));
			answer.insert(std::pair<int, std::pair<int, int>>(k, std::make_pair(i, 0)));
			k++;

		}
	}
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i] == '?')
		{
			inputp.insert(std::pair<int, int>(i, k));
			answer.insert(std::pair<int, std::pair<int, int>>(k, std::make_pair(i, 1)));
			k++;
		}
	}
	DINIC gr(k + 2, k + 1, k);
	int l = 0;
	while (p.size() != s.size())
	{
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i] == '?')
			{
				if (s[i] == '?')
				{
					int x = (*inputs.find(i)).second;
					int y = (*inputp.find(i - l)).second;
					gr.AddEdge(x, y, 1);
					gr.AddEdge(y, x, 1);
				}
				if (s[i] == '1')
				{
					int y = (*inputp.find(i - l)).second;
					gr.AddEdge(k, y, 1);
					gr.AddEdge(y, k, 1);
				}
				if (s[i] == '0')
				{
					int y = (*inputp.find(i - l)).second;
					gr.AddEdge(k + 1, y, 1);
					gr.AddEdge(y, k + 1, 1);
				}
			}
			if (p[i] != '?')
			{
				if (s[i] == '?')
				{
					if (p[i] == '0')
					{
						int y = (*inputs.find(i)).second;
						gr.AddEdge(k + 1, y, 1);
						gr.AddEdge(y, k + 1, 1);
					}
					if (p[i] == '1')
					{
						int y = (*inputs.find(i)).second;
						gr.AddEdge(k, y, 1);
						gr.AddEdge(y, k, 1);
					}
				}
			}
		}
		p = 'l' + p;
		l++;
	}
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i] == '?')
		{
			if (s[i] == '?')
			{
				int x = (*inputs.find(i)).second;
				int y = (*inputp.find(i - l)).second;
				gr.AddEdge(x, y, 1);
				gr.AddEdge(y, x, 1);
			}
			if (s[i] == '1')
			{
				int y = (*inputp.find(i - l)).second;
				gr.AddEdge(k, y, 1);
				gr.AddEdge(y, k, 1);
			}
			if (s[i] == '0')
			{
				int y = (*inputp.find(i - l)).second;
				gr.AddEdge(k + 1, y, 1);
				gr.AddEdge(y, k + 1, 1);
			}
		}
		if (p[i] != '?')
		{
			if (s[i] == '?')
			{
				if (p[i] == '0')
				{
					int y = (*inputs.find(i)).second;
					gr.AddEdge(k + 1, y, 1);
					gr.AddEdge(y, k + 1, 1);
				}
				if (p[i] == '1')
				{
					int y = (*inputs.find(i)).second;
					gr.AddEdge(k, y, 1);
					gr.AddEdge(y, k, 1);
				}
			}
		}
	}
	if (l > 0)
		p = p.substr(l, p.size() - 1);
	std::vector <int> d = gr.findMaxFlow();
	int INF = 10e9;
	for (int i = 0; i < d.size() - 2; i++)
	{
		if (d[i] != INF)
		{
			int x = ((*answer.find(i)).second).second;
			int y = ((*answer.find(i)).second).first;
			if (x == 0)
				s[y] = '0';
			if (x == 1)
				p[y] = '0';
		}
		if (d[i] == INF)
		{
			int x = ((*answer.find(i)).second).second;
			int y = ((*answer.find(i)).second).first;
			if (x == 0)
				s[y] = '1';
			if (x == 1)
				p[y] = '1';
		}
	}
	int ans = 0;
	while (p.size() != s.size())
	{
		for (int i = 0; i < p.size(); i++)
		{
			if (p[i] != s[i] && p[i] != 'l')
				ans++;
		}
		p = 'l' + p;
	}
	for (int i = 0; i < p.size(); i++)
	{
		if (p[i] != s[i] && p[i] != 'l')
			ans++;
	}
	if (l > 0)
		p = p.substr(l, p.size() - 1);
	std::cout << ans << '\n';
	std::cout << s << '\n' << p;
}