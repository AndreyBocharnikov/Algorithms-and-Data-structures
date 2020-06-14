#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, inf = 1e9;
    cin >> n >> m;
    set <pair<int, int> > dp;
    vector <vector <pair<int, int> > > vv(n + 1);
    vector <int> dist(n + 1, inf);
    dist[1] = 0;
    for (int i = 2; i <= n; i++)
        dp.insert({inf, i});
    dp.insert({0, 1});
    for (int i = 0; i < m; i++) {
        int f, t, cost;
        cin >> f >> t >> cost;
        vv[f].push_back({t, cost});
        vv[t].push_back({f, cost});
    }

    while (!dp.empty()) {
        auto p = *dp.begin();
        dp.erase(dp.begin());
        // cout << p.f << " " << p.s << endl;
        for (size_t i = 0; i < vv[p.s].size(); i++) {
            int to = vv[p.s][i].f, cost = vv[p.s][i].s;
            // cout << to << " ";
            if (p.f + cost < dist[to]) {
                dp.erase({dist[to], to});
                dist[to] = p.f + cost;
                dp.insert({dist[to], to});
                // cout << '!' << to << '\n';
            }
        }
        // cout << endl;
    }

    for (int i = 1; i <= n; i++)
        cout << dist[i] << " ";
}
