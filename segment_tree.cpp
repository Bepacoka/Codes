#include <vector>

using namespace std;

template <typename T>
struct node {
    size_t l = -1, r = 0;
    T val = {};

    node() = default;

    node(size_t l, size_t r, T val) : l(l), r(r), val(val) {}
};

template <typename T>
node<T> operator+(const node<T>& first, const node<T>& second) {
    return {first.l, second.r, first.val + second.val};
}

template <typename T>
struct segment_tree {
    vector <node<T>> tree;

    explicit segment_tree(const vector <T>& arr) {
        tree.resize(4 * arr.size());
        build(1, 0, arr.size(), arr);
    }

    void build(size_t v, size_t tl, size_t tr, const vector <T>& arr) {
        if (tl + 1 == tr) {
            tree[v] = {tl, tr, arr[tl]};
            return;
        }

        size_t tm = (tl + tr) / 2;
        build(2 * v, tl, tm, arr);
        build(2 * v + 1, tm, tr, arr);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    node<T> get(size_t v, size_t l, size_t r) {
        if (l <= tree[v].l and tree[v].r <= r) return tree[v];
        if (r <= tree[v].l or tree[v].r <= l) return {};
        return get(2 * v, l, r) + get(2 * v + 1, l, r);
    }

    T get(size_t l, size_t r) {
        return get(1, l, r).val;
    }

    void update(size_t v, size_t ind, T val) {
        if (tree[v].l + 1 == tree[v].r) {
            tree[v].val = val;
            return;
        }

        int m = (tree[v].l + tree[v].r) / 2;
        if (ind < m) update(2 * v, ind, val);
        else update(2 * v + 1, ind, val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    void update(size_t ind, T val) {
        update(1, ind, val);
    }
};
