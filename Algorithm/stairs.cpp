#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve() {
	int M, F, N, elevator = 1;
	cin >> M >> F >> N;
	if (N >= F - 1)
		N -= F - 1;
	elevator += N / M;
	if (N % M != 0) ++elevator;
	cout << elevator << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("stairs.inp", "r", stdin);
	freopen("stairs.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}