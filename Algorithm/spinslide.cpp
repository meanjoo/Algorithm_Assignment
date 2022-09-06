#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

char grid1[100][100], grid2[100][100];
int N, M;

void spin(char src[100][100], char dst[100][100]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			dst[i][j] = src[N - 1 - j][i];
	}
}

void slide(char grid[100][100]) {
	for (int c = 0; c < N; c++) {
		int blank = 0;
		for (int r = N - 1; r >= 0; r--) {
			if (grid[r][c] == '.')
				++blank;
			else if (grid[r][c] != '.' && blank != 0) {
				grid[r + blank][c] = grid[r][c];
				grid[r][c] = '.';
			}
		}
	}
}

void printGrid(char grid[100][100]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << grid[i][j];
		cout << endl;
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> grid1[i][j];
			grid2[i][j] = '.';
		}
	}

	for (int i = 0; i < M; i++) {
		if (i % 2 == 0) { // grid1->grid2
			spin(grid1, grid2);
			slide(grid2);
		}
		else { // grid2->grid1
			spin(grid2, grid1);
			slide(grid1);
		}
	}
	// 짝수번 시행했으면 grid1, 홀수번이면 grid2
	M % 2 == 0 ? printGrid(grid1) : printGrid(grid2);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("spinslide.inp", "r", stdin);
	freopen("spinslide.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cout << "Case #" << tc << ":" << endl;
		solve();
		cout << endl;
	}

	return 0;
}