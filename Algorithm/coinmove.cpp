//Bottom-up
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int P, K, S;
vector<char> dp[8];

void solve() {
	cin >> P >> K >> S;
	for (int i = 1; i <= K; i++) {
		dp[i].clear();
		dp[i].resize(S, ' ');
		dp[i][0] = 'L';
	}

	for (int i = P; i < S; i += P) {
		for (int j = 1; j <= K; j++)
			dp[j][i] = 'W';
	}

	for (int col = 1; col < S; col++) {
		if (col % P == 0) // 배수는 이미 W로 채워져 있는데 다른 값을 가지면 안 된다
			continue;
		for (int row = 1; row <= K; row++) {
			int cntL = 0;
			for (int i = 1; i <= K; i++) {
				if (i == row)
					continue;
				if (col - i >= 0 && dp[i][col - i] == 'L') {
					++cntL;
					break;
				}
			}
			dp[row][col] = cntL > 0 ? 'W' : 'L';
		}
	}

	int gap = 0;
	for (int i = 1; i <= K; i++) {
		if (S - i >= 0 && dp[i][S - i] == 'L') {
			gap = i;
			break;
		}
	}

	gap == 0 ? cout << "-1" << endl : cout << S - gap << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("coinmove.inp", "r", stdin);
	freopen("coinmove.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}