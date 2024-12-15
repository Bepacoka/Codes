#include <bits/stdc++.h>

using namespace std;

constexpr int ALPH_SIZE = 'z' - 'a' + 1;
constexpr char START = 'a';

struct Node {
    char c;
    bool is_term;
    vector<int> ind;
    Node *parent;
    Node *suff;
    Node *term;
    Node *children[ALPH_SIZE]{};

    Node() {
        c = '\0';
        is_term = false;
        ind = {};
        parent = nullptr;
        suff = nullptr;
        term = nullptr;
        for (auto &i: children) {
            i = nullptr;
        }
    }

    Node(char c, Node *parent) : c(c), parent(parent) {
        is_term = false;
        ind = {};
        suff = nullptr;
        term = nullptr;
        for (auto &i: children) {
            i = nullptr;
        }
    }
};

Node *init() {
    Node *root = new Node;
    root->suff = root;
    return root;
}

void add_word(Node *root, const string &s, int ind) {
    Node *cur = root;
    for (auto c: s) {
        if (!cur->children[c - START]) {
            cur->children[c - START] = new Node(c, cur);
        }
        cur = cur->children[c - START];
    }
    cur->is_term = true;
    cur->ind.push_back(ind);
}

Node *move(Node *cur, char c);

Node *get_suff(Node *cur) {
    if (cur->suff) {
        return cur->suff;
    }
    if (!cur->parent->parent) {
        cur->suff = cur->parent;
    } else {
        cur->suff = move(get_suff(cur->parent), cur->c);
    }
    get_suff(cur->suff);
    if (cur->suff->is_term) {
        cur->term = cur->suff;
    } else {
        cur->term = cur->suff->term;
    }

    return cur->suff;
}

Node *move(Node *cur, char c) {
    if (cur->children[c - START]) {
        return cur->children[c - START];
    }
    if (!cur->parent) {
        return cur;
    }
    return cur->children[c - START] = move(get_suff(cur), c);
}
