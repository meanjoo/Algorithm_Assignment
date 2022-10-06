#include <bits/stdc++.h>
#define endl '\n'
#define cut first
#define cube second
using namespace std;

const int MAX = 1e9;
int W, L, H;
pair<int, int> dp[201][201][201];

pair<int, int> cntSquare(int a, int b, int c) {
	if (dp[a][b][c].cube > 0)
		return dp[a][b][c];
	if (a == b && b == c)
		return dp[a][b][c] = { 0,1 };

	int minCut = MAX, cubeCnt = 0;
	for (int i = 1; i <= a / 2; i++) {
		if (cntSquare(i, b, c).cut + cntSquare(a - i, b, c).cut < minCut) {
			minCut = dp[i][b][c].cut + dp[a - i][b][c].cut;
			cubeCnt = dp[i][b][c].cube + dp[a - i][b][c].cube;
		}
	}
	for (int i = 1; i <= b / 2; i++) {
		if (cntSquare(a, i, c).cut + cntSquare(a, b - i, c).cut < minCut) {
			minCut = dp[a][i][c].cut + dp[a][b - i][c].cut;
			cubeCnt = dp[a][i][c].cube + dp[a][b - i][c].cube;
		}
	}
	for (int i = 1; i <= c / 2; i++) {
		if (cntSquare(a, b, i).cut + cntSquare(a, b, c - i).cut < minCut) {
			minCut = dp[a][b][i].cut + dp[a][b][c - i].cut;
			cubeCnt = dp[a][b][i].cube + dp[a][b][c - i].cube;
		}
	}
	dp[a][b][c] = dp[a][c][b] = dp[b][a][c] = dp[b][c][a] = dp[c][a][b] = dp[c][b][a] = { minCut + 1, cubeCnt };
	return dp[a][b][c];
}

void solve() {
	cin >> W >> L >> H;
	cout << cntSquare(W, L, H).cube << endl;
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