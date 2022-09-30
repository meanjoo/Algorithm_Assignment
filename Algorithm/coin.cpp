#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

char dp[101][101][101];
char test;

char winlose(int x, int y, int z) {
	if (dp[x][y][z] == 'W' || dp[x][y][z] == 'L')
		return dp[x][y][z];

	int cntL = 0;
	for (int i = 1; i <= 3; i++) {
		if (x - i >= 0 && winlose(x - i, y, z) == 'L')
			++cntL;
		if (y - i >= 0 && winlose(x, y - i, z) == 'L')
			++cntL;
		if (z - i >= 0 && winlose(x, y, z - i) == 'L')
			++cntL;
	}
	
	char val = cntL > 0 ? 'W' : 'L';
	dp[x][y][z] = val; dp[x][z][y] = val;
	dp[y][x][z] = val; dp[y][z][x] = val;
	dp[z][x][y] = val; dp[z][y][x] = val;
	return dp[x][y][z];
}

void solve() {
	int a, b, c;
	cin >> a >> b >> c;

	dp[0][0][0] = 'W'; // ?
	dp[0][0][1] = 'L'; dp[0][1][0] = 'L'; dp[1][0][0] = 'L';
	dp[0][1][1] = 'W'; dp[1][0][1] = 'W'; dp[1][1][0] = 'W';
	dp[1][1][1] = 'L';

	winlose(a, b, c);
	cout << "(" << a << " " << b << " " << c << ") : ";
	dp[a][b][c] == 'W' ? cout << "1" << endl : cout << "-1" << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("coin.inp", "r", stdin);
	freopen("coin.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}