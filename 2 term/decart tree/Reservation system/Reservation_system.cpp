#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Tree
{
public:
	Tree(int n);
	void build(std::vector <int>& a, int v, int L, int R);
	int get_max(int v, int tL, int tR, int l, int r);
	void print();
	void update_sum(int v, int tL, int tR, int l, int r, int add);
	void push(int v, int tL, int tR);
private:
	int n;
	std::vector <std::pair<int, int> > tree;
};

Tree::Tree(int n)
{
	tree.resize(4 * n);
}

void Tree::print()
{
	for (int i = 0; i < tree.size(); i++)
		std::cout << tree[i].first << ' ';
}

void Tree::build(std::vector <int>& a, int v, int L, int R)
{
	if (L == R)
	{
		tree[v].first = a[L];
		tree[v].second = 0;
	}
	else
	{
		int tm = (L + R) / 2;
		build(a, v * 2, L, tm);
		build(a, v * 2 + 1, tm + 1, R);
		tree[v].first = std::max(tree[v * 2].first, tree[v * 2 + 1].first);
		tree[v].second = 0;
	}

}

int Tree::get_max(int v, int tL, int tR, int l, int r)
{
	int INF = -10e9;
	if (l > r)
		return INF;
	if (l == tL && r == tR)
		return tree[v].first;
	int tm = (tL + tR) / 2;
	push(v, tL, tR);
	return std::max(get_max(v * 2, tL, tm, l, std::min(r, tm)),
		get_max(v * 2 + 1, tm + 1, tR, std::max(l, tm + 1), r));
}

void Tree::push(int v, int tL, int tR)
{
	tree[2 * v].second = tree[v].second + tree[2 * v].second;
	tree[2 * v + 1].second = tree[2 * v + 1].second + tree[v].second;
	tree[2 * v].first = tree[v].second + tree[2 * v].first;
	tree[2 * v + 1].first = tree[2 * v + 1].first + tree[v].second;
	tree[v].second = 0;
}

void Tree::update_sum(int v, int tL, int tR, int l, int r, int add) {
	if (l > r)
		return;
	if (l == tL && tR == r)
	{
		tree[v].second += add;
		tree[v].first += add;
	}
	else
	{
		push(v, tL, tR);
		int tm = (tL + tR) / 2;
		update_sum(v * 2, tL, tm, l, std::min(r, tm), add);
		update_sum(v * 2 + 1, tm + 1, tR, std::max(l, tm + 1), r, add);
		tree[v].first = std::max(tree[2 * v].first, tree[2 * v + 1].first);
	}

}

int main()
{
	std::vector <int> input;
	int n, m, count;
	std::cin >> n;
	n--;
	for (int i = 0; i < n; i++)
	{
		int x;
		std::cin >> x;
		input.push_back(x);
	}
	Tree T(n);
	T.build(input, 1, 0, n - 1);
	std::cin >> count;
	std::cin >> m;
	std::vector <int> answer;
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		std::cin >> x >> y >> z;
		y--;
		if (T.get_max(1, 0, n - 1, x, y) + z <= count)
		{
			T.update_sum(1, 0, n - 1, x, y, z);
		}
		else
			answer.push_back(i);
	}
	for (int i = 0; i < answer.size(); i++)
		std::cout << answer[i] << ' ';
}