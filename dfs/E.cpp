#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, ans;

void dfs(int v) {
    used[v] = 1;
    ans.push_back(v);
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (used[to] == 1) {
            cout << "YES\n";
            bool ok = 0;
            for (size_t j = 0; j < ans.size(); j++) {
                if (ok || ans[j] == to) {
                    ok = 1;
                    cout << ans[j] << " ";
                }
            }
            exit(0);
        }
        if (used[to] == 2) {
            continue;
        }
        dfs(to);
    }
    ans.pop_back();
    used[v] = 2;
}

int main() {
    ifstream cin("cycle.in");
    ofstream cout("cycle.out");
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

    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    cout << "NO";
}

