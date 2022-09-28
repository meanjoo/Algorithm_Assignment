#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef struct cost_path {
	int cost;
	string path;
}CP;

int n, m;
int grid[200][200];
CP dp[200][200];

// 왼쪽에서 오는 경우. 즉 오른쪽으로 가는 경로
void addPathRight(int i, int j) {
	dp[i][j].cost = grid[i][j] + dp[i][j - 1].cost;
	dp[i][j].path = dp[i][j - 1].path + "R";
}

// 위에서 오는 경우. 즉 아래로 내려가는 경로
void addPathDown(int i, int j) {
	dp[i][j].cost = grid[i][j] + dp[i - 1][j].cost;
	dp[i][j].path = dp[i - 1][j].path + "D";
}

// d 또는 r 반환. 어느 경로가 우측 우선인지 반환하는 함수
// d가 반환되면 fromUp(위쪽)에서 온 게 더 우측 우선이라 아래로 내려가는 경로를 선택, 
// r이 반환되면 fromLeft(왼쪽)에서 온 게 더 우측 우선이라 오른쪽으로 가는 경로를 선택
char select(string& fromUp, string& fromLeft) {
	int len = min((int)fromUp.length(), (int)fromLeft.length());
	for (int i = 0; i < len; i++) {
		if (fromUp[i] == fromLeft[i])
			continue;
		
		// 둘 중에 R이 먼저 나오는 게 우측 우선
		return fromUp[i] == 'R' ? 'd' : 'r';
	}
}

void print(int x, int y) {
	cout << "(" << x << " " << y << ")" << endl;
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> grid[i][j];
			dp[i][j].cost = -1;
		}
	}

	// 0행, 0열 채우기
	dp[0][0].cost = grid[0][0];
	for (int i = 1; i < m; i++) { // 0행
		if (grid[0][i] == -1)
			break;
		else {
			addPathRight(0, i);
		}
	}
	for (int i = 1; i < n; i++) { // 0열
		if (grid[i][0] == -1)
			break;
		else {
			addPathDown(i, 0);
		}
	}
	
	// n-1*m-1에서 0행 0열 제외한 나머지 채우기(왼쪽과 위를 토대로)
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (grid[i][j] == -1)
				continue;

			bool fromUp = dp[i - 1][j].cost != -1, fromLeft = dp[i][j - 1].cost != -1;
			if (!fromUp && !fromLeft) { // 위, 왼쪽 모두에서 올 수 없는 경우
				continue;
			}
			else if (fromUp && !fromLeft) { // 위에서만 올 수 있는 경우. 즉 아래로 내려가는 경로
				addPathDown(i, j);
			}
			else if (!fromUp && fromLeft) { // 왼쪽에서만 올 수 있는 경우. 즉 오른쪽으로 가는 경로
				addPathRight(i, j);
			}
			else { // 둘 다 가능한 경우
				if (dp[i - 1][j].cost < dp[i][j - 1].cost) { // 위쪽에서 오는 게 더 최저. 즉 아래로 내려가는 경로
					addPathDown(i, j);
				}
				else if (dp[i - 1][j].cost > dp[i][j - 1].cost) { // 왼쪽에서 오는 게 더 최저. 즉 오른쪽으로 가는 경로
					addPathRight(i, j);
				}
				else { // dp[i - 1][j].cost == dp[i][j - 1].cost => 최저 비용의 경로가 2개 이상일 때는 우측 이동 경로를 우선 선택
					char ch = select(dp[i - 1][j].path, dp[i][j - 1].path);
					ch == 'd' ? addPathDown(i, j) : addPathRight(i, j);
				}
			}
		}
	}

	int minPath = dp[n - 1][m - 1].cost;
	if (minPath == -1)
		cout << "No path." << endl;
	else {
		cout << minPath << endl;
		int x = 0, y = 0;
		print(x, y);
		for (auto& ch : dp[n - 1][m - 1].path) {
			ch == 'R' ? ++y : ++x;
			print(x, y);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("gridpath.inp", "r", stdin);
	freopen("gridpath.out", "w", stdout);

	solve();
	return 0;
}