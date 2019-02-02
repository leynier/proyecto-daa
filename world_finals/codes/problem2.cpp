#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int mn = 0;
        vector<int> list;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            list.push_back(s.size());
            mn = max(mn, list.back());
        }
        int ret = 0;
        int retw = -1;
        for (int w = mn;; ++w) {
            vector<int> cur(w);
            vector<int> next(w);
            int cs = -1, nline = 1;
            for (int vi = 0; vi < list.size(); ++vi) {
                if (cs + list[vi] >= w) {
                    cur.swap(next);
                    next = vector<int>(w);
                    cs = -1;
                    ++nline;
                }
                if (cs >= 0) {
                    next[cs] = max(cur[cs - 1] + 1, max(cur[cs] + 1, cur[cs + 1] + 1));
                    if (next[cs] > ret) {
                        ret = next[cs];
                        retw = w;
                    }
                }
                cs += list[vi] + 1;
            }
            if (ret >= nline)
                break;
        }
        cout << retw << " " << ret << endl;
    }
}