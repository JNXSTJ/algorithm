#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

const int maxn = 50;

struct Edge {
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

struct EdmondsKarp {
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn];
	int a[maxn];
	int p[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int cap) {
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	int Maxflow(int s, int t) {
		int flow = 0;
		for (;;) {
			memset(a, 0, sizeof(a));
			queue<int> Q;
			a[s] = INT_MAX;
			Q.push(s);
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				for (int i = 0; i < G[x].size(); i++) {
					Edge& e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = min(a[x], e.cap - e.flow);
						Q.push(e.to);
					}
				}
				if (a[t]) break;
			}
			if (!a[t]) break;
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += a[t];
				edges[p[u] ^ 1].flow -= a[t];
			}
			flow += a[t];
		}
		return flow;
	}
};

int main()
{
	EdmondsKarp ek;
	int s[10][3] = {
		{0, 1, 16},
		{0, 2, 13},
		{1, 2, 10},
		{1, 3, 12},
		{2, 1, 4},
		{2, 4, 14},
		{3, 2, 9},
		{3, 5, 20},
		{4, 5, 4},
		{4, 3, 7}
	};

	ek.init(10);
	for (int i = 0; i < 10; i++) {
		ek.AddEdge(s[i][0], s[i][1], s[i][2]);
	}
	cout << ek.Maxflow(0, 5) << endl;
	return 0;
}