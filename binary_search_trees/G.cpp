#include <iostream>

using namespace std;

struct node {
    node *l, *r;
    long long sum, pr, key, sz;

    node(long long k) {
        sum = k;
        key = k;
        sz = 1;
        pr = rand();
        l = nullptr;
        r = nullptr;
    }
};

long long sz(node *v) {
    if (v == nullptr)
        return 0;
    return v->sz;
}

long long sum(node *v) {
    if (v == nullptr)
        return 0LL;
    return v->sum;
}

void upd(node *v) {
    if (v == nullptr)
        return;
    v->sum = sum(v->l) + sum(v->r) + v->key;
    v->sz = sz(v->l) + sz(v->r) + 1;
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

pair<node *, node *> split(node *root, long long val) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (root->key <= val) {
        auto cur = split(root->r, val);
        root->r = cur.first;
        upd(root);
        return {root, cur.second};
    } else {
        auto cur = split(root->l, val);
        root->l = cur.second;
        upd(root);
        return {cur.first, root};
    }
}

bool find(node *v, long long val) {
    if (v == nullptr)
        return false;
    if (v->key == val)
        return true;
    if (v->key > val)
        return find(v->l, val);
    else
        return find(v->r, val);
}

void show(node *v) {
    if (v == nullptr)
        return;
    show(v->l);
    cout << v->key << " ";
    show(v->r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, mod = 1e9;
    long long last = -1, val;
    cin >> n;
    node *root = nullptr;
    for (int i = 0; i < n; i++) {
        char x;
        int l, r;
        cin >> x;
        if (x == '+') {
            cin >> val;
            if (last != -1)
                val = (last + val) % mod;
            if (find(root, val)) {
                last = -1;
                continue;
            }
            auto cur = split(root, val);
            root = merge(cur.first, new node(val));
            root = merge(root, cur.second);
            last = -1;
        } else {
            cin >> l >> r;
            auto frst = split(root, r);
            auto mid = split(frst.first, l - 1);
            last = sum(mid.second);
            cout << last << '\n';
            frst.first = merge(mid.first, mid.second);
            root = merge(frst.first, frst.second);
        }
    }
}

