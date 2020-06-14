#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, dist, dp, ans;

void dfs(int v, int p) {
    used[v] = 1;
    dist[v] = dist[p] + 1;
    int rev_edge = 1e9;
    vector <int> children;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == p)
            continue;
        if (used[to]) {
            rev_edge = min(rev_edge, dist[to]);
            continue;
        }
        children.push_back(to);
        dfs(to, v);
        dp[v] = min(dp[v], dp[to]);
    }

    dp[v] = min(dp[v], rev_edge);
    // cout << v << " " << dp[v] << " ";
    if (v == p) {
        // cout << children.size() << '\n';
        if (children.size() > 1)
            ans.push_back(v);
        return;
    }
    for (int i : children) {
        // cout << dp[i] << " ";
        if (dp[i] >= dist[v]) {
            ans.push_back(v);
            break;
        }
    }
    // cout << '\n';
}

int main() {
    ifstream cin("points.in");
    ofstream cout("points.out");
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
        vv[f].push_back(t);
        vv[t].push_back(f);
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dist[i] = -1,
            dfs(i, i);
    }
    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (int i : ans)
        cout << i << '\n';
}
/*
5 6
1 2
1 3
2 4
3 5
1 4
1 5

5 4
1 2
1 3
2 4
3 5

3 3
1 2
2 3
1 3
*/
