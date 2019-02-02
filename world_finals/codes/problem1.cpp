#include <bits/stdc++.h>

using namespace std;

string word;
int nodes = 0;
map<string, int> words;
vector<bool> commas(0);
vector<int> fixed_commas;
vector<string> text;
vector<bool> dots;

vector<vector<int> > sides;

void bfs(int node) {
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int act = q.front();
        q.pop();
        if (!commas[act]) {
            commas[act] = true;
            for (int i = 0; i < sides[act].size(); ++i)
                q.push(sides[act][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    bool first = true;
    while (cin >> word) {
        bool dot = false, comma = false;
        if (word.back() == ',') {
            word.pop_back();
            comma = true;
        } else if (word.back() == '.') {
            word.pop_back();
            dot = true;
        }
        if (words.find(word) == words.end())
            words[word] = nodes++;
        int index = words[word];
        if (comma)
            fixed_commas.push_back(index);
        if (first || dots.back()) {
            first = false;
            text.push_back(word);
            dots.push_back(dot);
            continue;
        }
        text.push_back(word);
        dots.push_back(dot);
    }
    sides.assign(2 * nodes + 5, vector<int>(0));
    commas.assign(2 * nodes + 5, false);
    for (int i = 1; i < text.size(); ++i) {
        int y = words[text[i]];
        int x = words[text[i - 1]];
        if (dots[i - 1])
            continue;
        sides[2 * x + 1].push_back(2 * y);
        sides[2 * y].push_back(2 * x + 1);
    }
    for (int i = 0; i < fixed_commas.size(); ++i)
        bfs(2 * fixed_commas[i] + 1);
    for (int i = 0; i < text.size(); ++i) {
        cout << text[i];
        int index = words[text[i]];
        if (dots[i])
            cout << ".";
        else if (commas[2 * index + 1])
            cout << ",";
        if (i + 1 < text.size())
            cout << " ";
    }
    return 0;
}
