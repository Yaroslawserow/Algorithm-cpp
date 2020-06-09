#include <iostream>
#include <vector>
#include <string>

namespace {
	class OccurenceFinder {
	private:
		template <typename T>
		using vector = std::vector<T>;
		using string = std::string;

		const string s;
		vector<int> prefs;
		int cur;
		bool is_same(int spos, char c) const {
			return (spos < s.length() && s[spos] == c);
		}

		int find_value(char curSymbol, int last) {
			int cur = last;
			while ((cur > 0) && !is_same(cur, curSymbol)) {
				cur = prefs[cur - 1];
			}

			if (is_same(cur, curSymbol)) {
				cur++;
			}
			return cur;
		}

	public:
		OccurenceFinder(const string& s)
			: s(s)
			, prefs(s.length())
			, cur(0)
		{
			vector <int> res;
			prefs[0] = 0;
			for (int i = 1; i < s.length(); i++) {
				prefs[i] = find_value(s[i], prefs[i - 1]);
			}
		}

		bool operator()(char c) {
			return (cur = find_value(c, cur)) == s.length();
		}
	};
}


int main() {
	std::vector <int > answer;
	std::string s;
	std::cin >> s;
	char t;
	int ans = 0;
	OccurenceFinder o(s);
	t = getchar();
	std::cout << t;
	if (o(t)) {
		std::cout << ans - s.length() << ' ';
	}
	while (t != -1) {
		++ans;
		t = getchar();
		if (o(t)) std::cout << ans - s.length() << ' ';
	}
}