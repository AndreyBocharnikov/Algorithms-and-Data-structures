#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> colored;
bool ans = true;

void dfs(int v, int col) {
    colored[v] = col;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (colored[to] == col) {
            ans = false;
            continue;
        }
        if (colored[to] == 3 - col)
            continue;
        dfs(to, 3 - col);
    }
}

int main() {
    ifstream cin("bipartite.in");
    ofstream cout("bipartite.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    colored.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        vv[t].push_back(f);
    }

    for (int i = 1; i <= n; i++) {
        if (!colored[i])
            dfs(i, 1);
    }
    if (ans)
        cout << "YES";
    else
        cout << "NO";
}
