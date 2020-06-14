#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv, graf;
vector <int> used, order, colored;

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

void top_sort(int v, int col) {
    colored[v] = col;
    for (size_t i = 0; i < graf[v].size(); i++) {
        int to = graf[v][i];
        if (colored[to])
            continue;
        top_sort(to, col);
    }
}

int main() {
    ifstream cin("cond.in");
    ofstream cout("cond.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    graf.resize(n + 1);
    used.resize(n + 1);
    colored.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        graf[t].push_back(f);
    }

    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dfs(i);
    }

    int col = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        if (!colored[v]) {
            col++;
            top_sort(v, col);
        }
    }
    cout << col << '\n';
    for (int i = 1; i <= n; i++)
        cout << colored[i] << " ";
}


