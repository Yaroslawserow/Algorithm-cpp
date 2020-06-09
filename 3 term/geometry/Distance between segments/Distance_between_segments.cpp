#include <iostream>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <cmath>

struct segment {
	long double x, y, z;
};

class distance {
public:
	distance(segment u, segment v, segment w);
	long double det(segment a, segment b);
	long double print();
private:
	long double answer;
};


distance::distance(segment u, segment v, segment w) {
	long double    a = det(u, u);
	long double    b = det(u, v);
	long double    c = det(v, v);
	long double    d = det(u, w);
	long double    e = det(v, w);
	long double    D = a * c - b * b;
	long double    sc, sN, sD = D;
	long double    tc, tN, tD = D;
	long double eps = 0.000000001;
	if (D <= eps) {
		sN = 0.0;
		sD = 1.0;
		tN = e;
		tD = c;
	}
	else {
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN <= 0.0) {
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN >= sD) {
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN <= 0.0) {
		tN = 0.0;
		if (-d <= 0.0)
			sN = 0.0;
		else if (-d >= a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN >= tD) {
		tN = tD;
		if ((-d + b) <= 0.0)
			sN = 0;
		else if ((-d + b) >= a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	sc = (std::abs(sN) <= eps ? 0.0 : sN / sD);
	tc = (std::abs(tN) <= eps ? 0.0 : tN / tD);
	segment  ans;
	ans.x = w.x + (sc * u.x) - (tc * v.x);
	ans.y = w.y + (sc * u.y) - (tc * v.y);
	ans.z = w.z + (sc * u.z) - (tc * v.z);
	answer = sqrt(det(ans, ans));
	long double answer;
}

long double distance::det(segment a, segment b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

long double distance::print() {
	return answer;
}

int main() {
	long double a, b, c;
	long double a1, b1, c1;
	long double a2, b2, c2;
	long double a3, b3, c3;
	segment s1, s2, s3;
	std::cin >> a >> b >> c;
	std::cin >> a1 >> b1 >> c1;
	std::cin >> a2 >> b2 >> c2;
	std::cin >> a3 >> b3 >> c3;
	s1.x = a1 - a;
	s1.y = b1 - b;
	s1.z = c1 - c;
	s2.x = a3 - a2;
	s2.y = b3 - b2;
	s2.z = c3 - c2;
	s3.x = a - a2;
	s3.y = b - b2;
	s3.z = c - c2;
	distance lol(s1, s2, s3);
	long double ans = lol.print();
	std::cout << std::setprecision(20) << ans;
}