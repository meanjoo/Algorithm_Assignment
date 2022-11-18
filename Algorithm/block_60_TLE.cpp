// 60점 - TLE
/*
* 좌표 압축을 딱 처음에만 해주는 게 아니라 값이 계속 변하므로 매번 해줘야 한다.
* 좌표 압축을 하는 이유는 가질 수 있는 것(직사각형의 왼쪽 아래 좌표와 직사각형의 오른쪽 위 좌표)의 개수에 비해 가질 수 있는 값의 범위가 너무 커서이다.
* 좌표 압축을 해야 segment tree의 노드 개수를 줄여 메모리를 줄일 수 있다.
* TLE가 발생한 이유는 downward와 leftward를 보면 구간의 최댓값을 가져오는 건 O(lgn)인데 구간 갱신이 O(n lgn)이다.
* 이 구간 갱신을 n번 반복하게 되는데 이는 O(n^2 lgn)이다. 구간 갱신 시간 때문에 TLE가 발생하는 것 같다.
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

typedef struct rectangle {
	// (llx, lly): 왼쪽 아래 꼭짓점, (urx, ury): 오른쪽 위 꼭짓점
	int llx, lly, urx, ury;
}RECT;

int N;
vector<RECT> rects;
vector<int> seg; // segment tree

// downward - lly 오름차순, 같은 lly는 llx 오름차순
bool sort_llyllx(const RECT& r1, const RECT& r2) {
	if (r1.lly == r2.lly)
		return r1.llx < r2.llx;
	return r1.lly < r2.lly;
}

// leftward -  llx 오름차순, 같은 llx에 대해서는 lly 오름차순
bool sort_llxlly(const RECT& r1, const RECT& r2) {
	if (r1.llx == r2.llx)
		return r1.lly < r2.lly;
	return r1.llx < r2.llx;
}

void setSeg(int leaf) {
	seg.clear(); // segment tree 초기화
	int h = (int)(ceil(log2(leaf)));
	seg.resize(1 << (h + 1));
}

int getMax(int node, int start, int end, int left, int right) {
	if (left > end || right < start)
		return 0;

	if (left <= start && end <= right)
		return seg[node];
	int mid = (start + end) >> 1;
	return max(getMax(node * 2, start, mid, left, right), getMax(node * 2 + 1, mid + 1, end, left, right));
}

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || idx > end)
		return;

	seg[node] = max(seg[node], val);
	if (start == end)
		return;

	int mid = (start + end) >> 1;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);
}

bool downward() {
	bool ret = false;
	/*
	* 아래로 밀 때 x좌표는 변하지 않는다.
	* 최댓값을 가져오는 것은 가로에 대해서 가져와야 하기 때문에 좌표 압축을 x좌표에 대해서만 하면 된다.
	*/
	vector<int> v;
	for (int i = 0; i < N; i++) {
		v.push_back(rects[i].llx);
		v.push_back(rects[i].urx);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	setSeg((int)v.size());

	sort(rects.begin(), rects.end(), sort_llyllx);
	for (int i = 0, ori_lly; i < N; i++) {
		ori_lly = rects[i].lly; // 변경되었는지 확인하기 위함. lly가 변하면 ury도 변했다는 것이므로 하나만 보면 된다.
		rects[i].lly = getMax(1, 0, (int)v.size() - 1, lower_bound(v.begin(), v.end(), rects[i].llx + 1) - v.begin(), lower_bound(v.begin(), v.end(), rects[i].urx) - v.begin());
		if (rects[i].lly != ori_lly)
			ret = true;
		rects[i].ury -= ori_lly - rects[i].lly;

		for (int j = lower_bound(v.begin(), v.end(), rects[i].llx + 1) - v.begin(); j <= lower_bound(v.begin(), v.end(), rects[i].urx) - v.begin(); j++)
			update(1, 0, (int)v.size() - 1, j, rects[i].ury);
	}

	return ret;
}

bool leftward() {
	bool ret = false;
	/*
	* 왼쪽으로 밀 때 y좌표는 변하지 않는다.
	* 최댓값을 가져오는 것은 세로에 대해서 가져와야 하기 때문에 좌표 압축을 y좌표에 대해서만 하면 된다.
	*/
	vector<int> v;
	for (int i = 0; i < N; i++) {
		v.push_back(rects[i].lly);
		v.push_back(rects[i].ury);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	setSeg((int)v.size());

	sort(rects.begin(), rects.end(), sort_llxlly);
	for (int i = 0, ori_llx; i < N; i++) {
		ori_llx = rects[i].llx; // 변경되었는지 확인하기 위함. llx가 변하면 urx도 변했다는 것이므로 하나만 보면 된다.
		rects[i].llx = getMax(1, 0, (int)v.size() - 1, lower_bound(v.begin(), v.end(), rects[i].lly + 1) - v.begin(), lower_bound(v.begin(), v.end(), rects[i].ury) - v.begin());
		if (rects[i].llx != ori_llx)
			ret = true;
		rects[i].urx -= ori_llx - rects[i].llx;

		for (int j = lower_bound(v.begin(), v.end(), rects[i].lly + 1) - v.begin(); j <= lower_bound(v.begin(), v.end(), rects[i].ury) - v.begin(); j++)
			update(1, 0, (int)v.size() - 1, j, rects[i].urx);
	}

	return ret;
}


void solve() {
	cin >> N;
	rects.resize(N);
	for (int i = 0; i < N; i++)
		cin >> rects[i].llx >> rects[i].lly >> rects[i].urx >> rects[i].ury;

	bool updateDown = true, updateLeft = true;
	while (updateDown || updateLeft) {
		updateDown = downward();
		//puts("downward");
		//for (auto& a : rects)
		//	printf("%d %d %d %d\n", a.llx, a.lly, a.urx, a.ury);
		updateLeft = leftward();
		//puts("leftward");
		//for (auto& a : rects)
		//	printf("%d %d %d %d\n", a.llx, a.lly, a.urx, a.ury);
	}

	int minx = 987654321, miny = 987654321, maxx = 0, maxy = 0;
	for (int i = 0; i < N; i++) {
		minx = min(minx, rects[i].llx);
		miny = min(miny, rects[i].lly);
		maxx = max(maxx, rects[i].urx);
		maxy = max(maxy, rects[i].ury);
	}
	//printf("minx: %d, miny: %d, maxx: %d, maxy: %d\n", minx, miny, maxx, maxy);
	cout << maxx - minx << ' ' << maxy - miny << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("block.inp", "r", stdin);
	freopen("block.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}