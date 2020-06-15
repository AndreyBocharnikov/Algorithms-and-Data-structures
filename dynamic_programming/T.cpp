#include <fstream>
#include <vector>
#define ll long long
#define f first
#define s second

using namespace std;
const int N = 3 * 1e5 + 1;
vector < vector <int> > vv, children;
ll dp[N], sz[N], dp2[N];

void dfs(int v, int p) {
    sz[v] = 1;
    for (int i = 0; i < int(vv[v].size()); i++) {
        int to = vv[v][i];
        if (to == p)
            continue;
        children[v].push_back(to);
        dfs(to, v);
        dp[v] += dp[to] + sz[to];
        sz[v] += sz[to];
    }
}

void dfs1(int v) {
    int n = int(children[v].size());
    if (n == 0)
        return;
    vector <ll> prf(n), suf(n);
    prf[0] = 2 * sz[children[v][0]] + dp[children[v][0]];
    suf[n - 1] = 2 * sz[children[v][n - 1]] + dp[children[v][n - 1]];
    for (int i = 1; i < n; i++) {
        int to = children[v][i];
        prf[i] = prf[i - 1] + 2 * sz[to] + dp[to];
    }
    for (int i = n - 2; i >= 0; i--) {
        int to = children[v][i];
        suf[i] = suf[i + 1] + 2 * sz[to] + dp[to];
    }
    for (int i = 0; i < n; i++) {
        int to = children[v][i];
        dp2[to] = dp2[v] + sz[1] - sz[v] + 1;
        if (i > 0)
            dp2[to] += prf[i - 1];
        if (i < n - 1)
            dp2[to] += suf[i + 1];
        dfs1(to);
    }
}

int main() {
    ifstream cin("treedp.in");
    ofstream cout("treedp.out");
    int n;
    cin >> n;
    vv.resize(n + 1);
    children.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        vv[t].push_back(f);
    }
    dfs(1, 1);
    dfs1(1);
    for (int i = 2; i <= n; i++)
        cout << dp[i] * (sz[1] - sz[i]) + dp2[i] * sz[i] << '\n';
}
