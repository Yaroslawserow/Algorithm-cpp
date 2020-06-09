#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include<set>
#include<map>
#include <cstdio>
#include <cstdlib>
#include<algorithm>

#define INRANGE(i, a, b) (i >= a && i < b)

using namespace std;
ofstream out("puzzle.out");
ifstream inp("puzzle.in");

class SlidingBlock
{
public:
	vector < int > disc;
	int n;
	int cost;
	int empty_slot;
	vector< string > record_move;
	SlidingBlock();
	SlidingBlock(int);
	SlidingBlock(vector < int >, vector < string >);
	vector < string > getMove();
	void makeMove(const string move = string());
	bool solved();
	vector < SlidingBlock > branches();
	void setCost();
	//void print();
	void readBlock();
	bool check();
	bool operator< (const SlidingBlock&) const;
	bool operator> (const SlidingBlock&) const;
};

SlidingBlock::SlidingBlock()
{
	SlidingBlock(3);
}

SlidingBlock::SlidingBlock(int size)
{
	n = size;
}

void SlidingBlock::readBlock()
{
	int temp;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			
			inp >> temp;
			disc.push_back(temp);
		}
	}
	int pos = std::abs(std::distance(find(disc.begin(), disc.end(), 0), disc.begin()));
	empty_slot = pos;
	setCost();
}

SlidingBlock::SlidingBlock(vector < int > node, vector < string > moves)
{
	disc.clear();
	n = (int)sqrt(node.size());
	for (int i = 0; i < (int)node.size(); ++i)
	{
		disc.push_back(node[i]);
		if (node[i] == 0)
			empty_slot = i;
	}

	for (int i = 0; i < moves.size(); i++)
		record_move.push_back(moves[i]);
	setCost();
}

void SlidingBlock::setCost()
{
	int h1 = 0, h2 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int val = disc[n * i + j];
			if (val  - 1!= n * i + j && val != 0)
			{
				h1++;
				int exp_pos_x = (val - 1) / n;
				int exp_pos_y = (val - 1) % n;
				h2 += abs(i - exp_pos_x) + abs(j - exp_pos_y);
			}
		}
	}
	cost = max(h1, h2) + this -> record_move.size();
}

vector < string > SlidingBlock::getMove()
{
	vector < string > movements;
	if (empty_slot / n < n - 1)
		movements.push_back("D");
	if (empty_slot % n < n - 1)
		movements.push_back("R");
	if (empty_slot / n > 0)
		movements.push_back("U");
	if (empty_slot % n > 0)
		movements.push_back("L");
	return movements;
}

void SlidingBlock::makeMove(string move)
{
	if (move.empty())
	{
		vector < string > moves = getMove();
		int rand_point_index = rand() % moves.size();
		makeMove(moves[rand_point_index]);
	}
	else
	{
		record_move.push_back(move);
		int temp = empty_slot;
		if (move.compare("U") == 0)
			empty_slot -= n;
		if (move.compare("D") == 0)
			empty_slot += n;
		if (move.compare("L") == 0)
			empty_slot -= 1;
		if (move.compare("R") == 0)
			empty_slot += 1;
		swap(disc[temp], disc[empty_slot]);
	}
	setCost();
}

bool SlidingBlock::solved()
{
	
	bool answer = true;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (disc[n * i + j] == 0 && (n * i + j) != disc.size() - 1)
				answer = false;
			if(disc[n * i + j] != 0)
				answer &= disc[n * i + j] == (n * i + j + 1);
		}
	}
	return answer;
}

vector < SlidingBlock > SlidingBlock::branches()
{
	vector < string > moves = getMove();
	vector < SlidingBlock > valid_branches;
	for (int i = 0; i < (int)moves.size(); ++i)
	{
		valid_branches.push_back(SlidingBlock(disc, record_move));
		valid_branches[i].makeMove(moves[i]);
	}
	return valid_branches;
}

/*void SlidingBlock::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << disc[n * i + j] << " ";
		}
		cout << endl;
	}
}*/

bool SlidingBlock::operator< (const SlidingBlock& node) const
{
	for (int i = 0; i < (int)node.disc.size(); i++)
	{
		if (node.disc[i] < this -> disc[i])
		{
			return true;
		}
		else if (node.disc[i] > this -> disc[i])
		{
			return false;
		}
		else
		{
			continue;
		}
	}
	return false;
}

bool SlidingBlock::operator> (const SlidingBlock& node) const
{
	for (int i = 0; i < (int)node.disc.size(); i++)
	{
		if (node.disc[i] > this->disc[i])
		{
			return true;
		}
		else if (node.disc[i] < this->disc[i])
		{
			return false;
		}
		else
		{
			continue;
		}
	}
	return false;
}

bool SlidingBlock::check()
{
	int inv = 0;
	for (int i = 0; i < 9; ++i)
		if (disc[i])
			for (int j = 0; j<i; ++j)
				if (disc[j] > disc[i])
					++inv;
	if (inv % 2 == 0)
		return true;
	else
		return false;
}

struct OrderByCost
{
	bool operator() (const SlidingBlock &a, const SlidingBlock &b) const
	{
		return a.cost >= b.cost;
	}
};

class Search
{
public:
	SlidingBlock start;
	priority_queue< SlidingBlock, vector < SlidingBlock >, OrderByCost > pq;
	set< SlidingBlock > explored;
	vector < SlidingBlock > expanded;

	Search(int n)
	{
		start = SlidingBlock(n);
		start.readBlock();
		if (start.check())
			searchAndPrint();
		else
		{
			//ofstream out("puzzle.out");
			out << -1;
		}
	}

	void searchAndPrint()
	{
		pushNode(start);
		SlidingBlock node = SlidingBlock(start.disc, start.record_move);
		setExplored(node);
		int lollol = 0;
		while (!node.solved())
		{
			node = getNextNode();
			expanded.push_back(node);
			vector < SlidingBlock > valid_branches = node.branches();
			for (int i = 0; i < (int)valid_branches.size(); i++)
			{
				if (!isExplored(valid_branches[i]))
				{
					pushNode(valid_branches[i]);
					setExplored(node);
				}
			}
		}

		out << node.record_move.size() << endl; 
		for (auto i = node.record_move.begin(); i != node.record_move.end(); i++)
			out << (*i);
	}

	void pushNode(SlidingBlock node)
	{
		pq.push(node);
	}

	void setExplored(SlidingBlock node)
	{
		explored.insert(node);
	}

	bool isExplored(SlidingBlock node)
	{
		return explored.count(node) > 0;
	}

	SlidingBlock getNextNode()
	{
		SlidingBlock node = pq.top();
		pq.pop();
		return node;
	}
};

int main()
{
	Search lol(3);
}