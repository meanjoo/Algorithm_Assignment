#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int n;
int dp[1001][1001], card[1001], ps[1001];

void func() {
	for (int i = 1; i <= n; i++) {
		for (int left = 1, right = i; right <= n; left++, right++) {
			if (left == right)
				dp[left][right] = card[left];
			else if (right - 1 == left)
				dp[left][right] = max(card[left], card[right]);
			else
				dp[left][right] = max(card[left] + ps[right] - ps[left] - dp[left + 1][right], card[right] + ps[right - 1] - ps[left - 1] - dp[left][right - 1]);
		}
	}
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> card[i];
		ps[i] = ps[i - 1] + card[i];
	}

	func();
	cout << dp[1][n] << endl;
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