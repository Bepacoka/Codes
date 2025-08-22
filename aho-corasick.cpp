#include <bits/stdc++.h>

using namespace std;

struct Node {
    int go[26] = {};
    int suff, term_suff;
    bool term;
    vector<pair <int, int>> ind;
    Node() : suff(0), term_suff(0), term(false) {}
};

Node trie[(int)1e6 + 1];
int last = 1;
void add_string(const string &s, int cur, int ind) {
    for (const auto ch: s) {
        if (!trie[cur].go[ch - 'a']) {
            trie[cur].go[ch - 'a'] = trie.size();
            trie.emplace_back();
        }
        cur = trie[cur].go[ch - 'a'];
    }
    trie[cur].term = true;
    trie[cur].ind.push_back({ind, 1});
}

void suff_build(const int root) {
    queue <int> q;
    trie[root].suff = root;
    for (int c = 0; c < 26; c++) {
        if (trie[root].go[c]) {
            trie[root].go[c] = trie[root].go[c];
            trie[trie[root].go[c]].suff = root;
            q.push(trie[root].go[c]);
        } else {
            trie[root].go[c] = root;
        }
    }
    while (!q.empty()) {
        const auto v = q.front();
        q.pop();
        for (int c = 0; c < 26; ++c) {
            if (trie[v].go[c]) {
                trie[trie[v].go[c]].suff = trie[trie[v].suff].go[c];
                if (trie[trie[trie[v].go[c]].suff].term) trie[trie[v].go[c]].term_suff = trie[trie[v].go[c]].suff;
                else trie[trie[v].go[c]].term_suff = trie[trie[trie[v].go[c]].suff].term_suff;
                q.push(trie[v].go[c]);
            } else {
                trie[v].go[c] = trie[trie[v].suff].go[c];
            }
        }
    }
}
