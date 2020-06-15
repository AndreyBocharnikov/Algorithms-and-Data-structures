#include <fstream>
#include <vector>
#include <algorithm>
#define ll long long
#define f first
#define s second

using namespace std;

ll dp[2001][2001], w[2001];
int R[2001][2001];
vector <string> ans;

void find_ans(int l, int r) {
    if (l == r)
        return;
    int mid = R[l][r];
    // cout << l << " " << mid << " " << r << '\n';
    for (int i = l; i <= mid; i++)
        ans[i] += '0';
    for (int i = mid + 1; i <= r; i++)
        ans[i] += '1';
    find_ans(l, mid);
    find_ans(mid + 1, r);
}

int main() {
    ifstream cin("optimalcode.in");
    ofstream cout("optimalcode.out");
    int n;
    ll inf = 1e18;
    cin >> n;
    ans.resize(n);
    vector <ll> f(n);
    for (int i = 0; i < 2001; i++)
        for (int j = 0; j < 2001; j++)
            dp[i][j] = inf;
    for (int i = 0; i < n; i++)
        cin >> f[i],
        dp[i][i] = 0;
    for (int i = 0; i < n; i++)
        w[i] = f[i];
    for (int i = 1; i < n; i++)
        w[i] += w[i - 1];
    for (int i = 0; i < n; i++)
        R[i][i] = i;

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            int l = R[i][j - 1], r = R[i + 1][j];
            ll val = i == 0 ? w[j] : w[j] - w[i - 1];
            // cout << i << " " << j << " " << l << " " << r << '\n';
            for (int k = l; k <= r; k++) {
                if (k + 1 <= j && dp[i][k] + dp[k + 1][j] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k + 1][j],
                    R[i][j] = k;
            }
            dp[i][j] += val;
            // cout << i << " " << j << " " << dp[i][j] << '\n';
        }
    }
    cout << dp[0][n - 1] << '\n';
    find_ans(0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}
