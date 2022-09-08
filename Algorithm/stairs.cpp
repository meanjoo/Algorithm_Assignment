#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve() {
	int M, F, N, elevator = 0, end = 0;
	cin >> M >> F >> N;
	// �ϴ� ������ ���� ��(F��)���� ���� �� �ִ� ��� �� ������ �ִ��� ���� ������ ����
	if (M - F <= N) {
		end = M;
		N -= M - F;
	}
	else {
		end = F + N;
		N -= N;
	}
	while (N > 0) {
		if (N - (M - 1) >= 0) {
			end = M;
			N -= M - 1;
		}
		else {
			end = max(N + 1, F);
			N -= N;
		}
		++elevator;
	}
	// end�� N����ŭ ����� �� �ö��� �� �������ִ� ��
	if (end != F) ++elevator;
	cout << elevator << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("stairs.inp", "r", stdin);
	freopen("stairs.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}