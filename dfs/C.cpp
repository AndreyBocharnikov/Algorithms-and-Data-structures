#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, int> > > vv;
vector <int> used, order, w;

void dfs(int v) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f;
        if (used[to]) {
            continue;
        }
        dfs(to);
    }
    order.push_back(v);
}

int main() {
    ifstream cin("shortpath.in");
    ofstream cout("shortpath.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, s, t;
    int inf = 1e9;
    cin >> n >> m >> s >> t;
    vv.resize(n + 1);
    used.resize(n + 1);
    w.resize(n + 1, inf);
    for (int i = 0; i < m; i++) {
        int f, t, x;
        cin >> f >> t >> x;
        vv[f].push_back({t, x});
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dfs(i);
    }

    reverse(order.begin(), order.end());
    int id = 0;
    while (order[id] != s) {
        id++;
    }

    w[s] = 0;
    for (size_t i = id; i < order.size(); i++) {
        int v = order[i];
        for (size_t j = 0; j < vv[v].size(); j++) {
            int to = vv[v][j].f, c = vv[v][j].s;
            w[to] = min(w[to], w[v] + c);
        }
    }

    if (w[t] == inf) {
        cout << "Unreachable";
    } else {
        cout << w[t];
    }
}



