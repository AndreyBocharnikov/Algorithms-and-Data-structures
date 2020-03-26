#include <bits/stdc++.h>

#define s second
using namespace std;

struct node {
    int val, lvl;
    node *l, *r;

    node(int v, int level, node *left, node *right) {
        val = v;
        lvl = level;
        l = left;
        r = right;
    }
};

node *root = nullptr;

node *skew(node *t) {
    if (t == nullptr)
        return nullptr;
    if (t->l == nullptr)
        return t;
    if (t->l->lvl == t->lvl) {
        node *cur = new node(t->val, t->lvl, t->l->r, t->r);
        return new node(t->l->val, t->l->lvl, t->l->l, cur);
    } else {
        return t;
    }
}

node *split(node *t) {
    if (t == nullptr)
        return nullptr;
    if (t->r == nullptr || t->r->r == nullptr)
        return t;
    if (t->lvl == t->r->r->lvl) {
        node *cur = new node(t->val, t->lvl, t->l, t->r->l);
        return new node(t->r->val, t->r->lvl + 1, cur, t->r->r);
    } else {
        return t;
    }
}

bool leaf(node *t) {
    if (t->l == nullptr && t->r == nullptr)
        return 1;
    return 0;
}

int mn(node *t) {
    if (t == nullptr)
        return 0;
    return t->lvl;
}

node *decrease_lvl(node *t) {
    int should_be = min(mn(t->l), mn(t->r)) + 1;
    if (should_be < t->lvl) {
        t->lvl = should_be;
        if (should_be < mn(t->r))
            t->r->lvl = should_be;
    }
    return t;
}

int res = 0;

void next(node *v, int k) {
    if (v == nullptr)
        return;
    if (v->val > k) {
        res = min(res, v->val);
        next(v->l, k);
    } else {
        next(v->r, k);
    }
}

void prev(node *v, int k) {
    if (v == nullptr)
        return;
    if (v->val < k) {
        res = max(res, v->val);
        prev(v->r, k);
    } else {
        prev(v->l, k);
    }
}

node *delet(node *t, int k) {
    if (t == nullptr)
        return nullptr;
    if (k > t->val)
        t->r = delet(t->r, k);
    if (k < t->val)
        t->l = delet(t->l, k);
    if (k == t->val) {
        if (leaf(t))
            return nullptr;
        if (t->l == nullptr) {
            res = 1e9;
            next(root, k);
            t->r = delet(t->r, res);
            t->val = res;
        } else {
            res = -1 * 1e9;
            prev(root, k);
            t->l = delet(t->l, res);
            t->val = res;
        }
    }
    t = decrease_lvl(t);
    t = skew(t);
    if (t->r != nullptr) {
        t->r = skew(t->r);
        if (t->r->r != nullptr)
            t->r->r = skew(t->r->r);
    }
    t = split(t);
    t->r = split(t->r);
    return t;
}

node *insert(node *v, int k) {
    if (v == nullptr)
        return new node(k, 1, nullptr, nullptr);
    if (k < v->val)
        v->l = insert(v->l, k);
    else
        v->r = insert(v->r, k);
    v = skew(v);
    v = split(v);
    return v;
}

bool find(node *v, int k) {
    if (v == nullptr)
        return 0;
    if (v->val == k)
        return 1;
    if (v->val > k)
        return find(v->l, k);
    else
        return find(v->r, k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    int val;

    while (cin >> s) {
        cin >> val;
        if (s == "insert" && !find(root, val))
            root = insert(root, val);
        if (s == "exists") {
            if (find(root, val))
                cout << "true\n";
            else
                cout << "false\n";
        }
        if (s == "next") {
            res = 1 * 1e9;
            next(root, val);
            if (res == 1 * 1e9)
                cout << "none\n";
            else
                cout << res << "\n";
        }
        if (s == "prev") {
            res = -1 * 1e9;
            prev(root, val);
            if (res == -1 * 1e9)
                cout << "none\n";
            else
                cout << res << "\n";
        }
        if (s == "delete" && find(root, val))
            root = delet(root, val);
    }
}

