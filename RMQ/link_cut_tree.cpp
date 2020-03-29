#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
using namespace std;

struct node{
    node *left, *right, *parent, *link;
    int sz, val;
    bool rev;

    node(node* l, node* r, node* p, int v) {
        left = l;
        right = r;
        parent = p;
        link = nullptr;
        sz = 1;
        val = v;
        rev = 0;
    }
};

vector <vector <int> > vv;
vector <node*> nodes;
vector <node*> rev_link;
vector <int> cur, par, cur_cnt;

int size(node* v) {
    if (v == nullptr)
        return 0;
    return v->sz;
}

void recomp(node * v) {
    v->sz = size(v->left) + size(v->right) + 1;
}

void set_parent(node* child, node* parent) {
    if (child != nullptr)
        child->parent = parent;
}

void reverse(node* v) {
    if (v == nullptr)
        return;
    v->rev ^= 1;
}

void push(node* v) {
    if (v == nullptr || !v->rev)
        return;
    swap(v->left, v->right);
    v->rev = false;
    reverse(v->left);
    reverse(v->right);
}

void keep_parent(node* v) {
    set_parent(v->left, v);
    set_parent(v->right, v);
    recomp(v);
}

void rotate(node* parent, node* child) {
    node* gparent = parent->parent;
    if (gparent != nullptr) {
        if (gparent->left == parent) {
            gparent->left = child;
        } else {
            gparent->right = child;
        }
    }

    if (parent->left == child)
        parent->left = child->right,
        child->right = parent;
    else
        parent->right = child->left,
        child->left = parent;
    keep_parent(parent);
    keep_parent(child);
    child->parent = gparent;
}

node* splay(node* v) {
    if (v->parent == nullptr)
        return v;
    node* p = v->parent;
    node* gp = p->parent;
    if (gp == nullptr) {
        rotate(p, v);
        return v;
    } else {
        bool zig_zig = (gp->left == p) == (p->left == v);
        if (zig_zig) {
            rotate(gp, p);
            rotate(p, v);
        } else {
            rotate(p, v);
            rotate(gp, v);
        }
        return splay(v);
    }
}

node* find(node* v, int key) {
    if (v == nullptr)
        return nullptr;
    push(v);
    int cur_sz = size(v->left);
    if (cur_sz == key)
        return splay(v);
    if (key < cur_sz && v->left != nullptr)
        return find(v->left, key);
    if (key > cur_sz && v->right != nullptr)
        return find(v->right, key - cur_sz - 1);
    return splay(v);
}

node* tree_root(node* v) {
    return find(v, 0);
}

pair<node*, node*> splite(node* v, int key) {
    if (v == nullptr)
        return {nullptr, nullptr};
    v = find(v, key);
    if (v->sz <= key)
        return {v, nullptr};
    set_parent(v->left, nullptr);
    v->left = nullptr;
    recomp(v);
    return {v->left, v};
}

node* merge(node* left, node* right) {
    if (right == nullptr)
        return left;
    if (left == nullptr)
        return right;
    right = tree_root(right);
    right->left = left;
    keep_parent(right);
    return right;
}

node* insert(node* v, int key, int val) {
    auto p = splite(v, key);
    v = new node(p.f, p.s, nullptr, val);
    v->sz = size(v->left) + size(v->right) + 1;
    keep_parent(v);
    return v;
}

void make_array(node* v) {
    if (v == nullptr)
        return;
    nodes[v->val] = v;
    make_array(v->left);
    make_array(v->right);
}

node* build(vector <int> &tree) {
    node* root = nullptr;
    for (size_t i = 0; i < tree.size(); i++)
        root = insert(root, int(i), tree[i]);
    make_array(root);
    return root;
}

void dfs(int v, int p) {
    cur.push_back(v);
    par[v] = p;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == p)
            continue;
        cur_cnt[v]++;
        dfs(to, v);
        if (cur.size() == 0)
            continue;
        node* cur_root = build(cur);
        int start = tree_root(cur_root)->val;
        if (cur_cnt[par[start]] > 1) {
            nodes[start]->link = nodes[par[start]];
        }
        cur.clear();
    }
}

void clean_up(node* v) {
    if (v == nullptr)
        return;
    clean_up(v->parent);
    push(v);
}

node* support_root(node* v) {
    clean_up(v);
    return splay(v);
}

node* cut_out(node* v) {
    support_root(v);
    auto p = splite(v, size(v->left) + 1);
    if (p.s != nullptr)
        tree_root(p.s)->link = v;
    return v;
}

node* expose(node* v) {
    v = tree_root(cut_out(v));
    while (v->link != nullptr) {
        node* next = cut_out(v->link);
        v->link = nullptr;
        v = tree_root(merge(next, v));
    }
    return v;
}

void revert(node* v) {
    node* root = expose(v);
    reverse(support_root(root));
}

int lca(int v, int u) {
    if (v == u)
        return v;
    expose(nodes[u]);
    expose(nodes[v]);
    node* check = tree_root(support_root(nodes[u]));
    if (check->link == nullptr) {
        expose(nodes[v]);
        expose(nodes[u]);
        return tree_root(support_root(nodes[v]))->link->val;
    }
    return tree_root(support_root(nodes[u]))->link->val;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, t, f;
    while (true) {
        vv.clear();
        nodes.clear();
        cur_cnt.clear();
        par.clear();
        cin >> n;
        if (n == 0)
            break;
        vv.resize(n + 1);
        nodes.resize(n + 1);
        cur_cnt.resize(n + 1);
        par.resize(n + 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> f >> t;
            vv[f].push_back(t);
            vv[t].push_back(f);
        }
        dfs(1, 1);
        int q, u, v;
        cin >> q;
        for (int i = 0; i < q; i++) {
            char x;
            cin >> x;
            if (x == '?') {
                cin >> u >> v;
                cout << lca(u, v) << '\n';
            } else {
                cin >> v;
                revert(nodes[v]);
            }
        }
    }
}


