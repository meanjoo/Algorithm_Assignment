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

// ���ʿ��� ���� ���. �� ���������� ���� ���
void addPathRight(int i, int j) {
	dp[i][j].cost = grid[i][j] + dp[i][j - 1].cost;
	dp[i][j].path = dp[i][j - 1].path + "R";
}

// ������ ���� ���. �� �Ʒ��� �������� ���
void addPathDown(int i, int j) {
	dp[i][j].cost = grid[i][j] + dp[i - 1][j].cost;
	dp[i][j].path = dp[i - 1][j].path + "D";
}

// d �Ǵ� r ��ȯ. ��� ��ΰ� ���� �켱���� ��ȯ�ϴ� �Լ�
// d�� ��ȯ�Ǹ� fromUp(����)���� �� �� �� ���� �켱�̶� �Ʒ��� �������� ��θ� ����, 
// r�� ��ȯ�Ǹ� fromLeft(����)���� �� �� �� ���� �켱�̶� ���������� ���� ��θ� ����
char select(string& fromUp, string& fromLeft) {
	int len = min((int)fromUp.length(), (int)fromLeft.length());
	for (int i = 0; i < len; i++) {
		if (fromUp[i] == fromLeft[i])
			continue;
		
		// �� �߿� R�� ���� ������ �� ���� �켱
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

	// 0��, 0�� ä���
	dp[0][0].cost = grid[0][0];
	for (int i = 1; i < m; i++) { // 0��
		if (grid[0][i] == -1)
			break;
		else {
			addPathRight(0, i);
		}
	}
	for (int i = 1; i < n; i++) { // 0��
		if (grid[i][0] == -1)
			break;
		else {
			addPathDown(i, 0);
		}
	}
	
	// n-1*m-1���� 0�� 0�� ������ ������ ä���(���ʰ� ���� ����)
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (grid[i][j] == -1)
				continue;

			bool fromUp = dp[i - 1][j].cost != -1, fromLeft = dp[i][j - 1].cost != -1;
			if (!fromUp && !fromLeft) { // ��, ���� ��ο��� �� �� ���� ���
				continue;
			}
			else if (fromUp && !fromLeft) { // �������� �� �� �ִ� ���. �� �Ʒ��� �������� ���
				addPathDown(i, j);
			}
			else if (!fromUp && fromLeft) { // ���ʿ����� �� �� �ִ� ���. �� ���������� ���� ���
				addPathRight(i, j);
			}
			else { // �� �� ������ ���
				if (dp[i - 1][j].cost < dp[i][j - 1].cost) { // ���ʿ��� ���� �� �� ����. �� �Ʒ��� �������� ���
					addPathDown(i, j);
				}
				else if (dp[i - 1][j].cost > dp[i][j - 1].cost) { // ���ʿ��� ���� �� �� ����. �� ���������� ���� ���
					addPathRight(i, j);
				}
				else { // dp[i - 1][j].cost == dp[i][j - 1].cost => ���� ����� ��ΰ� 2�� �̻��� ���� ���� �̵� ��θ� �켱 ����
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