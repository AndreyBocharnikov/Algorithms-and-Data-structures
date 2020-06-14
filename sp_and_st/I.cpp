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
    int ans = 2 * 1e9;
    for (int j = 0; j < m; j++) {
        for (int i = 1; i <= n; i++) {
            sz[i] = 1;
            p[i] = i;
        }
        int mx = -1 * 1e9, cnt = 0;
        for (int i = j; i < m; i++) {
            int f = get(edges[i].f), t = get(edges[i].t);
            // cout << f << " " << t << endl;
            if (f == t)
                continue;
            unio(f, t);
            cnt++;
            mx = max(mx, edges[i].cost);
        }
        if (cnt == n - 1) {
            ans = min(ans, mx - edges[j].cost);
        }
    }
    if (ans == 2 * 1e9) {
        cout << "NO";
    } else {
        cout << "YES\n" << ans;
    }
}
