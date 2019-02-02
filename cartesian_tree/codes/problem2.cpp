#include <bits/stdc++.h>
#define mod 1000000007

using namespace std;

long long ret, fact[100005], inv[100005];
int n, m, i, j, odd, sum, kk[10];
char a[100005];

struct node {
    int prior, key[10], cnt, own;
    node *l, *r;
    bool rev;

    node() {}

    node(int t) {
        key[0] = key[1] = key[2] = key[3] = key[4] = key[5] = key[6] = key[7] = key[8] = key[9] = 0;
        key[t] = 1;
        rev = false;
        l = r = NULL;
        cnt = 1;
        own = t;
        prior = ((rand()) << 15) + rand();
    }
};

typedef node *pnode;

pnode root, t1, t2, t3, t4;

int qt, L, R;

int cnt(pnode t) {
    if (!t)return 0; else return t->cnt;
}

void update(pnode t) {
    if (t->rev) {
        if (t->l)t->l->rev ^= 1;
        if (t->r)t->r->rev ^= 1;
        swap(t->l, t->r);
        t->rev = 0;
    }
    t->cnt = cnt(t->l) + 1 + cnt(t->r);
    for (int j = 0; j < 10; j++) {
        t->key[j] = 0;
        if (t->l)
            t->key[j] += t->l->key[j];
        if (t->r)
            t->key[j] += t->r->key[j];
    }
    ++t->key[t->own];
}

void split(pnode t, int key, pnode &l, pnode &r, int add = 0) {
    if (!t)return void(l = r = NULL);
    update(t);
    int cur_key = add + cnt(t->l) + 1;
    if (key <= cur_key)
        split(t->l, key, l, t->l, add), r = t;
    else
        split(t->r, key, t->r, r, add + 1 + cnt(t->l)), l = t;
    update(t);
}

void merge(pnode &t, pnode l, pnode r) {
    if (l)
        update(l);
    if (r)
        update(r);
    if (!l || !r)t = l ? l : r;
    else if (l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    update(t);
}

long long pw(long long t, long long k) {
    if (k == 1)return t;
    long long q = pw(t, k / 2);
    q = (q * q) % mod;
    if (k % 2)
        q = (q * t) % mod;
    return q;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    scanf("%d%d", &n, &m);
    fact[0] = 1;
    inv[0] = 1;
    for (i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = pw(fact[i], mod - 2);
        a[i] = getchar();
        while (a[i] < 'a' || a[i] > 'z')
            a[i] = getchar();
        merge(root, root, new node(a[i] - 'a'));
    }
    for (i = 1; i <= m; i++) {
        scanf("%d %d %d", &qt, &L, &R);
        if (qt == 1) {
            split(root, L, t1, t2);
            split(t2, R - L + 2, t3, t4);
            t3->rev ^= 1;
            merge(t2, t3, t4);
            merge(root, t1, t2);
        } else {
            split(root, L, t1, t2);
            split(t2, R - L + 2, t3, t4);
            for (j = 0, odd = 0, sum = 0; j < 10; j++) {
                kk[j] = t3->key[j];
                if (kk[j] % 2)
                    ++odd;
                kk[j] /= 2;
                sum += kk[j];
            }
            if (odd > 1)puts("0");
            else {
                ret = fact[sum];
                for (j = 0; j < 10; j++)
                    ret = (ret * inv[kk[j]]) % mod;
                printf("%lld\n", ret);
            }
            merge(t2, t3, t4);
            merge(root, t1, t2);
        }
    }
    return 0;
}