#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int odd(int num, int d, bool& chk) {
	if (num / d >= 3)
		chk = true;
	return num / d >= 2 ? num / d : 0;
}

int even(int num, int d) {
	return num / d >= 2 ? num / d : 0;
}

void solve() {
	int N, M, K, paint;
	cin >> N >> M >> K;
	int vertical = 0, horizontal = 0;
	bool chkVertical = M % 2 == 0 ? true : false;
	bool chkHorizontal = N % 2 == 0 ? true : false;
	for (int i = 0; i < K; i++) {
		cin >> paint;
		if (!chkVertical)
			vertical += odd(paint, N, chkVertical);
		else
			vertical += even(paint, N);

		if (!chkHorizontal)
			horizontal += odd(paint, M, chkHorizontal);
		else
			horizontal += even(paint, M);
	}
	(vertical >= M && chkVertical) || (horizontal >= N && chkHorizontal) ? cout << "Yes" << endl : cout << "No" << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("grid.inp", "r", stdin);
	freopen("grid.out", "w", stdout);
	
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}