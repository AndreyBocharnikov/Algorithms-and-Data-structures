#include <iostream>

using namespace std;

struct node {
    node *l, *r;
    int pr, key, sz;

    node(int k) {
        l = nullptr;
        r = nullptr;
        key = k;
        sz = 1;
        pr = rand();
    }
};

int size(node *v) {
    if (v == nullptr)
        return 0;
    return v->sz;
}

void upd(node *v) {
    v->sz = size(v->l) + size(v->r) + 1;
}

node *merge(node *root1, node *root2) {
    if (root1 == nullptr)
        return root2;
    if (root2 == nullptr)
        return root1;
    if (root1->pr > root2->pr) {
        root1->r = merge(root1->r, root2);
        upd(root1);
        return root1;
    } else {
        root2->l = merge(root1, root2->l);
        upd(root2);
        return root2;
    }
}

int find(node *v, int k) {
    // cout << v->key << " ";
    int sz = size(v->l) + 1;
    if (sz == k)
        return v->key;
    if (sz < k)
        return find(v->r, k - sz);
    else
        return find(v->l, k);
}

pair<node *, node *> splite(node *v, int k) {
    if (v == nullptr)
        return {nullptr, nullptr};
    if (v->key <= k) {
        auto cur = splite(v->r, k);
        v->r = cur.first;
        upd(v);
        return {v, cur.second};
    } else {
        auto cur = splite(v->l, k);
        v->l = cur.second;
        upd(v);
        return {cur.first, v};
    }
}

void show(node *v) {
    if (v == nullptr)
        return;
    show(v->l);
    cout << v->key << " ";
    show(v->r);
}

int main() {
    int n;
    cin >> n;
    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        int x, val;
        cin >> x >> val;
        if (x == 1) {
            auto cur = splite(root, val);
            cur.first = merge(cur.first, new node(val));
            root = merge(cur.first, cur.second);
        }
        if (x == -1) {
            auto cur = splite(root, val);
            auto mid = splite(cur.first, val - 1);
            root = merge(mid.first, cur.second);
        }
        if (x == 0) {
            cout << find(root, root->sz - val + 1) << '\n';
        }
    }
}

