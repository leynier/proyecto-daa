#include <bits/stdc++.h>

using namespace std;

vector<int> prime;
int result;
int a, b;

void sieve(int limit) {
    bool mark[limit+1];
    memset(mark, true, sizeof(mark));
    for (int p = 2; p * p < limit; ++p)
        if (mark[p])
            for (int i = p * p; i < limit; i += p)
                mark[i] = false;
    for (int p = 2; p < limit; p++) {
        if (mark[p]) {
            prime.push_back(p);
            if ((p % 4 == 1 || p ==2) && p >= a && p <= b)
                ++result;
        }
    }
}

void segmented_sieve(int n) {
    int limit = (int) floor(sqrt(n)) + 1;
    sieve(limit);
    int low = limit;
    int high = 2 * limit;
    while (low < n) {
        if (high >= n)
            high = n;
        bool mark[limit + 1];
        memset(mark, true, sizeof(mark));
        for (int i = 0; i < prime.size(); i++) {
            int loLim = (int) floor(low / prime[i]) * prime[i];
            if (loLim < low)
                loLim += prime[i];
            for (int j = loLim; j < high; j += prime[i])
                mark[j - low] = false;
        }
        for (int i = low; i < high; i++)
            if (mark[i - low])
                if ((i % 4 == 1 || i == 2) && i >= a && i <= b)
                    ++result;
        low = low + limit;
        high = high + limit;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b;
    segmented_sieve(b + 1);
    cout << result;
    return 0;
}