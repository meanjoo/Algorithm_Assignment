#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int INF = 7654321; // espa에서 할 때 이거 9999로 제출해서 100 받았는데 어떻게 100 받은 거지

typedef struct info2 {
	// fuel1, turn1은 오른쪽 방향을 보고 있는 것, fuel2, turn2는 아래쪽 방향을 보고 있는 것
	int fuel1, turn1, fuel2, turn2;
	info2() { fuel1 = turn1 = fuel2 = turn2 = 0; }
	info2(int F1, int T1, int F2, int T2) : fuel1(F1), turn1(T1), fuel2(F2), turn2(T2) {}
}I2;

int M, N, L, G;
int row[101][100], col[100][101]; // [i][j]로 가는 데 드는 비용
I2 dp[200][100][100]; // dp[i][x][y]; 최대 i번 꺾을 수 있을 때 [x][y]로 도착하는 최소 연료량

void solve() {
	cin >> M >> N >> L >> G;
	//row Fuel
	for (int i = 0; i < M; i++) {
		for (int j = 1; j < N; j++)
			cin >> row[i][j];
	}
	//col Fuel
	for (int i = 1; i < M; i++) {
		for (int j = 0; j < N; j++)
			cin >> col[i][j];
	}

	// 최대 max(M-1, N-1)번 꺾을 수 있다.(X)
	// 최대 2*min(M, N) - 1번 꺾을 수 있다.
	// 그림판을 참고하자.
	int maxTurn = 2 * min(M - 1, N - 1);

	// 몇 번을 꺾든 0행과 0열의 값은 전부 똑같다.
	for (int i = 0; i <= maxTurn; i++) {
		// 0행
		for (int y = 1; y < N; y++)
			dp[i][0][y] = I2(dp[i][0][y - 1].fuel1 + row[0][y], 0, INF, INF);
		// 0열
		for (int x = 1; x < M; x++)
			dp[i][x][0] = I2(INF, INF, dp[i][x - 1][0].fuel2 + col[x][0], 0);
	}

	// 0번 꺾는 base setting - 최대 0번 꺾어서는 (M-1,N-1)에 도달할 수 없다. M,N의 최솟값이 2이기 때문이다.
	for (int x = 1; x < M; x++) {
		for (int y = 1; y < N; y++)
			dp[0][x][y] = I2(INF, INF, INF, INF);
	}

	for (int i = 1; i <= maxTurn; i++) {
		int rightFuel, rightTurn, downFuel, downTurn; // rightXX: 오른쪽으로 향하는 중의 연료, 전환 횟수, downXX: 아래쪽으로 향하는 중의 연료, 전환 횟수
		for (int x = 1; x < M; x++) {
			for (int y = 1; y < N; y++) {
				I2 val;

				rightFuel = dp[i][x][y - 1].fuel1 + row[x][y];
				rightTurn = dp[i][x][y - 1].turn1;
				downFuel = dp[i - 1][x][y - 1].fuel2 + row[x][y];
				downTurn = dp[i - 1][x][y - 1].turn2 + 1;

				if (rightTurn <= i && downTurn <= i) {
					val.fuel1 = min(rightFuel, downFuel);
					if (rightFuel < downFuel)
						val.turn1 = rightTurn;
					else if (rightFuel > downFuel)
						val.turn1 = downTurn;
					else
						val.turn1 = min(rightTurn, downTurn);
				}
				else if (rightTurn <= i) {
					val.fuel1 = rightFuel;
					val.turn1 = rightTurn;
				}
				else if (downTurn <= i) {
					val.fuel1 = downFuel;
					val.turn1 = downTurn;
				}
				else {
					val.fuel1 = INF;
					val.turn1 = INF;
				}

				rightFuel = dp[i - 1][x - 1][y].fuel1 + col[x][y];
				rightTurn = dp[i - 1][x - 1][y].turn1 + 1;
				downFuel = dp[i][x - 1][y].fuel2 + col[x][y];
				downTurn = dp[i][x - 1][y].turn2;

				if (rightTurn <= i && downTurn <= i) {
					val.fuel2 = min(rightFuel, downFuel);
					if (rightFuel < downFuel)
						val.turn2 = rightTurn;
					else if (rightFuel > downFuel)
						val.turn2 = downTurn;
					else
						val.turn2 = min(rightTurn, downTurn);
				}
				else if (rightTurn <= i) {
					val.fuel2 = rightFuel;
					val.turn2 = rightTurn;
				}
				else if (downTurn <= i) {
					val.fuel2 = downFuel;
					val.turn2 = downTurn;
				}
				else {
					val.fuel2 = INF;
					val.turn2 = INF;
				}

				dp[i][x][y] = val;
			}
		}
	}

	//for (int i = 0; i <= maxTurn; i++) {
	//	cout << "maxTurn: " << i << endl;
	//	for (int x = 0; x < M; x++) {
	//		for (int y = 0; y < N; y++)
	//			printf("(%d, %d),(%d, %d) ", dp[i][x][y].fuel1, dp[i][x][y].turn1, dp[i][x][y].fuel2, dp[i][x][y].turn2);
	//		cout << endl;
	//	}
	//	cout << endl;

	//}

	//for (int i = 0; i <= maxTurn; i++) {
	//	printf("maxTurn: %d\n", i);
	//	printf("(%d, %d),(%d, %d)\n", dp[i][M-1][N-1].fuel1, dp[i][M-1][N-1].turn1, dp[i][M-1][N-1].fuel2, dp[i][M-1][N-1].turn2);
	//}
	//cout << "\n*********\n\n";

	int ans = L * (M - 1 + N - 1);
	bool avail = false;
	for (int i = 0; i <= maxTurn; i++) {
		if (dp[i][M - 1][N - 1].fuel1 <= G && dp[i][M - 1][N - 1].fuel2 <= G) {
			ans += min(dp[i][M - 1][N - 1].turn1, dp[i][M - 1][N - 1].turn2);
			avail = true;
			break;
		}
		else if (dp[i][M - 1][N - 1].fuel1 <= G) {
			ans += dp[i][M - 1][N - 1].turn1;
			avail = true;
			break;
		}
		else if (dp[i][M - 1][N - 1].fuel2 <= G) {
			ans += dp[i][M - 1][N - 1].turn2;
			avail = true;
			break;
		}
	}
	avail ? cout << ans << endl : cout << "-1\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("drive.inp", "r", stdin);
	freopen("drive.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}