#include <bits/stdc++.h>

#define infinite 1152921504606846976
#define base 1000000007
#define maxn 5000500

using namespace std;

int primes[maxn];
long long table[maxn];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t, l, r;
    cin >> t >> l >> r;
    for (int j = 2; j < maxn; j++)
        primes[j] = j;
    for (int j = 2; j * j < maxn; j++)
        if (primes[j] == j)
            for (int i = j * j; i < maxn; i += j)
                primes[i] = min(j, primes[i]);
    table[1] = 0;
    for (int j = 2; j < maxn; j++) {
        table[j] = infinite;
        for (int x = j; x != 1; x /= primes[x])
            table[j] = min(table[j], 1LL * table[j / primes[x]] + 1LL * j * (primes[x] - 1) / 2LL);
    }
    int ans = 0;
    int cnt = 1;
    for (int j = l; j <= r; j++) {
        table[j] %= base;
        ans = (int) ((1LL * ans + 1LL * cnt * table[j]) % base);
        cnt = (int) ((1LL * cnt * t) % base);
    }
    cout << ans;
    return 0;
}