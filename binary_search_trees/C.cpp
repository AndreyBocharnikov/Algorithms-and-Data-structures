#include <iostream>
#include <algorithm>

using namespace std;

struct tree {
    tree *l, *r;
    int key, pr, sz;

    tree(int k) {
        key = k;
        pr = rand();
        sz = 1;
        l = nullptr;
        r = nullptr;
    }
};

int size(tree *v) {
    if (v == nullptr)
        return 0;
    return v->sz;
}

void upd(tree *v) {
    if (v == nullptr)
        return;
    v->sz = size(v->l) + size(v->r) + 1;
}

void merge(tree *&T, tree *L, tree *R) {
    if (L == nullptr) {
        T = R;
        return;
    }
    if (R == nullptr) {
        T = L;
        return;
    }

    if (L->pr > R->pr) {
        merge(L->r, L->r, R);
        T = L;
    } else {
        merge(R->l, L, R->l);
        T = R;
    }
    upd(T);
}

void split(tree *T, tree *&L, tree *&R, int k) {
    if (T == nullptr) {
        L = nullptr;
        R = nullptr;
        return;
    }
    int siz = size(T->l) + 1;
    if (siz <= k) {
        split(T->r, T->r, R, k - siz);
        L = T;
    } else {
        split(T->l, L, T->l, k);
        R = T;
    }
    upd(L);
    upd(R);
}

void show(tree *v) {
    if (v == nullptr)
        return;
    show(v->l);
    cout << v->key << " ";
    show(v->r);
}

int main() {
    int n, q;
    cin >> n >> q;
    tree *root = nullptr;
    tree *a = nullptr;
    tree *b = nullptr;
    tree *c = nullptr;
    tree *d = nullptr;
    for (int i = 1; i <= n; i++)
        merge(root, root, new tree(i));

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        split(root, a, b, r);
        split(a, c, d, l - 1);
        merge(a, d, c);
        merge(root, a, b);
    }
    show(root);
}
