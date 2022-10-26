#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int MOD = 1e9 + 7;
const int MAXROW = 300;
const int MAXCOL = 20;

int N, K;
int dp[MAXROW + 1][MAXCOL + 1];

void makeDP() {
	for (int n = 1; n <= MAXROW; n++) {
		for (int k = 1; k <= MAXCOL; k++) {
			if (n < k)
				break;
			if (n == k || k == 1)
				dp[n][k] = 1;
			else
				dp[n][k] = ((dp[n - 1][k - 1] % MOD) + (dp[n - k][k] % MOD)) % MOD;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("addingways.inp", "r", stdin);
	freopen("addingways.out", "w", stdout);

	makeDP();
	while (true) {
		cin >> N >> K;
		if (N == 0 && K == 0)
			break;
		else
			cout << dp[N][K] << endl;
	}
	return 0;
}