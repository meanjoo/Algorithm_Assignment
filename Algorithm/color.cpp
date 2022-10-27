#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

string car1, car2;
int dp[5001][5001], ps1[5001][26], ps2[5001][26], cnt[26];
int len1, len2;

void init() {
	for (int i = 1; i <= 5000; i++) {
		for (int j = 0; j < 26; j++)
			ps1[i][j] = ps2[i][j] = 0;
	}
	for (int i = 0; i < 26; i++) {
		cnt[i] = 0;
	}
}

void solve() {
	cin >> car1 >> car2;
	car1 = " " + car1;
	car2 = " " + car2;
	len1 = (int)car1.length();
	len2 = (int)car2.length();

	for (int i = 1; i < len1; i++) {
		++cnt[car1[i] - 'A'];
		++ps1[i][car1[i] - 'A'];
		for (int j = 0; j < 26; j++)
			ps1[i][j] += ps1[i - 1][j];
	}

	for (int i = 1; i < len2; i++) {
		++cnt[car2[i] - 'A'];
		++ps2[i][car2[i] - 'A'];
		for (int j = 0; j < 26; j++)
			ps2[i][j] += ps2[i - 1][j];
	}

	// �ᱹ �� ������ ������ ���� ������ �ε��� - ���� ù �ε����� �ո� �ּ�ȭ�ϴ� ���̴�.
	// �� ���ڰ� ���� ù ��°���� ������������ ���� �ȴ�. �߰� �Ŵ� �ʿ����.

	//0�� - car2�� ���� ä���
	for (int j = 1; j < len2; j++) {
		int idx = car2[j] - 'A', val = 0;
		// ������� �����տ��� 1~i��° �������� ps2[j][idx]-ps2[0][idx]�ε� ������ 0���� ���� 0�̴�. 
		// �� ���������� 1~i��° �����ո� ���� ������ ���Ⱑ ���� ��� �ȴ�.
		if (ps2[j][idx] == 1) // ��ü ���ڿ� ���� �ش� �������� �� ���ڰ� ó�� �������� �갡 ���� ���� ���´�.
			val -= j;
		if (ps2[j][idx] == cnt[idx]) // �ش� �������� ���� �� �� ������ ������ ��ü ���ڿ��� �� ������ ������ ���ٸ� ���Ⱑ ���� ������ �ڸ��̴�.
			val += j;
		dp[0][j] = dp[0][j - 1] + val;
	}

	//0�� - car1�� ���� ä���
	for (int i = 1; i < len1; i++) {
		int idx = car1[i] - 'A', val = 0;
		if (ps1[i][idx] == 1)
			val -= i;
		if(ps1[i][idx] == cnt[idx])
			val += i;
		dp[i][0] = dp[i - 1][0] + val;
	}

	for (int i = 1; i < len1; i++) {
		for (int j = 1; j < len2; j++) {
			int val1 = 0, val2 = 0;

			// val1. idx1�� car1[i]�� ���� ��, ps1[i]�� car1[i]�� ps2[j]�� car1[i]�� �� - dp���� ����(dp[i-1][j])�̶� ����
			// val2. idx2�� car2[j]�� ���� ��, ps2[j]�� car2[j]�� ps1[i]�� car2[j]�� �� - dp���� ����(dp[i][j-1])�̶� ����
			int idx1 = car1[i] - 'A', idx2 = car2[j] - 'A';
			if (ps1[i][idx1] + ps2[j][idx1] == 1) // 'A'+idx1 ���ڰ� ó�� ����
				val1 -= i + j;
			if (ps1[i][idx1] + ps2[j][idx1] == cnt[idx1]) // 'A'+idx1 ���ڰ� ������ �ڸ���
				val1 += i + j;

			if (ps2[j][idx2] + ps1[i][idx2] == 1)
				val2 -= i + j;
			if (ps2[j][idx2] + ps1[i][idx2] == cnt[idx2])
				val2 += i + j;

			dp[i][j] = min(dp[i - 1][j] + val1, dp[i][j - 1] + val2);
		}
	}

	cout << dp[len1 - 1][len2 - 1] << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("color.inp", "r", stdin);
	freopen("color.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		solve();
	}
	return 0;
}