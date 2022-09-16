#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<int> paint;

void solve() {
	int N, M, K;
	cin >> N >> M >> K;
	paint.resize(K);
	for (int i = 0; i < K; i++)
		cin >> paint[i];
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