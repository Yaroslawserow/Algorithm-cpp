#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>

using namespace std;

namespace {
	struct vertex {
		int next_vert[200], move[200];
		bool isLeaf;
		char c;
		int suffLink, parent, goodsuffLink;
		std::vector <int> patern_number;
	};
	class Aho_Corasick {
	private:
		template <typename T>
		using vector = std::vector<T>;
		using string = std::string;
		std::vector <vertex> bor;
		int input;
		vector <int> count;
		vector <int> start;
		int sz;
		vertex make_bohr_vrtx(int p, char ch);
		void add_string_to_bor(const string& str, const int l);
		int get_link(int vertex);
		int get_move(int vertex, char ch);
		int get_goodsuffLink(int v);
		void check(int cur, int x);
	public:
		vector <int> answer(const string& text);
		Aho_Corasick(const string& mask);
	};

	Aho_Corasick::Aho_Corasick(const string& mask) {
		bor.push_back(make_bohr_vrtx(-1, '$'));
		int l = 0;
		sz = mask.size() - 1;
		input = 0;
		for (size_t i = 0; i < mask.size() - 1; ++i) {
			if ((mask[i] != '?') && (mask[i + 1] == '?')) {
				add_string_to_bor(mask.substr(l, i - l + 1), l);
			}
			if ((mask[i] == '?') && (mask[i + 1] != '?')) {
				l = i + 1;
			}
		}
	}

	vertex Aho_Corasick::make_bohr_vrtx(int p, char ch) {
		vertex v;
		memset(v.next_vert, 255, sizeof v.next_vert);
		memset(v.move, 255, sizeof v.move);
		v.isLeaf = false;
		v.suffLink = -1;
		v.parent = p;
		v.c = ch;
		v.goodsuffLink = -1;
		return v;
	}

	void Aho_Corasick::add_string_to_bor(const string& str, const int l) {
		int v = 0;
		for (size_t i = 0; i < str.length(); ++i) {
			char ch = str[i];
			if (bor[v].next_vert[ch] == -1) {
				bor.push_back(make_bohr_vrtx(v, ch));
				bor[v].next_vert[ch] = bor.size() - 1;
			}
			v = bor[v].next_vert[ch];
		}
		bor[v].isLeaf = true;
		bor[v].patern_number.push_back(l + str.length());
		input++;
	}

	int Aho_Corasick::get_link(int v) {
		if (bor[v].suffLink == -1) {
			if (v == 0 || bor[v].parent == 0) {
				bor[v].suffLink = 0;
			}
			else {
				bor[v].suffLink = get_move(get_link(bor[v].parent), bor[v].c);
			}
		}
		return bor[v].suffLink;
	}

	int Aho_Corasick::get_move(int v, char ch) {
		if (bor[v].move[ch] == -1) {
			if (bor[v].next_vert[ch] != -1) {
				bor[v].move[ch] = bor[v].next_vert[ch];
			}
			else {
				if (v == 0) {
					bor[v].move[ch] = 0;
				}
				else {
					bor[v].move[ch] = get_move(get_link(v), ch);
				}
			}
		}
		return bor[v].move[ch];
	}

	int Aho_Corasick::get_goodsuffLink(int v) {
		if (bor[v].goodsuffLink == -1) {
			int u = get_link(v);
			if (bor[u].isLeaf) {
				bor[v].goodsuffLink = u;
			}
			else {
				if (u == 0) {
					bor[v].goodsuffLink = 0;
				}
				else {
					bor[v].goodsuffLink = get_goodsuffLink(u);
				}

			}
		}
		return bor[v].goodsuffLink;
	}

	void Aho_Corasick::check(int v, int x) {
		int i = v;
		while (i != 0) {
			if (bor[i].isLeaf) {
				for (size_t j = 0; j < bor[i].patern_number.size(); ++j) {
					int cur = bor[i].patern_number[j];
					if (cur <= x) {
						start[x - cur]++;
					}
				}
			}
			i = get_goodsuffLink(i);
		}
		return;
	}

	std::vector <int> Aho_Corasick::answer(const string& text) {
		start.resize(text.length());
		vector <int> ans;
		int u = 0;
		for (size_t i = 0; i < text.length(); ++i) {
			u = get_move(u, text[i]);
			check(u, i + 1);
		}
		for (size_t i = 0; i < start.size() - sz + 1; ++i) {
			if (start[i] == input) {
				ans.push_back(i);
			}
		}
		return ans;
	}
}

int main() {
	std::string a, b;
	std::cin >> a >> b;
	if (a.size() > b.size()) {
		return 0;
	}
	std::vector <int> answer1;
	Aho_Corasick zzz(a + "?");
	answer1 = zzz.answer(b);
	for (size_t i = 0; i < answer1.size(); ++i) {
		std::cout << answer1[i] << ' ';
	}
	return 0;
}