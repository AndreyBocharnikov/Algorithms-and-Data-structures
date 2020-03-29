#include <iostream>
#include <string>
using namespace std;

struct tree{
    long long l, r, mn, add, st;
};

tree t[400000];
long long a[100000];
const long long INF = 2 * 1000000000000000000;

void build(int v, int l, int r) {
    t[v].l = l;
    t[v].r = r;
    t[v].add = INF;
    t[v].st = INF;
    if (t[v].l == t[v].r) {
        t[v].mn = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    t[v].mn = min(t[v * 2].mn, t[v * 2 + 1].mn);
}

void push(int v) {
    // cout << v << " " << t[v].st << endl;
    if (t[v].st != INF) {
        t[v].mn = t[v].st;
        if (t[v].l != t[v].r) {
            t[v * 2].st = t[v].st;
            t[v * 2 + 1].st = t[v].st;
            t[v * 2].add = INF;
            t[v * 2 + 1].add = INF;
        }
        t[v].st = INF;
    }
    if (t[v].add != INF) {
        t[v].mn += t[v].add;
        if (t[v].l != t[v].r) {
            if (t[v * 2].add == INF) {
                t[v * 2].add = t[v].add;
            } else {
                t[v * 2].add += t[v].add;
            }
            if (t[v * 2 + 1].add == INF) {
                t[v * 2 + 1].add = t[v].add;
            } else {
                t[v * 2 + 1].add += t[v].add;
            }
        }
        t[v].add = INF;
    }
}

long long min(int v, int l, int r) {
    push(v);
    if (t[v].l > r || t[v].r < l)
        return INF;
    if (l <= t[v].l && t[v].r <= r)
        return t[v].mn;
    return min(min(v * 2, l, r), min(v * 2 + 1, l, r));
}

void update(int v, int l, int r, long long new_val, long long val) {
    push(v);
    if (t[v].l > r || t[v].r < l)
        return;
    if (l <= t[v].l && t[v].r <= r) {
        // cout << v << " " << new_val << " " << val << " ";
        if (new_val != INF)
            t[v].st = new_val;
        if (val != INF)
            t[v].add = val;
        // cout << t[v].st << endl;
        push(v);
        return;
    }
    update(v * 2, l, r, new_val, val);
    update(v * 2 + 1, l, r, new_val, val);
    t[v].mn = min(t[v * 2].mn, t[v * 2 + 1].mn);
    // cout << v * 2 << " " << t[v * 2].mn << endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    build(1, 0, n - 1);
    string s;
    int l, r, val;
    while (cin >> s >> l >> r) {
        l--;
        r--;
        if (s == "min")
            cout << min(1, l, r) << '\n';
        if (s == "add") {
            cin >> val;
            update(1, l, r, INF, val);
        }
        if (s == "set") {
            cin >> val;
            update(1, l, r, val, INF);
        }
    }
}
