#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

const int maxn = 100;

struct Edge {
    int from, to, cap, flow, cost;
    Edge(int u, int v, int c, int f, int w): from(u), to(v), cap(c), flow(f), cost(w) {}
};

struct MCMF {
    int n, m;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];
    int d[maxn];
    int p[maxn];
    int a[maxn];

    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap, int cost) {
        edges.push_back(Edge(from, to, cap, 0, cost));
        edges.push_back(Edge(to, from, 0, 0, -cost));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BellmanFord(int s, int t, int &flow, long long& cost)
    {
        for (int i = 0; i < n; i++) d[i] = INT_MAX;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INT_MAX;

        queue<int> Q;
        Q.push(s);
        while (!Q.empty()) 
        {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for (int i = 0; i < G[u].size(); i++)
            {
                Edge& e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost)
                {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if (d[t] == INT_MAX) return false;
        flow += a[t];
        cost += (long long)d[t] * (long long)a[t];
        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        return true;
    }

    int MincostMaxflow(int s, int t, long long& cost) {
        int flow = 0; 
        cost = 0;
        while (BellmanFord(s, t, flow, cost));
        return flow;
    }
};

int main()
{
    MCMF mcmf;
    int edges[][4] = {
        {0, 1, 2, 2},
        {0, 2, 1, 5},
        {1, 2, 1, 2},
        {1, 3, 1, 3},
        {2, 3, 1, 1},
    };
    mcmf.init(4);
    for (int i=  0; i < 5; i++)
    {
        auto &x = edges[i];
        mcmf.AddEdge(x[0], x[1], x[2], x[3]);
    }
    long long cost = 0;
    cout << mcmf.MincostMaxflow(0, 3, cost) << endl;
    cout << cost << endl;
}
