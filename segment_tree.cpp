#include <vector>

typedef int T;

struct node {
    std::size_t l = -1, r = 0;
    T val = {};

    node() = default;

    node(std::size_t l, std::size_t r, T val) : l(l), r(r), val(val) {}
};

node operator+(const node& first, const node& second) {
    return {first.l, second.r, first.val + second.val};
}

struct segment_tree {
    std::vector <node> tree;

    explicit segment_tree(const std::vector <T>& arr) {
        tree.resize(4 * arr.size());
        build(1, 0, arr.size(), arr);
    }

    void build(std::size_t v, std::size_t tl, std::size_t tr, const std::vector <T>& arr) {
        if (tl + 1 == tr) {
            tree[v] = {tl, tr, arr[tl]};
            return;
        }

        std::size_t tm = (tl + tr) / 2;
        build(2 * v, tl, tm, arr);
        build(2 * v + 1, tm, tr, arr);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    node get(std::size_t v, std::size_t l, std::size_t r) {
        if (l <= tree[v].l and tree[v].r <= r) return tree[v];
        if (r <= tree[v].l or tree[v].r <= l) return {};
        return get(2 * v, l, r) + get(2 * v + 1, l, r);
    }

    T get(std::size_t l, std::size_t r) {
        return get(1, l, r).val;
    }

    void update(std::size_t v, std::size_t ind, T val) {
        if (tree[v].l + 1 == tree[v].r) {
            tree[v].val = val;
            return;
        }

        int m = (tree[v].l + tree[v].r) / 2;
        if (ind < m) update(2 * v, ind, val);
        else update(2 * v + 1, ind, val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    void update(std::size_t ind, T val) {
        update(1, ind, val);
    }
};
