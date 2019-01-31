#include <bits/stdc++.h>

using namespace std;

long long n, l, h;
bool table[1000001];
vector<long long> primes;

long long logarithm(long long a, long long b) {
    long long answer = 1;
    for (long long i = b; i >= 1; i /= 2)
        while (pow(a, answer + i) <= b)
            answer += i;
    return answer;
}

long long root(long long a, long long b) {
    long long answer = 1;
    for (long long i = b; i >= 1; i /= 2)
        while (pow(answer + i, a) <= b)
            answer += i;
    return answer;
}

void sieve() {
    for (long long i = 2; i < 1001; ++i)
        if (!table[i])
            for (long long j = 2 * i; j < 1000001; j += i)
                table[j] = true;
    for (long long i = 2; i < 1000001; ++i)
        if (!table[i])
            primes.push_back(i);
}

long long solve(long long length, long long limit) {
    long long counter = 0;
    for (int i = 2; i <= length; ++i)
        counter += upper_bound(primes.begin(), primes.end(), root(i, limit)) - primes.begin();
    return counter;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    sieve();
    cin >> n;
    while (n--) {
        cin >> l >> h;
        long long k = logarithm(2, h);
        long long counter = solve(k, h);
        if (l > 3)
            counter -= solve(k, l - 1);
        cout << counter << "\n";
    }
    return 0;
}