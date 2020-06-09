#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

class summ {
public:
	summ();
	bool check();
	void algoritm();
	double angle(std::pair<double, double> a, std::pair<double, double> b);
private:
	bool v = false;
	int n_len, m_len;
	std::vector <std::pair<double, double> > N, M;
	std::vector <std::pair<double, double> > N1, M1;
	std::vector <std::pair<double, double> > answer;
};

summ::summ() {
	std::cin >> n_len;
	double x, y;

	for (int i = 0; i < n_len; ++i) {
		std::cin >> x >> y;
		N.push_back(std::make_pair(x, y));
	}

	std::cin >> m_len;

	for (int i = 0; i < m_len; ++i) {
		std::cin >> x >> y;
		x = -x;
		y = -y;
		M.push_back(std::make_pair(x, y));
	}
	reverse(N.begin(), N.end());
	reverse(M.begin(), M.end());
	int cur1 = 0, cur2 = 0;
	std::pair <double, double> p1, p2;
	p1 = N[0];
	p2 = M[0];

	for (int i = 0; i < N.size(); ++i) {
		if ((p1.second > N[i].second) || (p1.second == N[i].second && p1.first > N[i].first)) {
			p1 = N[i];
			cur1 = i;
		}
	}

	for (int i = cur1; i < N.size(); ++i) {
		N1.push_back(N[i]);
	}

	for (int i = 0; i < cur1; ++i) {
		N1.push_back(N[i]);
	}

	for (int i = 0; i < M.size(); ++i) {
		if ((p2.second > M[i].second) || (p2.second == M[i].second && p2.first > M[i].first)) {
			p2 = M[i];
			cur2 = i;
		}
	}

	for (int i = cur2; i < M.size(); ++i) {
		M1.push_back(M[i]);
	}

	for (int i = 0; i < cur2; ++i) {
		M1.push_back(M[i]);
	}

	algoritm();
}

void summ::algoritm() {
	int i = 0, j = 0;
	N1.push_back(N1[0]);
	N1.push_back(N1[1]);
	M1.push_back(M1[0]);
	M1.push_back(M1[1]);
	while ((i < n_len) || (j < m_len)) {
		answer.push_back(std::make_pair(N1[i].first + M1[j].first, N1[i].second + M1[j].second));
		if (angle(N1[i], N1[i + 1]) < angle(M1[j], M1[j + 1])) {
			if (i != n_len) {
				++i;
			}
			else {
				++j;
			}

		}
		else {
			if (angle(M1[j], M1[j + 1]) < angle(N1[i], N1[i + 1])) {
				if (j != m_len) {
					++j;
				}
				else {
					++i;
				}
			}
			else {
				++i;
				++j;
			}
		}
	}
	answer.push_back(answer[0]);
}

double summ::angle(std::pair<double, double> a, std::pair<double, double> b) {
	return atan2(b.second - a.second, b.first - a.first);
}

bool summ::check() {
	bool result = false;
	int j = answer.size() - 2;
	for (int i = 0; i < answer.size() - 1; ++i) {
		if ((answer[i].second < 0.0 && answer[j].second >= 0.0 || answer[j].second < 0.0 && answer[i].second >= 0.0) &&
			(answer[i].first + (0.0 - answer[i].second) / (answer[j].second - answer[i].second) * (answer[j].first - answer[i].first) < 0.0)) {
			result = !result;
		}
		j = i;
	}
	return result;
}
int main()
{
	summ a;
	bool answer = a.check();
	if (answer == false) {
		std::cout << "NO";
	}
	else {
		std::cout << "YES";
	}

}