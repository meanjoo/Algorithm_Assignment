#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = 1e9;
int W, L, H;
int dp[201][201][201];

int cntSquare(int a, int b, int c) {
	if (dp[a][b][c] > 0)
		return dp[a][b][c];
	if (a == b && b == c)
		return dp[a][b][c] = 1;

	int min = MAX;
	for (int i = 1; i <= a / 2; i++) {
		if (cntSquare(i, b, c) + cntSquare(a - i, b, c) < min)
			min = dp[i][b][c] + dp[a - i][b][c];
	}
	for (int i = 1; i <= b / 2; i++) {
		if (cntSquare(a, i, c) + cntSquare(a, b - i, c) < min)
			min = dp[a][i][c] + dp[a][b - i][c];
	}
	for (int i = 1; i <= c / 2; i++) {
		if (cntSquare(a, b, i) + cntSquare(a, b, c - i) < min)
			min = dp[a][b][i] + dp[a][b][c - i];
	}
	dp[a][b][c] = dp[a][c][b] = dp[b][a][c] = dp[b][c][a] = dp[c][a][b] = dp[c][b][a] = min;
	return dp[a][b][c];
}

void solve() {
	cin >> W >> L >> H;
	cout << cntSquare(W, L, H) << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("cube.inp", "r", stdin);
	freopen("cube.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}