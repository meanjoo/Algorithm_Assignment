#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

vector<int> arr;
int n;

void solve() {
	cin >> n;
	arr.resize(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());
	// 정확한 구간을 구하는 게 아니기 때문에 최대값 2개와 최소값 2개를 찾아놓으면 거기서 구간을 정할 수 있다.
	cout << arr[n - 1] + arr[n - 2] - arr[0] - arr[1] << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("gain.inp", "r", stdin);
	freopen("gain.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}
