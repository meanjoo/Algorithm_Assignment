#include <bits/stdc++.h>
#define endl '\n'
#define x first
#define y second
#define MOD 100000
#define MAX 99999999
using namespace std;
typedef pair<int, int> Point;

typedef struct _myStruct {
	int cnt[202], min[202];
	Point path[202];
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
				dp[i][j].min[k] = MAX;
			}
			mark[i][j] = false;
		}
	}
	for (int i = 0; i <= K + 1; i++)
		dp[0][0].min[i] = 0;
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

int min3(int a, int b, int c) {
	return a < b && a < c? a : b < c ? b : c;
}

void solve() {
	cin >> M >> N >> K;
	init();
	getInput();

	// 0행
	for (int col = 1, chk = 0; col < N; col++) {
		int prevCost = dp[0][col - 1].min[chk];
		if (mark[0][col])
			++chk;
		dp[0][col].cnt[chk] = 1;
		dp[0][col].min[chk] = prevCost + rowCost[0][col];
		dp[0][col].path[chk] = { 0,col - 1 };
	}

	// 0열
	for (int row = 1, chk = 0; row < M; row++) {
		int prevCost = dp[row - 1][0].min[chk];
		if (mark[row][0])
			++chk;
		dp[row][0].cnt[chk] = 1;
		dp[row][0].min[chk] = prevCost + colCost[row][0];
		dp[row][0].path[chk] = { row - 1,0 };
	}

	for (int row = 1; row < M; row++) {
		for (int col = 1; col < N; col++) {
			for (int i = 0; i <= K + 1; i++) {
				dp[row][col].cnt[i] = ((dp[row][col - 1].cnt[i] % MOD) + (dp[row - 1][col].cnt[i] % MOD)) % MOD;
				dp[row][col].min[i] = min3(dp[row][col].min[i], dp[row - 1][col].min[i] + colCost[row][col], dp[row][col - 1].min[i] + rowCost[row][col]);

				if (dp[row - 1][col].min[i] + colCost[row][col] < dp[row][col - 1].min[i] + rowCost[row][col]) // 위에서 오는 경우
					dp[row][col].path[i] = { row - 1,col };
				else
					dp[row][col].path[i] = { row,col - 1 };
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
				dp[row][col].min[0] = MAX;
			}
		}
	}

	// dp 출력 보기
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << "(";
			for (int k = 0; k <= K + 1; k++) {
				cout << dp[i][j].cnt[k] << "," << dp[i][j].min[k] << ",[" << dp[i][j].path[k].x << "," << dp[i][j].path[k].y << "]/";
			}
			//cout << dp[i][j].cnt[3] << "," << dp[i][j].min[3] << ",[" << dp[i][j].path[3].x << "," << dp[i][j].path[3].y << "]/";

			cout << ") ";
		}
		cout << endl;
	}

	for (int k = 0; k <= K; k++) {
		if (dp[M - 1][N - 1].cnt[k] != 0) { // 가는 경로가 있는 경우 출력
			cout << "k:" << k << " count:" << dp[M - 1][N - 1].cnt[k] << " cost:" << dp[M - 1][N - 1].min[k] << endl;
			vector<Point> vp;
			int cx = M - 1, cy = N - 1, markCnt = k;
			while (cx != 0 || cy != 0) {
				vp.push_back({ cx,cy });
				int nx = dp[cx][cy].path[markCnt].x, ny = dp[cx][cy].path[markCnt].y;
				if (mark[cx][cy]) {
					--markCnt;
					//
				}

				cx = nx; cy = ny;
				//표시된 곳에 왔을 때 점 이동. 점을 옮긴 뒤에 표시된 횟수를 줄여야 한다.
			}
			reverse(vp.begin(), vp.end());
			cout << "(0,0)";
			for (auto& a : vp)
				cout << "->(" << a.x << "," << a.y << ")";
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