#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int INF = 987654321;

int n, m;
vector<int> house;
int dp[500][500][500];

void init() {
	house.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 1; k < m; k++)
				dp[i][j][k] = INF;
		}
	}
}

void solve() {
	cin >> n >> m;
	init();
	for (int i = 0; i < n; i++)
		cin >> house[i];
	sort(house.begin(), house.end());

	if (m == 1) {
		int mid = ((int)house.size() - 1) / 2;
		// ¦�� ���� �߾Ӱ��� 2����
		int val = (int)house.size() % 2 == 0 ? (house[mid] + house[mid + 1]) / 2 : house[mid];
		int ans = 0;
		for (auto& h : house)
			ans += abs(h - val);
		cout << ans << endl;
		return;
	}

	// �������� 1���� ��
	for (int i = 0; i < n; i++) {
		for (int j = i, mid, val; j < n; j++) {
			dp[i][j][1] = 0;
			if (i == j)
				continue;
			
			mid = (i + j) / 2;
			val = (j - i + 1) % 2 == 0 ? (house[mid] + house[mid + 1]) / 2 : house[mid];
			for (int k = i; k <= j; k++)
				dp[i][j][1] += abs(house[k] - val);
		}
	}

	// ������ m���� ��ġ�� �� �� ������ ���� ����� ��Ȱ�� ��������� �Ÿ��� ���� �ּڰ��� ���ϱ� ���ؼ��� ������ m-1���� ��ġ���� ���� �ʿ��ϴ�.
	for (int cnt = 2; cnt < m; cnt++) {
		for (int i = 0; i < n; i++) {
			dp[i][i + cnt - 1][cnt] = 0;
			for (int j = i + cnt; j < n; j++) {
				for (int k = i; k < j; k++)
					// i~k�� 1���� ��ġ�ϰ�, k+1~j�� cnt-1���� ��ġ �� �� cnt���� ��ġ. �� �߿��� �ּ�
					dp[i][j][cnt] = min(dp[i][j][cnt], dp[i][k][1] + dp[k + 1][j][cnt - 1]);
			}
		}
	}

	int ans = INF;
	for (int i = 0; i < n - 1; i++)
		ans = min(ans, dp[0][i][1] + dp[i + 1][n - 1][m - 1]);
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("bin.inp", "r", stdin);
	freopen("bin.out", "w", stdout);

	int T;
	cin >> T;
	for(int tc=1;tc<=T;tc++)
		solve();
	return 0;
}