#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAX = 1e9 + 1;

vector<int> arr, maxSeg, minSeg;
int n, comb[2], ans;

int makeMaxSeg(int node, int start, int end) {
	if (start == end)
		return maxSeg[node] = arr[start];
	int mid = (start + end) >> 1;
	return maxSeg[node] = max(makeMaxSeg(node * 2, start, mid), makeMaxSeg(node * 2 + 1, mid + 1, end));
}

int makeMinSeg(int node, int start, int end) {
	if (start == end)
		return minSeg[node] = arr[start];
	int mid = (start + end) >> 1;
	return minSeg[node] = min(makeMinSeg(node * 2, start, mid), makeMinSeg(node * 2 + 1, mid + 1, end));
}

int getMax(int node, int start, int end, int left, int right) {
	if (left > end || right < start)
		return 0;
	if (left <= start && end <= right)
		return maxSeg[node];
	int mid = (start + end) >> 1;
	return max(getMax(node * 2, start, mid, left, right), getMax(node * 2 + 1, mid + 1, end, left, right));
}

int getMin(int node, int start, int end, int left, int right) {
	if (left > end || right < start)
		return MAX;
	if (left <= start && end <= right)
		return minSeg[node];
	int mid = (start + end) >> 1;
	return min(getMin(node * 2, start, mid, left, right), getMin(node * 2 + 1, mid + 1, end, left, right));
}

void nC2(int depth, int next) {
	if (depth == 2) {
		int sectionIn = getMax(1, 0, n - 1, comb[0], comb[1]) - getMin(1, 0, n - 1, comb[0], comb[1]);
		int sectionOut = 0;
		if (comb[0] - 1 < 0 && comb[1] + 1 > n - 1) { // l이 배열의 첫 번째, r이 배열의 마지막
			sectionOut = 0;
		}
		else if (comb[0] - 1 < 0 && comb[1] + 1 <= n - 1) { // l(0)~r(sectionIn), r+1~n-1(sectionOut) l이 배열의 첫 번째
			sectionOut = getMax(1, 0, n - 1, comb[1] + 1, n - 1) - getMin(1, 0, n - 1, comb[1] + 1, n - 1);
		}
		else if (comb[1] + 1 > n - 1 && comb[0] - 1 >= 0) { // 0~l-1(sectionOut), l~n-1(sectionIn) r이 배열의 마지막
			sectionOut = getMax(1, 0, n - 1, 0, comb[0] - 1) - getMin(1, 0, n - 1, 0, comb[0] - 1);
		}
		else { // 0~l-1 l~r r+1~n-1
			sectionOut = max(getMax(1, 0, n - 1, 0, comb[0] - 1), getMax(1, 0, n - 1, comb[1] + 1, n - 1)) - min(getMin(1, 0, n - 1, 0, comb[0] - 1), getMin(1, 0, n - 1, comb[1] + 1, n - 1));
		}
		ans = sectionOut + sectionIn > ans ? sectionIn + sectionOut : ans;
		return;
	}
	for (int i = next; i < n; i++) {
		comb[depth] = i;
		nC2(depth + 1, i + 1);
	}
}

void solve() {
	ans = 0;
	cin >> n;
	int h = (int)ceil(log2(n));
	int size = 1 << (h + 1);
	maxSeg.resize(size);
	minSeg.resize(size);
	arr.resize(n);

	for (int i = 0; i < n; i++)
		cin >> arr[i];
	makeMaxSeg(1, 0, n - 1);
	makeMinSeg(1, 0, n - 1);
	nC2(0, 0);
	cout << ans << endl;
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