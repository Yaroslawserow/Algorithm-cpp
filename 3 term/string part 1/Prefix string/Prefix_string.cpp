#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace {
	class make_string {
	public:
		template <typename T>
		using vector = std::vector<T>;
		using string = std::string;
		const vector <int> pi;
		string answer;
		vector <bool> lol;
		char new_character(const int x) {
			for (int i = 0; i < lol.size(); ++i) {
				lol[i] = false;
			}
			int j = x;
			if (pi[j - 1] == 0) {
				char t = (answer[pi[j - 1]] + 1);
				return t;
			}
			else {
				while (pi[j - 1] != 0) {
					lol[answer[pi[j - 1]] - 'a'] = true;
					j = pi[j - 1];
				}
				lol[0] = true;
				for (int i = 0; i < lol.size(); ++i) {
					if (lol[i] == false) {
						char t = i + 'a';
						return t;
					}
				}
			}
		}
	public:
		make_string(const vector <int>& s)
			: pi(s)
			, lol(30)
		{
			answer += 'a';
			for (int i = 1; i < pi.size(); ++i) {
				if (pi[i] == 0) {
					answer += new_character(i);
				}
				else {
					answer += (answer[pi[i] - 1]);
				}
			}
		}

	};
}

int main() {
	int a;
	std::vector<int> s;
	while (std::cin >> a) {
		s.push_back(a);
	}
	make_string str(s);
	std::cout << str.answer << "\n";
}