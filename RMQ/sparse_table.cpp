#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, u, v, l, r;
    cin >> n >> m >> a >> u >> v;
    l = min(u, v);
    r = max(u, v);
    vector <int> arr(n + 1);
    vector <vector <int> > sparse_table(n + 1, vector <int> (25));
    arr[1] = a;
    sparse_table[1][0] = a;
    for (int i = 2; i <= n; i++) {
        arr[i] = (23 * arr[i - 1] + 21563) % 16714589;
        sparse_table[i][0] = arr[i];
    }
    for (int i = 1; i < 25; i++) {
        for (int j = 1; j <= n; j++) {
            int mn = min(n, j + (1 << (i - 1)));
            sparse_table[j][i] = min(sparse_table[j][i - 1], sparse_table[mn][i - 1]);
        }
    }
    vector <int> dp(n + 1);
    dp[1] = 0;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i / 2] + 1;
    int len = r - l + 1, left = r - (1 << dp[len]) + 1;
    int ans = min(sparse_table[l][dp[len]], sparse_table[left][dp[len]]);
    for (int i = 2; i <= m; i++) {
        int du = ((17 * u + 751 + ans + 2 * (i - 1)) % n) + 1;
        int dv = ((13 * v + 593 + ans + 5 * (i - 1)) % n) + 1;
        l = min(du, dv);
        r = max(du, dv);
        len = r - l + 1;
        left = r - (1 << dp[len]) + 1;
        ans = min(sparse_table[l][dp[len]], sparse_table[left][dp[len]]);
        u = du;
        v = dv;
    }
    cout << u << " " << v << " " << ans;
}

