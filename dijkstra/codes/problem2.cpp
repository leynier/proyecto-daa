#include <bits/stdc++.h>

using namespace std;

const int maxn = 300;
const int mod = int(1e9) + 7;
const long long inf = numeric_limits<long long>::max();

class OverflowInteger {
public:
    OverflowInteger(long long n = 0) : x(n) {
    }

    OverflowInteger operator+(const OverflowInteger &other) {
        if (x > inf - other.x) {
            return inf;
        }

        return x + other.x;
    }

    OverflowInteger operator*(const OverflowInteger &other) {
        if (other.x != 0 and x > inf / other.x) {
            return inf;
        }

        return x * other.x;
    }

    friend ostream &operator<<(ostream &out, const OverflowInteger &a) {
        out << a.x;
        return out;
    }

    bool operator==(const OverflowInteger &other) const {
        return x == other.x;
    }

    bool operator<(const OverflowInteger &other) const {
        return x < other.x;
    }

private:
    long long x;
};

long long dist[maxn][maxn];
int edge[maxn][maxn];
OverflowInteger ways[maxn][maxn];
bool used[maxn];

int dist_order[maxn];
OverflowInteger dp[maxn][maxn + 1][2];
int dp_ways[maxn][maxn + 1][2];
int n, k;

void dijkstra(long long dist[], OverflowInteger ways[], int node) {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    dist[node] = 0;
    ways[node] = 1;
    for (int i = 0; i < n - 1; ++i) {
        int best_node = -1;
        for (int j = 0; j < n; ++j)
            if (not used[j] and (best_node == -1 or dist[best_node] > dist[j]))
                best_node = j;
        used[best_node] = true;
        for (int j = 0; j < n; ++j) {
            if (not used[j] and edge[best_node][j]) {
                if (dist[j] > dist[best_node] + edge[best_node][j]) {
                    dist[j] = dist[best_node] + edge[best_node][j];
                    ways[j] = ways[best_node];
                } else if (dist[j] == dist[best_node] + edge[best_node][j])
                    ways[j] = ways[j] + ways[best_node];
            }
        }
    }
}

void compute(int to) {
    dp[to][0][0] = ways[0][dist_order[to]];
    dp_ways[to][0][0] = 1;
    if (dist[0][dist_order[to]] + dist[dist_order[to]][n - 1] == dist[0][n - 1]) {
        dp[to][1][1] = ways[0][dist_order[to]];
        dp_ways[to][1][1] = 1;
    }
    for (int taken = 1; taken <= k; ++taken) {
        for (int from = 0; from < to; ++from) {
            OverflowInteger cost_ignore = dp[from][taken][1] * ways[dist_order[from]][dist_order[to]];
            if (dp[to][taken][0] < cost_ignore) {
                dp[to][taken][0] = cost_ignore;
                dp_ways[to][taken][0] = dp_ways[from][taken][1];
            } else if (cost_ignore == dp[to][taken][0]) {
                dp_ways[to][taken][0] += dp_ways[from][taken][1];
                if (dp_ways[to][taken][0] >= mod)
                    dp_ways[to][taken][0] -= mod;
            }
            if (dist[0][dist_order[from]] + dist[dist_order[from]][dist_order[to]] + dist[dist_order[to]][n - 1] == dist[0][n - 1]) {
                OverflowInteger cost_from = dp[from][taken - 1][1] * ways[dist_order[from]][dist_order[to]];
                if (dp[to][taken][1] < cost_from) {
                    dp[to][taken][1] = cost_from;
                    dp_ways[to][taken][1] = dp_ways[from][taken - 1][1];
                } else if (cost_from == dp[to][taken][1]) {
                    dp_ways[to][taken][1] += dp_ways[from][taken - 1][1];
                    if (dp_ways[to][taken][1] >= mod)
                        dp_ways[to][taken][1] -= mod;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = inf;
    for (int i = 0; i < m; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        --x;
        --y;
        edge[x][y] = edge[y][x] = c;
    }
    for (int i = 0; i < n; ++i)
        dijkstra(dist[i], ways[i], i);
    for (int i = 0; i < n; ++i)
        dist_order[i] = i;
    sort(dist_order, dist_order + n, [](const int &x, const int &y) {
        return dist[0][x] < dist[0][y];
    });
    dp[0][0][0] = dp[0][1][1] = 1;
    dp_ways[0][0][0] = dp_ways[0][1][1] = 1;
    for (int i = 1; i < n; ++i) {
        compute(i);
        if (dist_order[i] == n - 1) {
            int all = dp_ways[i][k][1];
            if (dp[i][k][1] == dp[i][k][0]) {
                all += dp_ways[i][k][0];
                if (all >= mod)
                    all -= mod;
            }
            cout << dp[i][k][1] << ' ' << all << endl;
            return 0;
        }
    }
}