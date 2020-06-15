#include <fstream>
#include <vector>
#include <algorithm>
#define f first
#define s second
#define ll long long

using namespace std;
const ll inf = 2 * 1e18;
vector <vector <int> > p;
vector <pair <int, int> > ans;
void find_p(int l, int r) {
    if (p[l][r] == -1)
        return;
    int k = p[l][r];
    if (l != k)
        ans.push_back({l, k});
    if (k + 1 != r)
        ans.push_back({k + 1, r});
    // cout << l << " " << k << '\n';
    // cout << k + 1 << " " << r << '\n';
    find_p(l, k);
    find_p(k + 1, r);
}

int main() {
    ifstream cin("matrix.in");
    ofstream cout("matrix.out");
    int n;
    cin >> n;
    if (n == 1)
        return cout << "A", 0;
    p.resize(n, vector <int> (n, -1));
    vector <pair <ll, ll> > vp(n);
    vector <vector <ll> > dp(n, vector <ll> (n, inf));
    for (int i = 0; i < n; i++)
        cin >> vp[i].first >> vp[i].second;
    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1] = vp[i].first * vp[i + 1].first * vp[i + 1].second;
        dp[i][i] = 0;
    }
    dp[n - 1][n - 1] = 0;
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++) {
                if (dp[i][k] + dp[k + 1][j] + vp[i].first * vp[k].s * vp[j].s < dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j] + vp[i].f * vp[k].s * vp[j].s;
                    p[i][j] = k;
                }
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + vp[i].f * vp[k].s * vp[j].s);
            }
        }
    }
    // cout << dp[0][n - 1] << '\n';
    find_p(0, n - 1);
    vector <vector <int> > kek(n);
    kek[0].push_back(1);
    kek[n - 1].push_back(-1);
    for (int i = 0; i < int(ans.size()); i++) {
        kek[ans[i].first].push_back(1);
        kek[ans[i].second].push_back(-1);
    }
    for (int i = 0; i < n; i++) {
        sort(kek[i].begin(), kek[i].end());
        reverse(kek[i].begin(), kek[i].end());
    }
    for (int i = 0; i < n; i++) {
        bool ok = 1;
        for (int j = 0; j < int(kek[i].size()); j++) {
            if (kek[i][j] == 1) {
                cout << '(';
            } else {
                if (ok) {
                    cout << "A";
                    ok = 0;
                }
                cout << ')';
            }
        }
        if (ok)
            cout << "A";
    }
}

