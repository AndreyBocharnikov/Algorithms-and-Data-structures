#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

struct parsoch {
    parsoch(int left_size, int right_size, vector <vector <int> > vv)
    : n(left_size), m(right_size), graf(vv) {
        p.resize(m + 1, -1);
        used.resize(n + 1, -1);
        in_parsoch.resize(n + 1);
    }

    bool dfs(int v) {
        used[v] = 1;
        for (size_t i = 0; i < graf[v].size(); i++) {
            int to = graf[v][i];
            if (p[to] == -1 || (!used[p[to]] && dfs(p[to]))) {
                p[to] = v;
                in_parsoch[v] = true;
                return true;
            }
        }
        return false;
    }

    int solve() {
        while (true) {
            used.assign(n + 1, 0);
            bool ok = false;
            for (int i = 1; i <= n; i++) {
                if (!used[i] && !in_parsoch[i]) {
                    ok |= dfs(i);
                }
            }
            if (!ok)
                break;
        }
        int ans = 0;
        for (int i = 1; i <= m; i++) {
            if (p[i] != -1) {
                ans++;
            }
        }
        return ans;
    }


 private:
    int n, m;
    vector <vector <int> > graf;
    vector <int> p, used, in_parsoch;
};

int main() {
    // ifstream cin("std.in");
    // ofstream cout("std")
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector <vector <int> > vv(n + 1);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        vv[l].push_back(r);
    }
    parsoch model = parsoch(n, n, vv);
    cout << n - model.solve();
}
