#include <iostream>
#include <vector>
#define ll long long
#define f first
#define s second
#define pr pair <int, int>
using namespace std;

vector < vector <pr> > vv, children;
vector <pair <pr, pr> > edge;
int cnt[501], sz[501], dp2[501], dist[501];
int dp[2][500001];

void dfs(int v, int p) {
    sz[v] = 1;
    for (int i = 0; i < int(vv[v].size()); i++) {
        int to = vv[v][i].f, id = vv[v][i].s;
        if (to == p)
            continue;
        dist[to] = dist[v] + 1;
        dfs(to, v);
        children[v].push_back({to, id});
        sz[v] += sz[to];
    }
}

void dfs2(int v) {
    int n = int(children[v].size());
    if (n == 0)
        return;
    vector <int> prf(n), suf(n);
    prf[0] = sz[children[v][0].f];
    suf[n - 1] = sz[children[v][n - 1].f];
    for (int i = 1; i < n; i++)
        prf[i] = prf[i - 1] + sz[children[v][i].f];
    for (int i = n - 2; i >= 0; i--)
        suf[i] = suf[i + 1] + sz[children[v][i].f];
    for (int i = 0; i < n; i++) {
        int to = children[v][i].f;
        if (i > 0)
            dp2[to] += prf[i - 1];
        if (i < n - 1)
            dp2[to] += suf[i + 1];
        dfs2(to);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int mod = 1000000007;
    int n, m;
    cin >> n >> m;
    vector <int> prf(n), suf(n);
    if (n > 500)
        return cout << 0, 0;
    if (n == 1)
        return cout << 0, 0;
    vv.resize(n + 1);
    children.resize(n + 1);
    edge.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int t, f, a, b;
        cin >> f >> t >> a >> b;
        vv[f].push_back({t, i});
        vv[t].push_back({f, i});
        edge[i] = {{f, t}, {a, b}};
    }
    if (n == 2) {
        if (m % 2 == 0 && edge[0].s.f <= m / 2 && edge[0].s.s >= m / 2)
            cout << 1;
        else
            cout << 0;
        return 0;
    }
    dfs(1, 1);
    dfs2(1);
    for (int i = 0; i < n - 1; i++) {
        int f = edge[i].f.f, t = edge[i].f.s;
        if (dist[f] > dist[t])
            swap(f, t);
        cnt[i] = 2 * sz[t] * (sz[1] - sz[f] + 1 + dp2[t]);
    }
    for (int i = 0; i < n - 1; i++)
        m -= cnt[i] * edge[i].s.f;
    if (m < 0)
        return cout << 0, 0;
    dp[0][0] = 1;
    for (int i = 1; i <= n - 1; i++) {
        int k = cnt[i - 1];
        ll val = 1LL * k * (edge[i - 1].s.s - edge[i - 1].s.f + 1);
        // cout << i - 1 << " " << k << " " << val << '\n';
        for (int j = 0; j <= m; j++) {
            dp[1][j] = dp[0][j];
            if (j >= k)
                dp[1][j] += dp[1][j - k];
            dp[1][j] %= mod;
            if (j >= val)
                dp[1][j] -= dp[0][j - val];
            if (dp[1][j] < 0)
                dp[1][j] += mod;
        }
        for (int j = 0; j <= m; j++)
            dp[0][j] = dp[1][j],
            dp[1][j] = 0;
        // cout << '\n';
    }
    cout << dp[0][m];
}
