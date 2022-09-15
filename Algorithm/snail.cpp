#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

typedef struct point {
	ll x, y;
}Point;

// level은 가장 x가 바깥부터 얼마나 안쪽에 있는지를 의미한다. 가장 바깥을 level 0이라고 한다.
int getLevel(ll n, ll x) {
	int level = -1;
	ll s = 0, e = 0;
	while (n >= 0) {
		s = e + 1; e = s + 4 * n - 1;
		n -= 2;
		++level;
		if (s <= x && x <= e)
			break;
	}
	return level;
}

Point getPoint(ll n, ll level, ll num) {
	Point p;
	ll step = n - 2 * level - 1;
	ll start = 4 * (level * n - level * level) + 1;
	if (num <= start + step) { // →
		p.x = level;
		p.y = num - start + level;
	}
	else if (num <= start + step * 2) { // ↓
		p.x = num - (start + step) + level;
		p.y = n - 1 - level;
	}
	else if (num <= start + step * 3) { // ←
		p.x = n - 1 - level;
		p.y = start + step * 3 - num + level;
	}
	else { // ↑
		p.x = start + step * 4 - num + level;
		p.y = level;
	}
	return p;
}

bool isSquare(Point& p1, Point& p2) {
	return abs(p1.x - p2.x) == abs(p1.y - p2.y);
}

void solve() {
	ll n, a, b;
	cin >> n >> a >> b;
	int levelA = getLevel(n - 1, a), levelB = getLevel(n - 1, b);
	Point Pa = getPoint(n, levelA, a), Pb = getPoint(n, levelB, b);
	isSquare(Pa, Pb) ? cout << "YES\n" : cout << "NO\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("snail.inp", "r", stdin);
	freopen("snail.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}