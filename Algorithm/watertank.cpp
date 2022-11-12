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
int tank[1001][1001], row[1001][1000], col[1000][1001]; // row: ���� ���� ũ�� ����, col: ���� ���� ũ�� ����
bool rowVisited[1001][1000], colVisited[1000][1001]; // �ش� ���� �湮 ����
bool visited[1001][1001]; // �ش� ĭ �湮 ����
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} }; // ��, ��, ��, ��
priority_queue<ST> pq;

void solve() {
	cin >> N >> M >> H;
	// ó�� tank�� ���� H�� ���� �� �湮 �迭 �ʱ�ȭ
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			tank[i][j] = H;
			visited[i][j] = false;
		}
	}

	// ���� ���� ũ�� ���� �Է� �� ���� ���� �湮 �迭 �ʱ�ȭ
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> row[i][j];
			rowVisited[i][j] = false;

			if (i == 0 && row[i][j] != -1) { // �� �� �ٱ��� �ִ� ����
				pq.push(ST(row[i][j], i + 1, j + 1));
				tank[i + 1][j + 1] = min(tank[i + 1][j + 1], row[i][j]);
				rowVisited[i][j] = true;
			}

			else if (i == N && row[i][j] != -1) { // �� �Ʒ� �ٱ��� �ִ� ����
				pq.push(ST(row[i][j], i, j + 1));
				tank[i][j + 1] = min(tank[i][j + 1], row[i][j]);
				rowVisited[i][j] = true;
			}
		}
	}

	// ���� ���� ũ�� ���� �Է� �� ���� ���� �湮 �迭 �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= M; j++) {
			cin >> col[i][j];
			colVisited[i][j] = false;

			if (j == 0 && col[i][j] != -1) { // �� ���� �ٱ��� �ִ� ����
				pq.push(ST(col[i][j], i + 1, j + 1));
				tank[i + 1][j + 1] = min(tank[i + 1][j + 1], col[i][j]);
				colVisited[i][j] = true;
			}

			else if (j == M && col[i][j] != -1) { // �� ������ �ٱ��� �ִ� ����
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

		//printf("���� ĭ: (%d, %d)\n", t.x, t.y);

		visited[t.x][t.y] = true;

		for (int i = 0; i < 4; i++) {
			int nx = t.x + dir[i][0], ny = t.y + dir[i][1];

			if (nx >= 1 && nx <= N && ny >= 1 && ny <= M && !visited[nx][ny]) {
				if (i == 0 && col[t.x - 1][t.y] != -1 && !colVisited[t.x - 1][t.y]) { // ������
					tank[nx][ny] = max(min(col[t.x - 1][t.y], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(col[t.x - 1][t.y], nx, ny));
					colVisited[t.x - 1][t.y] = true;
				}

				else if (i == 1 && col[t.x - 1][t.y - 1] != -1 && !colVisited[t.x - 1][t.y - 1]) { // ����
					tank[nx][ny] = max(min(col[t.x - 1][t.y - 1], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(col[t.x - 1][t.y - 1], nx, ny));
					colVisited[t.x - 1][t.y] = true;
				}

				else if (i == 2 && row[t.x][t.y - 1] != -1 && !rowVisited[t.x][t.y - 1]) { // �Ʒ���
					tank[nx][ny] = max(min(row[t.x][t.y - 1], tank[nx][ny]), tank[t.x][t.y]);

					pq.push(ST(row[t.x][t.y - 1], nx, ny));
					rowVisited[t.x][t.y - 1] = true;
				}

				else if (i == 3 && row[t.x - 1][t.y - 1] != -1 && !rowVisited[t.x - 1][t.y - 1]) { // ����
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