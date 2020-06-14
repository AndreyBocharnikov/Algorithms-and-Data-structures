#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <int> sz, p;

struct edge {
    int cost, f, t;
};

int get(int x) {
    if (x == p[x])
        return x;
    return p[x] = get(p[x]);
}

void unio(int x, int y) {
    if (sz[x] > sz[y]) {
        swap(x, y);
    }

    p[x] = y;
    sz[y] += sz[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    ll ans = 0;
    cin >> n >> m;
    sz.resize(n + 1);
    p.resize(n + 1);
    for (int i = 1; i <= n; i++)
        sz[i] = 1,
        p[i] = i;
    vector <edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].f >> edges[i].t >> edges[i].cost;
    }
    sort(edges.begin(), edges.end(), [](edge a, edge b) {return a.cost < b.cost;});

    for (int i = 0; i < m; i++) {
        int f = get(edges[i].f), t = get(edges[i].t);
        // cout << f << " " << t << endl;
        if (f == t)
            continue;
        unio(f, t);
        ans += edges[i].cost;
    }

    cout << ans;
}

