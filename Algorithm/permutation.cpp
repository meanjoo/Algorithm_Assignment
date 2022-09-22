#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

typedef struct node {
	int num;
	node* left, * right;
}Node;

vector<int> arr, depth;

void init() {
	arr.clear();
	depth.clear();
}

int findRootIndex(int left, int right) {
	int idx = left;
	for (int i = left + 1; i <= right; i++) {
		if (arr[i] > arr[idx])
			idx = i;
	}
	return idx;
}

void makeTree(Node* root, int left, int right, int pidx) {
	if (left > right)
		return;

	Node* newnode = new Node;
	int rootIdx = findRootIndex(left, right);
	newnode->num = arr[rootIdx];
	newnode->left = NULL; newnode->right = NULL;
	left < pidx ? root->left = newnode : root->right = newnode;

	if (left == right)
		return;

	makeTree(newnode, left, rootIdx - 1, rootIdx); //왼쪽 이진트리 생성
	makeTree(newnode, rootIdx + 1, right, rootIdx); // 오른쪽 이진트리 생성
}

void traversal(Node* ptr, int n, int d) {
	depth[n] = d;
	if (ptr->left != NULL)
		traversal(ptr->left, ptr->left->num, d + 1);
	if (ptr->right != NULL)
		traversal(ptr->right, ptr->right->num, d + 1);
}

void solve() {
	int n;
	cin >> n;
	arr.resize(n);
	depth.resize(n + 1, 0);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	Node* root = new Node;
	int maxidx = findRootIndex(0, n - 1);
	root->num = arr[maxidx];
	root->left = NULL; root->right = NULL;
	makeTree(root, 0, maxidx - 1, maxidx);
	makeTree(root, maxidx + 1, n - 1, maxidx);

	traversal(root, root->num, 0);
	for (auto& a : arr)
		cout << depth[a] << ' ';
	cout << endl;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("permutation.inp", "r", stdin);
	freopen("permutation.out", "w", stdout);

	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		solve();
	}
	return 0;
}