#include "bits/stdc++.h"

using namespace std;

const int MAX = 2000;
const int inf = (int) 1e9;
int n, p, temp;
vector<int> taxi, passenger;
vector<vector<pair<int, int>>> graph(MAX + 5);

bool bmp(int i, const vector<vector<int>> &w, vector<int> &mr, vector<int> &mc, vector<int> &seen) {
    for (int j = 0; j < w[i].size(); ++j) {
        if (w[i][j] && !seen[j]) {
            seen[j] = true;
            if (mc[j] < 0 || bmp(mc[j], w, mr, mc, seen)) {
                mr[i] = j;
                mc[j] = i;
                return true;
            }
        }
    }
    return false;
}

int maxBMP(const vector<vector<int>> &w, vector<int> &mr, vector<int> &mc) {
    mr = vector<int>(w.size(), -1);
    mc = vector<int>(w[0].size(), -1);
    int ct = 0;
    for (int i = 0; i < w.size(); ++i) {
        vector<int> seen(w[0].size());
        if (bmp(i, w, mr, mc, seen))
            ++ct;
    }
    return ct;
}

vector<int> dijkstra(int start) {
    vector<int> dist(n + p + 5, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
    dist[start] = 0;
    queue.push(pair<int, int>(0, start));
    while (!queue.empty()) {
        pair<int, int> top = queue.top();
        queue.pop();
        int v = top.second, cost = top.first;
        if (cost <= dist[v]) {
            for (int i = 0; i < graph[v].size(); ++i) {
                int v2 = graph[v][i].first, d = graph[v][i].second;
                if (dist[v2] > dist[v] + d) {
                    dist[v2] = dist[v] + d;
                    queue.push({dist[v2], v2});
                }
            }
        }
    }
    return dist;
}

void build(vector<int> &disTh, vector<vector<int>> &distTaxi, vector<vector<int>> &v) {
    vector<int> speed, ttime;
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        speed.push_back(temp);
    }
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        ttime.push_back(temp);
    }
    for (int i = 0; i < n; ++i) {
        int capacity = speed[i] * ttime[i];
        for (int j = 0; j < p; ++j) {
            int totaldist = disTh[passenger[j]] + distTaxi[i][passenger[j]];
            if (totaldist <= capacity) {
                v[i][j] = 1;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt, r, x, y, d;
    cin >> tt;
    while (tt--) {
        cin >> n >> p >> r;
        for (int i = 0; i < MAX; ++i)
            graph[i].clear();
        vector<vector<int>> v(505, vector<int>(1005, 0));
        vector<vector<int>> distTaxi(505);
        taxi.clear();
        passenger.clear();
        for (int i = 0; i < n; ++i) {
            cin >> temp;
            taxi.push_back(temp);
        }
        for (int i = 0; i < p; ++i) {
            cin >> temp;
            passenger.push_back(temp);
        }
        for (int i = 0; i < r; ++i) {
            cin >> x >> y >> d;
            graph[x].push_back({y, d});
            graph[y].push_back({x, d});
        }
        vector<int> distTh = dijkstra(n + p + 1);
        for (int i = 0; i < n; ++i)
            distTaxi[i] = dijkstra(taxi[i]);
        build(distTh, distTaxi, v);
        vector<int> left(505, -1), right(1005, -1);
        cout << maxBMP(v, left, right) << '\n';
    }
}