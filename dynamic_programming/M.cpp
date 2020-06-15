#include <fstream>
#include <vector>
#include <algorithm>
#define ll long long

using namespace std;
const ll inf = 2 * 1000000000000000000;

int main() {
    ifstream cin("salesman.in");
    ofstream cout("salesman.out");
    int n, m;
    cin >> n >> m;
    vector < vector <int> > vv(n + 1, vector <int> (n + 1));
    int mask = 1 << n;
    for (int i = 0; i < m; i++) {
        int f, t, val;
        cin >> f >> t >> val;
        vv[f - 1][t - 1] = val;
        vv[t - 1][f - 1] = val;
    }
    vector < vector <ll> > dp(mask, vector <ll> (n, inf));
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = 0;
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) % 2 == 1) {
                int cur_mask = (i ^ (1 << j));
                // cout << i << " " << cur_mask << '\n';
                for (int o = 0; o < n; o++)
                    if ((cur_mask >> o) % 2 == 1 && vv[j][o])
                        dp[i][j] = min(dp[i][j], dp[cur_mask][o] + vv[j][o]);
            }
        }
    }
    ll ans(inf);
    for (int i = 0; i < n; i++)
        ans = min(ans, dp[mask - 1][i]);
    if (ans == inf)
        cout << -1;
    else
        cout << ans;
}
