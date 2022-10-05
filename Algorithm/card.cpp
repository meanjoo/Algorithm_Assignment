#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int dp[3][1000];

int max2(int a, int b) {
	return a > b ? a : b;
}

int max3(int a, int b, int c) {
	return a > b && a > c ? a : b > c ? b : c;
}

void solve() {
	int n, card;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> card;
		if (i == 0 || i == 1 || i == 2)
			dp[0][i] = dp[1][i] = dp[2][i] = card;
		else {
			dp[0][i] = i == 5 ? card + dp[1][i - 2] : card + max2(dp[1][i - 2], dp[2][i - 2]);
			dp[1][i] = card + max3(dp[0][i - 3], dp[1][i - 3], dp[2][i - 3]);
			dp[2][i] = i == 3 ? max2(dp[0][i], dp[1][i]) : card + max3(dp[0][i - 4], dp[1][i - 4], dp[2][i - 4]);

		}
	}
	cout << max3(dp[0][n - 1], dp[1][n - 1], dp[2][n - 1]) << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("card.inp", "r", stdin);
	freopen("card.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}