// 60�� - TLE
/*
* ��ǥ ������ �� ó������ ���ִ� �� �ƴ϶� ���� ��� ���ϹǷ� �Ź� ����� �Ѵ�.
* ��ǥ ������ �ϴ� ������ ���� �� �ִ� ��(���簢���� ���� �Ʒ� ��ǥ�� ���簢���� ������ �� ��ǥ)�� ������ ���� ���� �� �ִ� ���� ������ �ʹ� Ŀ���̴�.
* ��ǥ ������ �ؾ� segment tree�� ��� ������ �ٿ� �޸𸮸� ���� �� �ִ�.
* TLE�� �߻��� ������ downward�� leftward�� ���� ������ �ִ��� �������� �� O(lgn)�ε� ���� ������ O(n lgn)�̴�.
* �� ���� ������ n�� �ݺ��ϰ� �Ǵµ� �̴� O(n^2 lgn)�̴�. ���� ���� �ð� ������ TLE�� �߻��ϴ� �� ����.
*/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

typedef struct rectangle {
	// (llx, lly): ���� �Ʒ� ������, (urx, ury): ������ �� ������
	int llx, lly, urx, ury;
}RECT;

int N;
vector<RECT> rects;
vector<int> seg; // segment tree

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
	* �Ʒ��� �� �� x��ǥ�� ������ �ʴ´�.
	* �ִ��� �������� ���� ���ο� ���ؼ� �����;� �ϱ� ������ ��ǥ ������ x��ǥ�� ���ؼ��� �ϸ� �ȴ�.
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
		ori_lly = rects[i].lly; // ����Ǿ����� Ȯ���ϱ� ����. lly�� ���ϸ� ury�� ���ߴٴ� ���̹Ƿ� �ϳ��� ���� �ȴ�.
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
	* �������� �� �� y��ǥ�� ������ �ʴ´�.
	* �ִ��� �������� ���� ���ο� ���ؼ� �����;� �ϱ� ������ ��ǥ ������ y��ǥ�� ���ؼ��� �ϸ� �ȴ�.
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
		ori_llx = rects[i].llx; // ����Ǿ����� Ȯ���ϱ� ����. llx�� ���ϸ� urx�� ���ߴٴ� ���̹Ƿ� �ϳ��� ���� �ȴ�.
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