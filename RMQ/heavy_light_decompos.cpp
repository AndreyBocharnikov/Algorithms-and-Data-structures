#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
using namespace std;

vector <vector <int> > vv, pr;
const int N = 3 * 100001;
int tin[N], tout[N], dist[N], sz[N], path[N], head[N], ar[N], id[N];
ll tree[4 * N], lazy[4 * N];
int timer = 0;
int n;

void dfs(int v, int p) {
    timer++;
    tin[v] = timer;
    pr[v][0] = p;
    sz[v] = 1;
    for (int i = 1; i < 22; i++) {
        int u = pr[v][i - 1];
        pr[v][i] = pr[u][i - 1];
    }
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == p)
            continue;
        dist[to] = dist[v] + 1;
        dfs(to, v);
        sz[v] += sz[to];
    }
    tout[v] = timer;
}

bool anc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
    if (anc(v, u))
        return v;
    if (anc(u, v))
        return u;
    for (int i = 21; i >= 0; i--) {
        int cur = pr[v][i];
        if (!anc(cur, u))
            v = cur;
    }
    return pr[v][0];
}

int path_number = 0, index = 0;
void hld(int v) {
    id[v] = index++;
    if (head[path_number] == 0) {
        head[path_number] = v;
    }
    path[v] = path_number;
    int heavy = -1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == pr[v][0])
            continue;
        if (heavy == -1 || sz[to] > sz[heavy])
            heavy = to;
    }
    if (heavy == -1)
        return;
    hld(heavy);
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == heavy || to == pr[v][0])
            continue;
        path_number++;
        hld(to);
    }
}

void push(int v, int l, int r) {
    if (lazy[v] > 0) {
        tree[v] += lazy[v];
        if (l != r)
            lazy[v * 2] += lazy[v],
            lazy[v * 2 + 1] += lazy[v];
        lazy[v] = 0;
    }
}

void update(int v, int l, int r, int tl, int tr, int val) {
    push(v, l, r);
    if (tl > r || tr < l)
        return;
    if (tl <= l && r <= tr) {
        lazy[v] += val;
        push(v, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(v * 2, l, m, tl, tr, val);
    update(v * 2 + 1, m + 1, r, tl, tr, val);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

void add(int v, int u, int val) {
    while (!anc(head[path[v]], u)) {
        update(1, 0, n - 1, id[head[path[v]]], id[v], val);
        v = pr[head[path[v]]][0];
    }

    while (!anc(head[path[u]], v)) {
        update(1, 0, n - 1, id[head[path[u]]], id[u], val);
        u = pr[head[path[u]]][0];
    }
    int l = min(id[u], id[v]), r = max(id[u], id[v]);
    update(1, 0, n - 1, l, r, val);
}

ll query(int v, int l, int r, int pos) {
    push(v, l, r);
    if (l == r) {
        return tree[v];
    }
    int m = (l + r) / 2;
    if (pos <= m)
        return query(v * 2, l, m, pos);
    else
        return query(v * 2 + 1, m + 1, r, pos);
}

ll get(int v) {
    return query(1, 0, n - 1, id[v]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    vv.resize(n + 1);
    pr.resize(n + 1, vector <int> (22));
    for (int i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        vv[t].push_back(f);
    }
    dfs(1, 1);
    hld(1);
    int q, u, v, val;
    cin >> q;
    for (int i = 0; i < q; i++) {
        char x;
        cin >> x;
        if (x == '+') {
            cin >> u >> v >> val;
            add(u, v, val);
        } else {
            cin >> v;
            cout << get(v) << '\n';
        }
    }
}

