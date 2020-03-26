#include <iostream>

using namespace std;

struct node {
    node *left, *right;
    int key;

    node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

node *root = nullptr;

node *insert(node *v, int val) {
    if (v == nullptr)
        return new node(val);
    if (v->key > val)
        v->left = insert(v->left, val);
    else
        v->right = insert(v->right, val);
    return v;
}

bool leaf(node *v) {
    return v->left == nullptr && v->right == nullptr;
}

int res = 0;

void next(node *v, int k) {
    if (v == nullptr)
        return;
    if (v->key > k) {
        res = min(res, v->key);
        next(v->left, k);
    } else {
        next(v->right, k);
    }
}

void prev(node *v, int k) {
    if (v == nullptr)
        return;
    if (v->key < k) {
        res = max(res, v->key);
        prev(v->right, k);
    } else {
        prev(v->left, k);
    }
}

node *dlt(node *v, int val) {
    if (v->key < val)
        v->right = dlt(v->right, val);
    if (v->key > val)
        v->left = dlt(v->left, val);
    if (v->key == val) {
        if (leaf(v))
            return nullptr;
        if (v->left == nullptr) {
            res = 2 * 1e9;
            next(root, v->key);
            int cur = res;
            v->right = dlt(v->right, res);
            // cout << v->key << " " << cur << endl;
            v->key = cur;
        } else {
            res = -2 * 1e9;
            prev(root, v->key);
            int cur = res;
            v->left = dlt(v->left, res);
            // cout << v->key << " " << cur << endl;
            v->key = cur;
        }
    }
    return v;
}

bool find(node *v, int val) {
    if (v == nullptr)
        return 0;
    if (v->key == val)
        return 1;
    if (v->key > val)
        return find(v->left, val);
    else
        return find(v->right, val);
}

void show(node *v) {
    if (v == nullptr)
        return;
    show(v->left);
    // cout << v->key << " ";
    show(v->right);
}

int main() {
    string s;
    int val;
    while (cin >> s) {
        cin >> val;
        if (s == "insert" && !find(root, val))
            root = insert(root, val);
        if (s == "delete" && find(root, val))
            root = dlt(root, val);
        if (s == "next") {
            res = 2 * 1e9;
            next(root, val);
            if (res == 2 * 1e9)
                cout << "none\n";
            else
                cout << res << "\n";
        }
        if (s == "prev") {
            res = -2 * 1e9;
            prev(root, val);
            if (res == -2 * 1e9)
                cout << "none\n";
            else
                cout << res << '\n';
        }
        if (s == "exists") {
            if (find(root, val))
                cout << "true\n";
            else
                cout << "false\n";
        }
    }
}
