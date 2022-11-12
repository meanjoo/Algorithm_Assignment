#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef struct st {
	int holesize, x, y;
	st(int HS, int X, int Y) : holesize(HS), x(X), y(Y) {}

	bool operator<(const st& st1) const {
		return holesize > st1.holesize;
	}
}ST;

int N, M, H;
int tank[1001][1001], row[1001][1000], col[1000][1001]; // row: 가로 구멍 크기 정보, col: 세로 구멍 크기 정보
bool rowVisited[1001][1000], colVisited[1000][1001]; // 해당 구멍 방문 여부
bool visited[1001][1001]; // 해당 칸 방문 여부
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} }; // 오, 왼, 아, 위
priority_queue<ST> pq;

void solve() {
	cin >> N >> M >> H;
	// 처음 tank의 물을 H로 설정 및 방문 배열 초기화
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			tank[i][j] = H;
			visited[i][j] = false;
		}
	}

	// 가로 구멍 크기 정보 입력 및 가로 구멍 방문 배열 초기화
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> row[i][j];
			rowVisited[i][j] = false;

			if (i == 0 && row[i][j] != -1) { // 맨 위 바깥에 있는 구멍
				pq.push(ST(row[i][j], i + 1, j + 1));
				tank[i + 1][j + 1] = min(tank[i + 1][j + 1], row[i][j]);
				rowVisited[i][j] = true;
			}

			else if (i == N && row[i][j] != -1) { // 맨 아래 바깥에 있는 구멍
				pq.push(ST(row[i][j], i, j + 1));
				tank[i][j + 1] = min(tank[i][j + 1], row[i][j]);
				rowVisited[i][j] = true;
			}
		}
	}

	// 세로 구멍 크기 정보 입력 및 세로 구멍 방문 배열 초기화
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			cin >> col[i][j];
			colVisited[i][j] = false;

			if (j == 0 && col[i][j] != -1) { // 맨 왼쪽 바깥에 있는 구멍
				pq.push(ST(col[i][j], i + 1, j + 1));
				tank[i + 1][j + 1] = min(tank[i + 1][j + 1], col[i][j]);
				colVisited[i][j] = true;
			}

			else if (j == M && col[i][j] != -1) { // 맨 오른쪽 바깥에 있는 구멍
				pq.push(ST(col[i][j], i + 1, j));
				tank[i + 1][j] = min(tank[i + 1][j], col[i][j]);
				colVisited[i][j] = true;
			}
		}
	}

	while (!pq.empty()) {
		ST t = pq.top(); pq.pop();

		if (visited[t.x][t.y])
			continue;

		//printf("현재 칸: (%d, %d)\n", t.x, t.y);

		visited[t.x][t.y] = true;

		for (int i = 0; i < 4; i++) {
			int nx = t.x + dir[i][0], ny = t.y + dir[i][1];

			if (nx >= 1 && nx <= N && ny >= 1 && ny <= M && !visited[nx][ny]) {
				if (i == 0 && col[t.x - 1][t.y] != -1 && !colVisited[t.x - 1][t.y]) { // 오른쪽
					tank[nx][ny] = max(min(col[t.x - 1][t.y], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(col[t.x - 1][t.y], nx, ny));
					colVisited[t.x - 1][t.y] = true;
				}

				else if (i == 1 && col[t.x - 1][t.y - 1] != -1 && !colVisited[t.x - 1][t.y - 1]) { // 왼쪽
					tank[nx][ny] = max(min(col[t.x - 1][t.y - 1], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(col[t.x - 1][t.y - 1], nx, ny));
					colVisited[t.x - 1][t.y] = true;
				}

				else if (i == 2 && row[t.x][t.y - 1] != -1 && !rowVisited[t.x][t.y - 1]) { // 아래쪽
					tank[nx][ny] = max(min(row[t.x][t.y - 1], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(row[t.x][t.y - 1], nx, ny));
					rowVisited[t.x][t.y - 1] = true;
				}

				else if (i == 3 && row[t.x - 1][t.y - 1] != -1 && !rowVisited[t.x - 1][t.y - 1]) { // 위쪽
					tank[nx][ny] = max(min(row[t.x - 1][t.y - 1], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(row[t.x - 1][t.y - 1], nx, ny));
					rowVisited[t.x - 1][t.y - 1] = true;
				}
			}
		}
	}

	//for (int i = 1; i <= N; i++) {
	//	for (int j = 1; j <= M; j++)
	//		cout << tank[i][j] << ' ';
	//	cout << endl;
	//}

	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++)
			ans += tank[i][j];
	}
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("watertank.inp", "r", stdin);
	freopen("watertank.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}