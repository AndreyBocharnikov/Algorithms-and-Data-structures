#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

set<int> R;
vector <vector <int> > vv;
vector <int> used, p;

void dfs(int v) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        R.insert(to);
        if (!used[p[to]])
            dfs(p[to]);
    }
}

int main() {
    // ifstream cin("std.in");
    // ofstream cout("std")
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vv.resize(m + 1);
    used.resize(m + 1);
    p.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int to;
            cin >> to;
            vv[i].push_back(to);
        }
    }
    vector <int> from;
    for (int i = 1; i <= m; i++) {
        int r;
        cin >> r;
        if (r == 0)
            from.push_back(i);
        else
            p[r] = i;
    }
    for (size_t i = 0; i < from.size(); i++) {
        int v = from[i];
        if (!used[v])
            dfs(v);
    }
    vector <int> L;
    for (int i = 1; i <= m; i++)
        if (!used[i])
            L.push_back(i);
    cout << R.size() + L.size() << '\n';
    cout << L.size() << " ";
    for (size_t i = 0; i < L.size(); i++) {
        cout << L[i] << " ";
    }
    cout << '\n' << R.size() << " ";
    for (int i : R)
        cout << i << " ";
}

