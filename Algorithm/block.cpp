// 100��
/*
* 60�� �ڵ�� �ٸ� ���� 60�� �ڵ��� segment tree�� �Ϲ� segment tree�̰�, 100�� �ڵ��� segment tree�� lazy propagation�� ����� segment tree�̴�.
* ������Ʈ �� �� �� �ϳ��� ������Ʈ �ϴ� �� �ƴ϶� ������ ������Ʈ�ϱ� ������ �Ϲ� segment tree�� �ϰ� �Ǹ� ������ ������Ʈ �ϴ� ���� O(n lgn) �ð��� �ɸ���.
* O(n lgn)�� �׳� �迭���� ���� [a,b]�� �ϳ��� ������Ʈ�ϴ� �� �ɸ��� O(n)���� ���ڴ�.
* lazy propagation�� ���� O(lgn)�� ������ ������Ʈ�ϰ� ������ ���� ������ �� �ִ�.
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

typedef struct rectangle {
	// (llx, lly): ���� �Ʒ� ������, (urx, ury): ������ �� ������
	int llx, lly, urx, ury;
}RECT;

typedef struct node {
	int val, lazy;
	node() : val(0), lazy(0) {}
}NODE;

int N;
vector<RECT> rects;
vector<NODE> seg; // segment tree with lazy propagation

// downward - lly ��������, ���� lly�� llx ��������
bool sort_llyllx(const RECT& r1, const RECT& r2) {
	if (r1.lly == r2.lly)
		return r1.llx < r2.llx;
	return r1.lly < r2.lly;
}

// leftward -  llx ��������, ���� llx�� ���ؼ��� lly ��������
bool sort_llxlly(const RECT& r1, const RECT& r2) {
	if (r1.llx == r2.llx)
		return r1.lly < r2.lly;
	return r1.llx < r2.llx;
}

void setSeg(int leaf) {
	seg.clear(); // segment tree �ʱ�ȭ
	int h = (int)(ceil(log2(leaf)));
	seg.resize(1 << (h + 1));
}

// lazy �ݿ��ϸ鼭 �� ��� - [left, right]�� �ִ�
// get������ lazy �ݿ��Ͽ� �� ���� �� lazy �ʱ�ȭ
int getMax(int node, int start, int end, int left, int right) {
	// lazy ó�� �� ����
	if (seg[node].lazy != 0) {
		seg[node].val = max(seg[node].val, seg[node].lazy);
		if (start != end) { // �ڽ��� �ִٸ� �ڽĿ��� lazy ����
			seg[node * 2].lazy = max(seg[node].lazy, seg[node * 2].lazy);
			seg[node * 2 + 1].lazy = max(seg[node].lazy, seg[node * 2 + 1].lazy);
		}
		seg[node].lazy = 0; // �ڽĿ��� lazy ���� �� �� lazy ����
	}

	if (left > end || right < start)
		return 0;
	if (left <= start && end <= right)
		return seg[node].val;
	int mid = (start + end) >> 1;
	return max(getMax(node * 2, start, mid, left, right), getMax(node * 2 + 1, mid + 1, end, left, right));
}

// ��ǥ �������� lazy�� �ΰ� ������ �ʿ��ϰ� �� �� lazy �ݿ��ϱ� - [left, right] �� ������Ʈ
// update������ lazy ���� �� lazy �ݿ��Ͽ� �� ����
void update(int node, int start, int end, int left, int right, int val) {
	// lazy�� �������� �� lazy�� ó���ϰ� �����ϱ�
	if (seg[node].lazy != 0) {
		seg[node].val = max(seg[node].val, seg[node].lazy);
		if (start != end) { // �ڽ��� �ִٸ� �ڽĿ��� lazy ����
			seg[node * 2].lazy = max(seg[node].lazy, seg[node * 2].lazy);
			seg[node * 2 + 1].lazy = max(seg[node].lazy, seg[node * 2 + 1].lazy);
		}
		seg[node].lazy = 0; // �ڽĿ��� lazy ���� �� �� lazy ����
	}

	if (left > end || right < start)
		return;
	// ��ǥ ������ ã��
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
		ori_lly = rects[i].lly; // ����Ǿ����� Ȯ���ϱ� ����. lly�� ���ϸ� ury�� ���ߴٴ� ���̹Ƿ� �ϳ��� ���� �ȴ�.
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
		ori_llx = rects[i].llx; // ����Ǿ����� Ȯ���ϱ� ����. llx�� ���ϸ� urx�� ���ߴٴ� ���̹Ƿ� �ϳ��� ���� �ȴ�.
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