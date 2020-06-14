#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, ans;

bool dfs(int v) {
    used[v] = 1;
    bool res = false;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (used[to] == 1)
            return 1;
        if (used[to] == 2) {
            continue;
        }
        res |= dfs(to);
    }
    ans.push_back(v);
    used[v] = 2;
    return res;
}

int main() {
    ifstream cin("topsort.in");
    ofstream cout("topsort.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    used.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
    }

    bool can = false;
    for (int i = 1; i <= n; i++) {
        if (!used[i])
            can |= dfs(i);
    }

    if (can) {
        cout << -1;
    } else {
        reverse(ans.begin(), ans.end());
        for (int i : ans)
            cout << i << " ";
    }
}

