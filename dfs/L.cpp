#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, int> > > vv;
vector <int> used, dist, dp, ans, colors;

void dfs(int v, int p) {
    used[v] = 1;
    dist[v] = dist[p] + 1;
    int rev_edge = 1e9;
    vector <int> children;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f;
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
}

void dfs2(int v, int p, int col, int edge = -1) {
    used[v] = 1;
    ans[edge + 1] = col;
    // cout << v << " " << edge << " " << col << '\n';
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f, next_edge = vv[v][i].s;
        if (to == p)
            continue;
        if (used[to]) {
            if (ans[next_edge + 1] == 0) {
                ans[next_edge + 1] = col;
            }
            continue;
        }

        if (dp[to] < dist[v]) {
            dfs2(to, v, col, next_edge);
        } else {
            // cout << v << " " << to << '\n';
            int new_color = colors.back() + 1;
            colors.push_back(new_color);
            dfs2(to, v, new_color, next_edge);
        }
    }
}

int main() {
    ifstream cin("biconv.in");
    ofstream cout("biconv.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    dist.resize(n + 1);
    used.resize(n + 1);
    ans.resize(m + 1);
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

    used.assign(n + 1, 0);
    colors.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dfs2(i, i, 0);
    }
    cout << colors.size() - 1 << '\n';
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
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

6 7
1 2
2 3
1 3
3 4
4 5
5 6
4 6
*/

