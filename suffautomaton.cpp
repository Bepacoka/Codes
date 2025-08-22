#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int INF = 1e9;

struct node {
    map <char, node*> go;
    node *link = nullptr;
    int maxlen = 0;
};

node *last, *root;
void extend(char ch) {
    node *cur = new node;
    cur->maxlen = last->maxlen + 1;
    auto p = last;
    while (p && !p->go.count(ch)) {
        p->go[ch] = cur;
        p = p->link;
    }
    if (!p) {
        cur->link = root;
        last = cur;
        return;
    }
    auto q = p->go[ch];
    if (q->maxlen == p->maxlen + 1) {
        cur->link = q;
    } else {
       auto new_q = new node(*q);
       new_q->maxlen = p->maxlen + 1;
       cur->link = new_q;
       q->link = new_q;
       while (p && p->go[ch] == q) {
           p->go[ch] = new_q;
           p = p->link;
       }
    }
    last = cur;
}

bool check(const string &s) {
    auto cur = root;
    for (auto ch : s) {
        if (!cur->go.count(ch)) return false;
        cur = cur->go[ch];
    }
    return true;
}

void add(const string &s) {
    for (auto ch : s) extend(ch);
}
