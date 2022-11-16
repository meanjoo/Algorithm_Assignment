#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int INF = 98765;

typedef struct node {
	int v, w;
	node(int V, int W) : v(V), w(W) {}
}NODE;

// 이분탐색하기 위한 정렬 - 노드가 많아지면 순차 탐색이 너무 오래 걸릴 것 같다. 
// 제출하고 나서야 생각이 나는 건데 노드가 500개라서 500*500 행렬로 만들어도 될 거 같다............ 사서 고생한 게 아닐까..
bool sortNode(const NODE& n1, const NODE& n2) {
	return n1.v < n2.v;
}

// dijkstra의 pq를 위한 정렬
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

// pq를 위한 LOCA 정렬 - d를 기준으로 내림차순 -> priority_queue에서 top에 가장 작은 d
struct pqLoca {
	bool operator()(const LOCA& l1, const LOCA& l2) {
		return l1.d > l2.d;
	}
};

// loca 배열을 위한 LOCA 정렬 -> 간선의 정점 번호순으로 정렬
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

// 값이 존재함이 보장되는 이분 탐색이겠지?
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

	// binary search를 위한 정렬
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end(), sortNode);

	for (int i = 0; i < K; i++) {
		cin >> a >> b;
		dijkstra();
		double move = 1.0 * dist[b] / 2;

		vector<LOCA> locaA, locaB; // loca에서의 변수. (u, v)에서 d만큼 이동함
		priority_queue<LOCA, vector<LOCA>, pqLoca> pq;
		for (int i = 1; i <= N; i++)
			visited[i] = false;

		pq.push(LOCA(a, a, 0)); // pq에서의 d: 여태까지 이동한 거리
		while (!pq.empty()) {
			auto t = pq.top(); pq.pop();
			if (visited[t.v]) // 이 조건 없으니까 1.inp랑 2.inp에서 딱 하나씩 답이 이상하게 나왔다(이전 답이랑 같은 값으로 답이 나왔음). - for locaA
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
			if (visited[t.v]) // 이 조건 없으니까 1.inp랑 2.inp에서 딱 하나씩 답이 이상하게 나왔다(이전 답이랑 같은 값으로 답이 나왔음). - for locaB
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
			// 같은 간선인 경우
			if (locaA[p].u == locaB[q].u && locaA[p].v == locaB[q].v) {
				// loca 두 값의 합이 간선의 길이와 같으면 답 - 이거 때문에 자기 자신의 거리는 0이라는 걸 해줘야 하나?
				if ((int)(locaA[p].d + locaB[q].d) == getEdgeWeight(locaA[p].u, locaA[p].v)) {
					ans1 = locaA[p].u;
					ans2 = locaA[p].v;
					break;
				}
				// 아니면 답이 아님
				else {
					++p;
					++q;
				}

			}

			// 다른 경우 -> 더 작은 간선 쪽의 인덱스를 증가
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