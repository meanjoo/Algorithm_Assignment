#include <bits/stdc++.h>
#define endl '\n'
#define MOD 100000
using namespace std;

typedef struct _myStruct {
	int cnt[202], min[202];
	string path[202];
}myStruct;

bool mark[100][100];
int rowCost[100][100], colCost[100][100];
int M, N, K;
myStruct dp[100][100];

void init() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k <= K + 1; k++) {
				dp[i][j].cnt[k] = 0;
				dp[i][j].min[k] = 0;
				dp[i][j].path[k] = "";
			}
			mark[i][j] = false;
		}
	}
}

void getInput() {
	int x, y;
	for (int i = 0; i < K; i++) {
		cin >> x >> y;
		mark[x][y] = true;
	}
	for (int row = 0; row < M; row++) {
		for (int col = 1; col < N; col++)
			cin >> rowCost[row][col];
	}
	for (int row = 1; row < M; row++) {
		for (int col = 0; col < N; col++)
			cin >> colCost[row][col];
	}
}

void addPathRight(int row, int col, int i) {
	dp[row][col].min[i] = dp[row][col - 1].min[i] + rowCost[row][col];
	dp[row][col].path[i] = dp[row][col - 1].path[i] + "R";
}

void addPathDown(int row, int col, int i) {
	dp[row][col].min[i] = dp[row - 1][col].min[i] + colCost[row][col];
	dp[row][col].path[i] = dp[row - 1][col].path[i] + "D";
}

char direction(string& fromUp, string& fromLeft) {
	int len = (int)fromUp.length();
	for (int i = 0; i < len; i++) {
		if (fromUp[i] == fromLeft[i])
			continue;
		return fromUp[i] == 'D' ? 'd' : 'r';
	}
}

void arrowPoint(int x, int y) {
	cout << "->(" << x << "," << y << ")";
}

void solve() {
	cin >> M >> N >> K;
	init();
	getInput();

	// 0행
	string str = "R";
	for (int col = 1, chk = 0; col < N; col++) {
		int prevCost = dp[0][col - 1].min[chk];
		if (mark[0][col])
			++chk;
		dp[0][col].cnt[chk] = 1;
		dp[0][col].min[chk] = prevCost + rowCost[0][col];
		dp[0][col].path[chk] = str;
		str.push_back('R');
	}

	// 0열
	str = "D";
	for (int row = 1, chk = 0; row < M; row++) {
		int prevCost = dp[row - 1][0].min[chk];
		if (mark[row][0])
			++chk;
		dp[row][0].cnt[chk] = 1;
		dp[row][0].min[chk] = prevCost + colCost[row][0];
		dp[row][0].path[chk] = str;
		str.push_back('D');
	}

	for (int row = 1; row < M; row++) {
		for (int col = 1; col < N; col++) {
			for (int i = 0; i <= K + 1; i++) {
				dp[row][col].cnt[i] = ((dp[row][col - 1].cnt[i] % MOD) + (dp[row - 1][col].cnt[i] % MOD)) % MOD;

				if (dp[row - 1][col].min[i] == 0 && dp[row][col - 1].min[i] == 0) // mark를 i번 지나서 오는 경우가 없음
					continue;
				else if (dp[row - 1][col].min[i] == 0) // mark를 i번 지나서 오는 경우는 왼쪽에서 오른쪽으로 오는 경우밖에 없음
					addPathRight(row, col, i);
				else if (dp[row][col - 1].min[i] == 0) // mark를 i번 지나서 오는 경우는 위에서 아래로 오는 경우밖에 없음
					addPathDown(row, col, i);
				else {
					int fromUp = dp[row - 1][col].min[i] + colCost[row][col];
					int fromLeft = dp[row][col - 1].min[i] + rowCost[row][col];
					if (fromUp < fromLeft)
						addPathDown(row, col, i);
					else if (fromLeft < fromUp)
						addPathRight(row, col, i);
					else { // fromLeft == fromUp
						char sel = direction(dp[row - 1][col].path[i], dp[row][col - 1].path[i]);
						sel == 'd' ? addPathDown(row, col, i) : addPathRight(row, col, i);
					}
				}
			}
			if (mark[row][col]) {
				dp[row][col].cnt[K + 1] = ((dp[row][col].cnt[K + 1] % MOD) + (dp[row][col].cnt[K] % MOD)) % MOD;
				dp[row][col].min[K + 1] = dp[row][col].min[K];
				dp[row][col].path[K + 1] = dp[row][col].path[K];
				for (int i = K; i > 0; i--) {
					dp[row][col].cnt[i] = dp[row][col].cnt[i - 1];
					dp[row][col].min[i] = dp[row][col].min[i - 1];
					dp[row][col].path[i] = dp[row][col].path[i - 1];
				}
				dp[row][col].cnt[0] = 0;
				dp[row][col].min[0] = 0;
				dp[row][col].path[0] = "";
			}
		}
	}

	// dp 출력 보기
	//for (int i = 0; i < M; i++) {
	//	for (int j = 0; j < N; j++) {
	//		cout << "(";
	//		for (int k = 0; k <= K + 1; k++) {
	//			cout << dp[i][j].cnt[k] << ", " << dp[i][j].min[k] << ", " << dp[i][j].path[k] << "/";
	//		}
	//		cout << ") ";
	//	}
	//	cout << endl;
	//}

	auto& ans = dp[M - 1][N - 1];
	for (int k = 0; k <= K; k++) {
		if (ans.min[k] != 0) {
			cout << "k:" << k << " count:" << ans.cnt[k] << " cost:" << ans.min[k] << endl;
			cout << "(0,0)";
			int x = 0, y = 0;
			for (auto& s : ans.path[k]) {
				s == 'R' ? ++y : ++x;
				arrowPoint(x, y);
			}
			cout << endl;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("path.inp", "r", stdin);
	freopen("path.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cout << "Test Case No:" << tc << endl;
		solve();
		cout << endl;
	}
	return 0;
}