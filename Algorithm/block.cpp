// 100점
/*
* 60점 코드와 다른 것은 60점 코드의 segment tree는 일반 segment tree이고, 100점 코드의 segment tree는 lazy propagation이 적용된 segment tree이다.
* 업데이트 할 때 값 하나를 업데이트 하는 게 아니라 구간을 업데이트하기 때문에 일반 segment tree로 하게 되면 구간을 업데이트 하는 데에 O(n lgn) 시간이 걸린다.
* O(n lgn)은 그냥 배열에서 구간 [a,b]를 하나씩 업데이트하는 데 걸리는 O(n)보다 나쁘다.
* lazy propagation을 쓰면 O(lgn)에 구간을 업데이트하고 구간의 값을 가져올 수 있다.
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

typedef struct rectangle {
	// (llx, lly): 왼쪽 아래 꼭짓점, (urx, ury): 오른쪽 위 꼭짓점
	int llx, lly, urx, ury;
}RECT;

typedef struct node {
	int val, lazy;
	node() : val(0), lazy(0) {}
}NODE;

int N;
vector<RECT> rects;
vector<NODE> seg; // segment tree with lazy propagation

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

// lazy 반영하면서 값 얻기 - [left, right]의 최댓값
// get에서는 lazy 반영하여 값 변경 및 lazy 초기화
int getMax(int node, int start, int end, int left, int right) {
	// lazy 처리 및 전파
	if (seg[node].lazy != 0) {
		seg[node].val = max(seg[node].val, seg[node].lazy);
		if (start != end) { // 자식이 있다면 자식에게 lazy 전파
			seg[node * 2].lazy = max(seg[node].lazy, seg[node * 2].lazy);
			seg[node * 2 + 1].lazy = max(seg[node].lazy, seg[node * 2 + 1].lazy);
		}
		seg[node].lazy = 0; // 자식에게 lazy 전파 후 내 lazy 삭제
	}

	if (left > end || right < start)
		return 0;
	if (left <= start && end <= right)
		return seg[node].val;
	int mid = (start + end) >> 1;
	return max(getMax(node * 2, start, mid, left, right), getMax(node * 2 + 1, mid + 1, end, left, right));
}

// 대표 구간에만 lazy를 두고 실제로 필요하게 될 때 lazy 반영하기 - [left, right] 값 업데이트
// update에서는 lazy 변경 및 lazy 반영하여 값 변경
void update(int node, int start, int end, int left, int right, int val) {
	// lazy가 남아있을 때 lazy를 처리하고 전파하기
	if (seg[node].lazy != 0) {
		seg[node].val = max(seg[node].val, seg[node].lazy);
		if (start != end) { // 자식이 있다면 자식에게 lazy 전파
			seg[node * 2].lazy = max(seg[node].lazy, seg[node * 2].lazy);
			seg[node * 2 + 1].lazy = max(seg[node].lazy, seg[node * 2 + 1].lazy);
		}
		seg[node].lazy = 0; // 자식에게 lazy 전파 후 내 lazy 삭제
	}

	if (left > end || right < start)
		return;
	// 대표 구간을 찾음
	if (left <= start && end <= right) {
		seg[node].val = max(seg[node].val, val);
		if (start != end) {
			seg[node * 2].lazy = max(seg[node * 2].lazy, val);
			seg[node * 2 + 1].lazy = max(seg[node * 2 + 1].lazy, val);
		}
		return;
	}

	int mid = (start + end) >> 1;
	update(node * 2, start, mid, left, right, val);
	update(node * 2 + 1, mid + 1, end, left, right, val);

	seg[node].val = max(seg[node * 2].val, seg[node * 2 + 1].val);
}

bool downward() {
	bool ret = false;
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

		update(1, 0, (int)v.size() - 1, lower_bound(v.begin(), v.end(), rects[i].llx + 1) - v.begin(), lower_bound(v.begin(), v.end(), rects[i].urx) - v.begin(), rects[i].ury);
	}

	return ret;
}

bool leftward() {
	bool ret = false;
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

		update(1, 0, (int)v.size() - 1, lower_bound(v.begin(), v.end(), rects[i].lly + 1) - v.begin(), lower_bound(v.begin(), v.end(), rects[i].ury) - v.begin(), rects[i].urx);
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