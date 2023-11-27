#include <bits/stdc++.h>

using namespace std;

typedef int T;

struct Node {
    T key = 0, priority = 0;
    Node *left = nullptr, *right = nullptr;
    explicit Node(T key = 0, T priority = 0, Node* left = nullptr, Node* right = nullptr) : key(key), priority(priority), left(left), right(right) {}
};

pair<Node*, Node*> split(Node* root, T key) {
    if (root == nullptr)
        return {nullptr, nullptr};
    if (root->key < key) {
        pair<Node*, Node*> result = split(root->right, key);
        root->right = result.first;
        return {root, result.second};
    } else {
        pair<Node*, Node*> result = split(root->left, key);
        root->left = result.second;
        return {result.first, root};
    }
}

Node* merge(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void insert(Node*& root, Node* x) {
    if (root == nullptr) {
        root = x;
        return;
    }
    if (x->priority > root->priority) {
        pair <Node*, Node*> a = split(root, x->key);
        x->left = a.first, x->right = a.second;
        root = x;
    } else if (root->key < x->key) {
        insert(root->right, x);
    } else {
        insert(root->left, x);
    }
}

void erase(Node*& root, T key) {
    if (root == nullptr) return;
    if (root->key == key)
        root = merge(root->left, root->right);
    else if (root->key < key)
        erase(root->right, key);
    else
        erase(root->left, key);
}

bool is_in(Node* root, T x) {
    if (root == nullptr) return false;
    if (root->key == x) return true;
    if (root->key < x)
        return is_in(root->right, x);
    else
        return is_in(root->left, x);
}

int main() {
    Node* root = nullptr;
}
