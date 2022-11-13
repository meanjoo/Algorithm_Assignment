// 40점 - TLE
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const ll INF = 987654321;

typedef struct task {
	ll income, time;
	int num;
	double incPerTime;
}TASK;

ll I, totalIncome;
vector<vector<ll>> dp;
int n, arr[11];
vector<TASK> subject;

bool compareTASK(const TASK& subject1, const TASK& subject2) {
	if (subject1.incPerTime == subject2.incPerTime)
		return subject1.time < subject2.time;
	return subject1.incPerTime > subject2.incPerTime;
}

ll makeDp(int s, ll i) {
	if (dp[s][i] > 0)
		return dp[s][i];

	if (i <= subject[s].income)
		return dp[s][i] = min(subject[s].time, makeDp(s - 1, i));
	else
		return dp[s][i] = min(subject[s].time + makeDp(s - 1, i - subject[s].income), makeDp(s - 1, i));
}

void getTaskNum(int s, ll i) {
	if (s == 0)
		return;

	int ns;
	ll ni;
	if (i <= subject[s].income) {
		if (dp[s][i] == subject[s].time) { // s번째 선택
			totalIncome += subject[s].income;
			if (subject[s].num <= 10)
				arr[subject[s].num] = 1;
			ns = 0;
			ni = 0;
		}
		else { // s번째 선택 안 함
			ns = s - 1;
			ni = i;
		}
	}

	else {
		if (dp[s][i] == dp[s - 1][i]) { // s번째 선택 안 함
			ns = s - 1;
			ni = i;
		}
		else { // s번째 선택
			totalIncome += subject[s].income;
			if (subject[s].num <= 10)
				arr[subject[s].num] = 1;
			ns = s - 1;
			ni = i - subject[s].income;
		}
	}
	getTaskNum(ns, ni);
}

void solve() {
	cin >> n >> I;
	subject.resize(n + 1);
	dp.resize(n + 1);
	for (int i = 1; i <= n; i++)
		dp[i].resize(I + 1, 0);

	for (int i = 1; i <= n; i++) {
		cin >> subject[i].income >> subject[i].time;
		subject[i].num = i;
		subject[i].incPerTime = 1.0 * subject[i].income / subject[i].time;
	}
	sort(subject.begin() + 1, subject.end(), compareTASK);

	for (int i = 1; i <= I; i++)
		dp[1][i] = i <= subject[1].income ? subject[1].time : INF;

	makeDp(n, I);
	getTaskNum(n, I);

	cout << dp[n][I] << ' ' << totalIncome << endl;
	for (int i = 1; i <= 10; i++)
		cout << arr[i] << ' ';
	cout << endl;

	//for(int i=1;i<=n;i++)
	//	printf("수입: %lld, 시간: %lld, 번호: %d, 시간당 수입: %f\n", subject[i].income, subject[i].time, subject[i].num, subject[i].incPerTime);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("freelancer.inp", "r", stdin);
	freopen("freelancer.out", "w", stdout);

	solve();
	return 0;
}