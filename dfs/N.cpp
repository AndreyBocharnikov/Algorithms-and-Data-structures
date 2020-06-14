#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, int> > > vv, graf;
vector <int> used, colored, order;

void dfs(int v, int cost) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].f, cur_cost = vv[v][i].s;
        if (used[to] || cur_cost > cost)
            continue;
        dfs(to, cost);
    }
    order.push_back(v);
}

void top_sort(int v, int col, int cost) {
    colored[v] = col;
    for (size_t i = 0; i < graf[v].size(); i++) {
        int to = graf[v][i].f, cur_cost = graf[v][i].s;
        if (colored[to] || cur_cost > cost)
            continue;
        top_sort(to, col, cost);
    }
}

int main() {
    ifstream cin("avia.in");
    ofstream cout("avia.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, l = -1, r = 1e9;
    cin >> n;
    vv.resize(n);
    graf.resize(n);
    used.resize(n);
    colored.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cost;
            cin >> cost;
            if (i == j)
                continue;
            vv[i].push_back({j, cost});
            graf[j].push_back({i, cost});
        }
    }
    while (r - l > 1) {
        int m = (l + r) / 2;
        bool ok = true;
        for (int i = 0; i < n; i++)
            colored[i] = 0,
            used[i] = 0;
        order.clear();

        for (int i = 0; i < n; i++)
            if (!used[i])
                dfs(i, m);

        top_sort(order.back(), 1, m);
        for (int i = 0; i < n; i++)
            ok &= colored[i];

        if (ok)
            r = m;
        else
            l = m;
    }
    cout << r;
}
