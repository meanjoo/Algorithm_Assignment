#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<int> paint;

// sz: 1줄의 크기, target: 최소 개수
bool canPaint(int sz, int target) {
	int cnt = 0;
	for (auto& p : paint) {
		if ((int)(p / sz) >= 2)
			cnt += (int)(p / sz);
	}
	return cnt >= target;
}

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
	//paint.resize(K);
	int vertical = 0, horizontal = 0;
	bool chkVertical = M % 2 == 0 ? true : false;
	bool chkHorizontal = N % 2 == 0 ? true : false;
	cout << "v: " << chkVertical << ", h : " << chkHorizontal << endl;
	for (int i = 0; i < K; i++) {
		cin >> paint;
		if (!chkVertical)
			vertical += odd(paint, N, chkVertical);
		else
			vertical += even(paint, N);

		if (!chkHorizontal)
			horizontal += odd(paint, N, chkHorizontal);
		else
			horizontal += even(paint, M);
	}
	//cout << "vertical: " << vertical << ", horizontal: " << horizontal << endl;
	cout << "vertical: " << vertical << ", " << chkVertical << " / horizontal: " << horizontal << ", " << chkHorizontal << endl;
	//(vertical >= K && chkVertical) || (horizontal >= K && chkHorizontal) ? cout << "YES" << endl : cout << "NO" << endl;
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