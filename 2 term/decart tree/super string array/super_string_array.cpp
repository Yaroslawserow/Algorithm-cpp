#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct Node
{
	int y;
	int size;
	std::string value;
	Node* left, * right;
};

class Decart_tree
{
public:

	Decart_tree(std::string value);
	Node* new_node(std::string value);
	int get_sz(Node* tree);
	void upd_sz(Node* tree);
	Node* merge(Node* tree1, Node* tree2);
	void split(Node* tree, int x, Node*& tree1, Node*& tree2);
	Node* add(Node* tree, int pos, std::string value);
	std::string get_value(Node* tree, int pos);
	Node* remove(Node* tree, int pos);
	void insert(int x, std::string s);
	void deleate(int x);
	std::string getAT(int x);
	//void print_tree(Node *t);
private:
	Node* global_tree;
};

Decart_tree::Decart_tree(std::string value)
{
	global_tree = new_node(value);
}
Node* Decart_tree::new_node(std::string value)
{
	Node* result = new Node;
	result->y = rand();
	result->size = 1;
	result->value = value;
	result->left = nullptr;
	result->right = nullptr;
	return result;
}

/*void Decart_tree::print_tree(Node *t)
{
	if (t == nullptr) { return; }
	print_tree(t->left);
	std::cout << t->value << " ";
	print_tree(t->right);
}*/

int Decart_tree::get_sz(Node* t)
{
	if (t == nullptr)
	{
		return 0;
	}
	return t->size;
}

void Decart_tree::upd_sz(Node* t)
{
	if (t == nullptr)
	{
		return;
	}
	t->size = 1 + get_sz(t->left) + get_sz(t->right);
}

Node* Decart_tree::merge(Node* t1, Node* t2)
{
	if (t1 == nullptr)
	{
		return t2;
	}
	if (t2 == nullptr)
	{
		return t1;
	}
	if (t1->y > t2->y)
	{
		t1->right = merge(t1->right, t2);
		upd_sz(t1);
		return t1;
	}
	else
	{
		t2->left = merge(t1, t2->left);
		upd_sz(t2);
		return t2;
	}
}

void Decart_tree::split(Node* t, int x, Node*& t1, Node*& t2)
{
	if (t == nullptr)
	{
		t1 = t2 = nullptr;
		return;
	}
	if (get_sz(t->left) < x)
	{
		split(t->right, x - get_sz(t->left) - 1, t->right, t2);
		t1 = t;
	}
	else
	{
		split(t->left, x, t1, t->left);
		t2 = t;
	}
	upd_sz(t);
}



Node* Decart_tree::add(Node* t, int pos, std::string val)
{
	Node* t1, * t2;
	split(t, pos, t1, t2);
	Node* new_tree = new_node(val);
	return merge(merge(t1, new_tree), t2);
}

Node* Decart_tree::remove(Node* t, int pos)
{
	Node* t1, * t2, * t3, * t4, * cur;
	cur = t;
	split(t, pos, t1, t2);
	split(t2, 1, t3, t4);
	t = merge(t1, t4);
	delete t3;
	return t;
}

std::string Decart_tree::get_value(Node* t, int pos)
{
	int my_idx = get_sz(t->left);
	if (pos < my_idx)
	{
		return get_value(t->left, pos);
	}
	else if (pos == my_idx)
	{
		return t->value;
	}
	else
	{
		return get_value(t->right, pos - my_idx - 1);
	}
}

void Decart_tree::insert(int x, std::string s)
{
	global_tree = add(global_tree, x, s);
}

void Decart_tree::deleate(int x)
{
	global_tree = remove(global_tree, x);
}

std::string Decart_tree::getAT(int x)
{
	return get_value(global_tree, x);
}

int main()
{
	int k;
	std::cin >> k;
	char c;
	int x;
	std::string s;
	std::cin >> c >> x >> s;
	Decart_tree t(s);
	for (int i = 0; i < k - 1; i++)
	{
		std::cin >> c;
		if (c == '+')
		{
			std::cin >> x >> s;
			t.insert(x, s);
		}
		if (c == '-')
		{
			std::cin >> x;
			t.deleate(x);
		}
		if (c == '?')
		{
			std::cin >> x;
			std::cout << t.getAT(x) << '\n';
		}
	}
}