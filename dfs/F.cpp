#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, order, w;

void dfs(int v) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (used[to]) {
            continue;
        }
        dfs(to);
    }
    order.push_back(v);
}

int main() {
    ifstream cin("hamiltonian.in");
    ofstream cout("hamiltonian.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    used.resize(n + 1);
    w.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dfs(i),
            cnt++;
    }

    reverse(order.begin(), order.end());

    for (size_t i = 0; i < order.size(); i++) {
        int v = order[i];
        // cout << v << " ";
        for (size_t j = 0; j < vv[v].size(); j++) {
            int to = vv[v][j];
            w[to] = max(w[to], w[v] + 1);
        }
    }

    bool ans = false;
    for (int i = 1; i <= n; i++) {
        if (w[i] == n - 1)
            ans = true;
    }

    if (ans) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
