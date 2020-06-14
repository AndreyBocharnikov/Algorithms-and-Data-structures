#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

int const N = 201;
int dp[N][N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, inf = 1e9;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        for (int v = 1; v <= n; v++) {
            for (int u = 1; u <= n; u++) {
                dp[i][v][u] = inf;
            }
            dp[i][v][v] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        int f, t, cost;
        cin >> f >> t >> cost;
        dp[0][f][t] = cost;
    }

    for (int i = 1; i <= n; i++) {
        for (int v = 1; v <= n; v++) {
            for (int u = 1; u <= n; u++) {
                dp[i][v][u] = min(dp[i - 1][v][u], dp[i - 1][v][i] + dp[i - 1][i][u]);
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        for (int u = 1; u <= n; u++) {
            cout << dp[n][v][u] << ' ';
        }
        cout << '\n';
    }
}

