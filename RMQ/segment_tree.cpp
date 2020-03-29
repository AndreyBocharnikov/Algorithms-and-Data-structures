#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <int> a, tree;
int inf = 1000000001;

void build(int v, int l, int r) {
    if (l == r) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int query(int v, int l, int r, int tl, int tr) {
    if (tl <= l && r <= tr) {
        return tree[v];
    }
    if (l > tr || r < tl) {
        return inf;
    }
    int m = (l + r) / 2;
    int res_l = query(v * 2, l, m, tl, tr);
    int res_r = query(v * 2 + 1, m + 1, r, tl, tr);
    return min(res_l, res_r);
}

void update(int v, int l, int r, int pos, int val) {
    if (l == r) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos <= m)
        update(v * 2, l, m, pos, val);
    else
        update(v * 2 + 1, m + 1, r, pos, val);
    tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, l, r, pos, val;
    cin >> n;
    a.resize(n);
    tree.resize(4 * n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(1, 0, n - 1);
    string s;
    while (cin >> s) {
        if (s == "min") {
            cin >> l >> r;
            l--;
            r--;
            cout << query(1, 0, n - 1, l, r) << '\n';
        } else {
            cin >> pos >> val;
            pos--;
            update(1, 0, n - 1, pos, val);
        }
    }
}

