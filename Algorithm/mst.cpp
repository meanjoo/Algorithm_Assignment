#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

// kruskal
typedef struct edge_weight_num {
	int u, v, w, n;
}EWN;

// prim
typedef struct vertex_weight_num {
	int v, w, n;
	vertex_weight_num(int V, int W, int N) : v(V), w(W), n(N) {}

	bool operator<(const vertex_weight_num& vwn) const {
		if (w == vwn.w)
			return n > vwn.n;
		return w > vwn.w;
	}
}VWN;

int N, M;
vector<VWN> adj[10000]; // use at Prim
vector<EWN> edges; // use at Kruskal
vector<int> parent; // use at Kruskal

bool kruskalSort(const EWN& ewn1, const EWN& ewn2) {
	if (ewn1.w == ewn2.w)
		return ewn1.n < ewn2.n;
	return ewn1.w < ewn2.w;
}

int find(int x) {
	if (parent[x] < 0)
		return x;
	else
		return parent[x] = find(parent[x]);
}

bool same(int x, int y) {
	return find(x) == find(y);
}

void unite(int x, int y) {
	x = find(x); y = find(y);

	if (abs(parent[x]) < abs(parent[y]))
		swap(x, y);	
	parent[x] += parent[y];
	parent[y] = x;
}

void Kruskal() {
	sort(edges.begin(), edges.end(), kruskalSort);
	parent.resize(N);
	for (int i = 0; i < N; i++)
		parent[i] = -1;

	int minWeight = 0;
	vector<int> ans;

	for (auto& e : edges) {
		if ((int)ans.size() == N - 1)
			break;
		if (!same(e.u, e.v)) {
			unite(e.u, e.v);
			minWeight += e.w;
			ans.push_back(e.n);
		}
	}

	cout << "Tree edges by Kruskal algorithm: " << minWeight << endl;
	for (auto& a : ans)
		cout << a << endl;
}

void Prim(int start) {
	vector<bool> visited(N, false);
	vector<int> ans;
	int minWeight = 0;
	priority_queue<VWN> pq;

	visited[start] = true;
	for (auto& e : adj[start])
		pq.push(e);
	while (!pq.empty()) {
		auto t = pq.top(); pq.pop();
		if (visited[t.v])
			continue;

		visited[t.v] = true;
		minWeight += t.w;
		ans.push_back(t.n);
		for (auto& e : adj[t.v]) {
			pq.push(e);
		}
	}

	cout << "Tree edges by Prim algorithm with starting vertex " << start << ": " << minWeight << endl;
	for (auto& a : ans)
		cout << a << endl;
}

void solve() {
	cin >> N >> M;
	edges.resize(M);
	for (int i = 0; i < M; i++) {
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
		edges[i].n = i;
		adj[edges[i].u].push_back({ edges[i].v, edges[i].w, i });
		adj[edges[i].v].push_back({ edges[i].u,edges[i].w, i });
	}

	Kruskal();
	Prim(0);
	Prim(N / 2);
	Prim(N - 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("mst.inp", "r", stdin);
	freopen("mst.out", "w", stdout);

	solve();
	return 0;
}