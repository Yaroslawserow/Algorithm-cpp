#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <stdio.h>

namespace {
	class search
	{
	private:
		int alphabet;
		std::vector <int> pref;
		std::vector <int> prefn;
		std::vector <int> lcp;
		std::vector <int> pos;
		void suffmas(std::string& s);
		void LCP(std::string& s);
	public:
		search(std::string& s);
		int answer(std::string& s);
	};
	search::search(std::string& s) {
		alphabet = 256;
		pref.resize(s.size());
		prefn.resize(s.size());
		lcp.resize(s.size());
		pos.resize(s.size());
		suffmas(s);
		LCP(s);
	}

	void search::suffmas(std::string& s) {
		int* cnt, * classes, * classesn;
		cnt = new int[s.size()];
		classes = new int[s.size()];
		classesn = new int[s.size()];
		memset(cnt, 0, alphabet * sizeof(int));
		for (int i = 0; i < s.size(); ++i)
			++cnt[s[i]];
		for (int i = 1; i < alphabet; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = 0; i < s.size(); ++i)
			pref[--cnt[s[i]]] = i;
		classes[pref[0]] = 0;
		int c = 1;
		for (int i = 1; i < s.size(); ++i) {
			if (s[pref[i]] != s[pref[i - 1]]) {
				++c;
			}
			classes[pref[i]] = c - 1;
		}

		for (int h = 0; (1 << h) < s.size(); ++h) {
			for (int i = 0; i < s.size(); ++i) {
				prefn[i] = pref[i] - (1 << h);
				if (prefn[i] < 0)  prefn[i] += s.size();
			}

			memset(cnt, 0, c * sizeof(int));

			for (int i = 0; i < s.size(); ++i)
				++cnt[classes[prefn[i]]];
			for (int i = 1; i < c; ++i)
				cnt[i] += cnt[i - 1];
			for (int i = s.size() - 1; i >= 0; --i)
				pref[--cnt[classes[prefn[i]]]] = prefn[i];

			classesn[pref[0]] = 0;
			c = 1;
			for (int i = 1; i < s.size(); ++i) {
				int mid1 = (pref[i] + (1 << h)) % s.size(), mid2 = (pref[i - 1] + (1 << h)) % s.size();
				if (classes[pref[i]] != classes[pref[i - 1]] || classes[mid1] != classes[mid2])
					++c;
				classesn[pref[i]] = c - 1;
			}
			memcpy(classes, classesn, s.size() * sizeof(int));
		}
		return;
	}

	void search::LCP(std::string& s) {

		for (int i = 0; i < s.size(); ++i) {
			pos[pref[i]] = i;
		}
		int k = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (k > 0) {
				k--;
			}
			if (pos[i] == s.size() - 1) {
				lcp[s.size() - 1] = -1;
				k = 0;
			}
			else
			{
				int j = pref[pos[i] + 1];
				while ((std::max(i + k, j + k) < s.size()) && (s[i + k] == s[j + k])) {
					++k;
				}
				lcp[pos[i]] = k;
			}
		}
		return;
	}

	int search::answer(std::string& s) {
		int sum = 0;
		for (int i = 0; i < s.size(); ++i) {
			sum += s.size() - 1 - pref[i];
		}
		for (int i = 0; i < s.size() - 1; ++i) {
			sum -= lcp[i];
		}

		return sum;
	}

}
int main() {
	std::string s;
	std::cin >> s;
	s += '$';
	search a(s);
	std::cout << a.answer(s);
	return 0;
}