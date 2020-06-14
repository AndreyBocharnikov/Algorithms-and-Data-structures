#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, order, w;

void dfs(int v, vector <int> &tmp) {
    used[v] = 1;
    tmp.push_back(v);
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (used[to]) {
            continue;
        }
        dfs(to, tmp);
    }
}

int main() {
    ifstream cin("components.in");
    ofstream cout("components.out");
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
        vv[t].push_back(f);
    }

    int cnt = 0;
    vector <int> tmp, ans(n + 1);
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            cnt++;
            dfs(i, tmp);
            for (int j : tmp)
                ans[j] = cnt;
            tmp.clear();
        }
    }
    cout << cnt << '\n';
    for (size_t i = 1; i < ans.size(); i++)
        cout << ans[i] << " ";
}
