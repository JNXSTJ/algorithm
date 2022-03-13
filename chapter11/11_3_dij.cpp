#include <vector>
#include <iostream>
#include <queue>

using namespace std;

#define maxn 10000


struct Edge {
	int from, to, dist;
	Edge(int u, int v, int d): from(u), to(v), dist(d) {}
};

struct HeapNode {
	int d, u;
	bool operator < (const HeapNode& rhs) const
	{
		return d > rhs.d;
	}
};

struct Dijkstra {
	int n, m; 
	vector<Edge> edges; 
	vector<int> G[maxn]; 
	bool done[maxn]; // 是否已永久标号
	int d[maxn];  		// s到各个点的距离
	int p[maxn];		// 最短路中的上一条弧

	void init(int n) {
		this->n = n; 
		for(int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void AddEdge(int from, int to, int dist)
	{
		edges.push_back(Edge(from, to, dist)); 
		m = edges.size(); 
		G[from].push_back(m-1);
	}
	
	void dijkstra(int s) {
		priority_queue<HeapNode> Q;
		for (int i = 0; i < n; i++) d[i] = INT_MAX;
		d[s] = 0;
		memset(done, 0, sizeof(done));
		Q.push({0, s});
		while (!Q.empty())
		{
			HeapNode x = Q.top(); Q.pop();
			int u = x.u;
			if (done[u]) continue;
			done[u] = true;
			for (int i = 0; i < G[u].size(); i++) {
				Edge& e = edges[G[u][i]];
				if (d[e.to] > d[u] + e.dist)
				{
					d[e.to] = d[u] + e.dist;
					p[e.to] = G[u][i];
					Q.push({d[e.to], e.to});
				}
			}
		}

	} 
};

int main()
{
	Dijkstra dij;
	int n = 10;
	dij.init(n);
	dij.AddEdge(1, 2, 3);
	dij.AddEdge(2, 3, 4);
	dij.dijkstra(1);
	cout << dij.d[3] << endl;
	cout << "*****" << endl;
	return 0;
}