#include <bits/stdc++.h>

using namespace std;

const int maxn = int(1e5) + 10;
const long long inf = (long long) 1e16;

int n, m, s, vis[maxn], sub[maxn];
vector<pair<int, int>> graph[maxn];
vector<int> path[maxn];
long long dist[maxn];

namespace DominatorTree {
    vector<int> graph[maxn], tree[maxn], reverse_graph[maxn], bucket[maxn];
    int sdom[maxn], idom[maxn], parent[maxn], dsu[maxn], label[maxn], arr[maxn], rev[maxn], time;

    int find(int u, int x = 0) {
        if (u == dsu[u])
            return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0)
            return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }

    void merge(int u, int v) {
        dsu[v] = u;
    }

    void dfs0(int u) {
        ++time;
        arr[u] = time;
        rev[time] = u;
        label[time] = time;
        sdom[time] = time;
        dsu[time] = time;
        for (int i = 0; i < graph[u].size(); ++i) {
            int w = graph[u][i];
            if (!arr[w]) {
                dfs0(w);
                parent[arr[w]] = arr[u];
            }
            reverse_graph[arr[w]].push_back(arr[u]);
        }
    }

    void dfs1(int u, int p, int sub[]) {
        sub[u] = 1;
        for (auto w : tree[u]) {
            if (w != p) {
                dfs1(w, u, sub);
                sub[u] += sub[w];
            }
        }
    }

    void reset(int n) {
        for (int i = 1; i <= n; ++i) {
            graph[i].clear();
            reverse_graph[i].clear();
            tree[i].clear();
            arr[i] = 0;
        }
        time = 0;
    }

    void add_edge(int u, int v) {
        graph[u].push_back(v);
    }

    void get(int n, int root, int sub[]) {
        dfs0(root);
        n = time;
        for (int i = n; i >= 1; --i) {
            for (int j = 0; j < reverse_graph[i].size(); ++j)
                sdom[i] = min(sdom[i], sdom[find(reverse_graph[i][j])]);
            if (i > 1)
                bucket[sdom[i]].push_back(i);
            for (int j = 0; j < bucket[i].size(); ++j) {
                int w = bucket[i][j];
                int v = find(w);
                if (sdom[v] == sdom[w])
                    idom[w] = sdom[w];
                else
                    idom[w] = v;
            }
            if (i > 1)
                merge(parent[i], i);
        }
        for (int i = 2; i <= n; ++i) {
            if (idom[i] != sdom[i])
                idom[i] = idom[idom[i]];
            tree[rev[i]].push_back(rev[idom[i]]);
            tree[rev[idom[i]]].push_back(rev[i]);
        }
        dfs1(rev[1], rev[1], sub);
    }
}

int dijkstra(int root) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = inf;
        path[i].clear();
    }
    DominatorTree::reset(n);
    dist[root] = 0;
    memset(vis, 0, sizeof(vis));
    set<pair<long long, int>> S;
    S.insert({dist[root], root});
    while (!S.empty()) {
        int u = S.begin()->second;
        S.erase(S.begin());
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto w : graph[u])
            if (dist[u] + w.second < dist[w.first]) {
                dist[w.first] = dist[u] + w.second;
                path[w.first].clear();
                path[w.first].push_back(u);
                S.insert({dist[w.first], w.first});
            } else if (dist[u] + w.second == dist[w.first])
                path[w.first].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        for (auto j : path[i])
            DominatorTree::add_edge(j, i);
    DominatorTree::get(n, root, sub);
    int mx = 0;
    for (int i = 1; i <= n; ++i)
        if (i != root)
            mx = max(mx, sub[i]);
    return mx;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> s;
    int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    cout << dijkstra(s);
    return 0;
}