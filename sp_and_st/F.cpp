#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

struct edge {
    int a, b, cost;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, inf = 2 * 1e9;
    int no_edge = 1e9;
    cin >> n;
    m = n * n;
    vector <int> dist(n + 1, inf);
    vector <edge> edges(n * n);
    vector <int> p(n + 1);
    int id = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            edges[id].a = i;
            edges[id].b = j;
            cin >> edges[id++].cost;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (edges[j].cost == no_edge)
                continue;
            int f = edges[j].a, t = edges[j].b;
            if (dist[f] == inf) {
                dist[t] = edges[j].cost;
                dist[f] = 0;
            } else {
                if (dist[t] > dist[f] + edges[j].cost) {
                    dist[t] = dist[f] + edges[j].cost;
                    p[t] = f;
                }
            }
        }
    }

    int x = -1;
    for (int j = 0; j < m; j++) {
        if (edges[j].cost == no_edge)
            continue;
        int f = edges[j].a, t = edges[j].b;
        if (dist[t] > dist[f] + edges[j].cost) {
            dist[t] = dist[f] + edges[j].cost;
            p[t] = f;
            x = t;
        }
    }

    if (x == -1)
        return cout << "NO", 0;
    cout << "YES\n";
    vector <int> ans;
    for (int j = 0; j < n; j++)
        x = p[x];
    int end_ = x, cur = end_;
    ans.push_back(cur);
    while (p[cur] != end_) {
        ans.push_back(p[cur]);
        cur = p[cur];
    }
    ans.push_back(end_);
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i : ans)
        cout << i + 1 << " ";
}

