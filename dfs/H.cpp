#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, int> > > vv;
vector <int> used, dist, dp, ans;

void dfs(int v, int p, int edge = -1) {
    // cout << v << endl;
    used[v] = 1;
    dist[v] = dist[p] + 1;
    int min_rev = 1e9;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f, next_edge = vv[v][i].s;
        if (to == p)
            continue;
        if (used[to]) {
            min_rev = min(min_rev, dist[to]);
            continue;
        }
        dfs(to, v, next_edge);
        dp[v] = min(dp[v], dp[to]);
    }
    // cout << v << " " << min_rev << " " << dp[v] << '\n';
    dp[v] = min(dp[v], min_rev);
    // cout << dp[v] << " " << dist[v] << '\n';
    if (dp[v] >= dist[v] && edge != -1)
        ans.push_back(edge);
}

int main() {
    ifstream cin("bridges.in");
    ofstream cout("bridges.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    dist.resize(n + 1);
    used.resize(n + 1);
    dp.resize(n + 1, 1e9);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back({t, i});
        vv[t].push_back({f, i});
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dist[i] = -1,
            dfs(i, i);
    }
    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (int i : ans)
        cout << i + 1 << " ";
}
