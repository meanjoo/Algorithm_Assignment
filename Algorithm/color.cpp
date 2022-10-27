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

	// 결국 이 문제는 문자의 가장 마지막 인덱스 - 가장 첫 인덱스의 합를 최소화하는 것이다.
	// 그 문자가 가장 첫 번째인지 마지막인지만 보면 된다. 중간 거는 필요없다.

	//0행 - car2를 통해 채우기
	for (int j = 1; j < len2; j++) {
		int idx = car2[j] - 'A', val = 0;
		// 원래라면 누적합에서 1~i번째 구간합은 ps2[j][idx]-ps2[0][idx]인데 어차피 0행은 전부 0이다. 
		// 이 문제에서는 1~i번째 구간합만 쓰기 때문에 빼기가 굳이 없어도 된다.
		if (ps2[j][idx] == 1) // 전체 문자에 대해 해당 구간에서 이 문자가 처음 나왔으면 얘가 제일 먼저 나온다.
			val -= j;
		if (ps2[j][idx] == cnt[idx]) // 해당 구간까지 봤을 때 그 문자의 개수가 전체 문자에서 그 문자의 개수와 같다면 여기가 가장 마지막 자리이다.
			val += j;
		dp[0][j] = dp[0][j - 1] + val;
	}

	//0열 - car1을 통해 채우기
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

			// val1. idx1은 car1[i]를 보는 것, ps1[i]의 car1[i]과 ps2[j]의 car1[i]를 봄 - dp에서 위쪽(dp[i-1][j])이랑 연산
			// val2. idx2는 car2[j]를 보는 것, ps2[j]의 car2[j]과 ps1[i]의 car2[j]를 봄 - dp에서 왼쪽(dp[i][j-1])이랑 연산
			int idx1 = car1[i] - 'A', idx2 = car2[j] - 'A';
			if (ps1[i][idx1] + ps2[j][idx1] == 1) // 'A'+idx1 문자가 처음 등장
				val1 -= i + j;
			if (ps1[i][idx1] + ps2[j][idx1] == cnt[idx1]) // 'A'+idx1 문자가 마지막 자리임
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