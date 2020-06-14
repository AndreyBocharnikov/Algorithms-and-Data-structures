#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used, dp;

bool dfs(int v) {
    bool win = 0;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (dp[to] == -1)
            dp[to] = !dfs(to);
        win |= dp[to];
    }
    dp[v] = win;
    return win;
}

int main() {
    ifstream cin("game.in");
    ofstream cout("game.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, s;
    cin >> n >> m >> s;
    vv.resize(n + 1);
    dp.resize(n + 1, -1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
    }

    if (dfs(s)) {
        cout << "First player wins\n";
    } else {
        cout << "Second player wins\n";
    }
}
/*
3 3
1 3
1 2
2 3
*/

