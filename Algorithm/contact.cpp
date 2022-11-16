#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int INF = 98765;

typedef struct node {
	int v, w;
	node(int V, int W) : v(V), w(W) {}
}NODE;

// �̺�Ž���ϱ� ���� ���� - ��尡 �������� ���� Ž���� �ʹ� ���� �ɸ� �� ����. 
// �����ϰ� ������ ������ ���� �ǵ� ��尡 500���� 500*500 ��ķ� ���� �� �� ����............ �缭 ����� �� �ƴұ�..
bool sortNode(const NODE& n1, const NODE& n2) {
	return n1.v < n2.v;
}

// dijkstra�� pq�� ���� ����
struct pqNode {
	bool operator()(const NODE& n1, const NODE& n2) {
		return n1.w > n2.w;
	}
};

typedef struct location {
	int u, v;
	double d;
	location(int U, int V, double D) : u(U), v(V), d(D) {}
}LOCA;

// pq�� ���� LOCA ���� - d�� �������� �������� -> priority_queue���� top�� ���� ���� d
struct pqLoca {
	bool operator()(const LOCA& l1, const LOCA& l2) {
		return l1.d > l2.d;
	}
};

// loca �迭�� ���� LOCA ���� -> ������ ���� ��ȣ������ ����
bool sortLocaEdge(const LOCA& l1, const LOCA& l2) {
	if (l1.u == l2.u)
		return l1.v < l2.v;
	return l1.u < l2.u;
}

int N, M, K, a, b, ans1, ans2;
vector<NODE> graph[501];
int dist[501];
bool visited[501];

void dijkstra() {
	priority_queue<NODE, vector<NODE>, pqNode> pq;
	for (int i = 1; i <= N; i++) {
		dist[i] = INF;
		visited[i] = false;
	}

	dist[a] = 0;
	pq.push(NODE(a, 0));

	while (!pq.empty()) {
		NODE t = pq.top(); pq.pop();
		if (t.v == b)
			break;
		if (visited[t.v])
			continue;

		visited[t.v] = true;
		for (auto& next : graph[t.v]) {
			if (dist[next.v] > dist[t.v] + next.w) {
				dist[next.v] = dist[t.v] + next.w;
				pq.push(NODE(next.v, dist[next.v]));
			}
		}
	}
}

// ���� �������� ����Ǵ� �̺� Ž���̰���?
int getEdgeWeight(int u, int v) {
	int left = 0, right = graph[u].size() - 1;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (graph[u][mid].v == v)
			return graph[u][mid].w;

		if (graph[u][mid].v < v)
			left = mid + 1;
		else
			right = mid - 1;
	}
}

void solve() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		graph[i].clear();
		graph[i].push_back(NODE(i, 0));
	}

	for (int i = 0, u, v, w; i < M; i++) {
		cin >> u >> v >> w;
		graph[u].push_back(NODE(v, w));
		graph[v].push_back(NODE(u, w));
	}

	// binary search�� ���� ����
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end(), sortNode);

	for (int i = 0; i < K; i++) {
		cin >> a >> b;
		dijkstra();
		double move = 1.0 * dist[b] / 2;

		vector<LOCA> locaA, locaB; // loca������ ����. (u, v)���� d��ŭ �̵���
		priority_queue<LOCA, vector<LOCA>, pqLoca> pq;
		for (int i = 1; i <= N; i++)
			visited[i] = false;

		pq.push(LOCA(a, a, 0)); // pq������ d: ���±��� �̵��� �Ÿ�
		while (!pq.empty()) {
			auto t = pq.top(); pq.pop();
			if (visited[t.v]) // �� ���� �����ϱ� 1.inp�� 2.inp���� �� �ϳ��� ���� �̻��ϰ� ���Դ�(���� ���̶� ���� ������ ���� ������). - for locaA
				continue;

			visited[t.u] = true;
			for (auto& g : graph[t.v]) {
				if (t.d + g.w < move) {
					if (!visited[g.v])
						pq.push(LOCA(t.v, g.v, t.d + g.w));
				}
				else {
					if (!visited[g.v])
						locaA.push_back(LOCA(min(t.v, g.v), max(t.v, g.v), move - t.d));
				}
			}
		}

		for (int i = 1; i <= N; i++)
			visited[i] = false;
		pq.push(LOCA(b, b, 0));
		while (!pq.empty()) {
			auto t = pq.top(); pq.pop();
			if (visited[t.v]) // �� ���� �����ϱ� 1.inp�� 2.inp���� �� �ϳ��� ���� �̻��ϰ� ���Դ�(���� ���̶� ���� ������ ���� ������). - for locaB
				continue;

			visited[t.u] = true;
			for (auto& g : graph[t.v]) {
				if (t.d + g.w < move) {
					if (!visited[g.v])
						pq.push(LOCA(t.v, g.v, t.d + g.w));
				}
				else {
					if (!visited[g.v])
						locaB.push_back(LOCA(min(t.v, g.v), max(t.v, g.v), move - t.d));
				}
			}
		}

		sort(locaA.begin(), locaA.end(), sortLocaEdge);
		sort(locaB.begin(), locaB.end(), sortLocaEdge);

		for (int p = 0, q = 0; p < locaA.size() && q < locaB.size();) {
			// ���� ������ ���
			if (locaA[p].u == locaB[q].u && locaA[p].v == locaB[q].v) {
				// loca �� ���� ���� ������ ���̿� ������ �� - �̰� ������ �ڱ� �ڽ��� �Ÿ��� 0�̶�� �� ����� �ϳ�?
				if ((int)(locaA[p].d + locaB[q].d) == getEdgeWeight(locaA[p].u, locaA[p].v)) {
					ans1 = locaA[p].u;
					ans2 = locaA[p].v;
					break;
				}
				// �ƴϸ� ���� �ƴ�
				else {
					++p;
					++q;
				}

			}

			// �ٸ� ��� -> �� ���� ���� ���� �ε����� ����
			else {
				if (locaA[p].u < locaB[q].u) {
					++p;
				}
				else if (locaA[p].u > locaB[q].u) {
					++q;
				}
				else {
					locaA[p].v < locaB[q].v ? ++p : ++q;
				}
			}
		}

		//for (auto& a : locaA)
		//	printf("(%d, %d, %f), ", a.u, a.v, a.d);
		//cout << endl;
		//for (auto& a : locaB)
		//	printf("(%d, %d, %f), ", a.u, a.v, a.d);
		//cout << endl;
		cout << ans1 << ' ' << ans2 << endl;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("contact.inp", "r", stdin);
	freopen("contact.out", "w", stdout);
	
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
		solve();
	return 0;
}