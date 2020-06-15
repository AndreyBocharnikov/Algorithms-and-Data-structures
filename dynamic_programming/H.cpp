#include <fstream>
#include <vector>
#include <algorithm>
#define s second
#define f first
#define ll long long

using namespace std;

int main() {
    ifstream cin("perm.in");
    ofstream cout("perm.out");
    int n, k, mask;
    ll m;
    cin >> n >> m >> k;
    mask = 1 << n;
    vector <int> a(n);
    vector <vector <ll> > dp(mask, vector <ll> (n));
    vector <vector <int> > vv(n, vector <int> (n));
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = 1;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (__gcd(a[i], a[j]) >= k) {
                vv[i][j] = 1;
                vv[j][i] = 1;
            }
        }
    for (int i = 0; i < mask; i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) % 2 == 1) {
                int cur_mask = (i ^ (1 << j));
                for (int o = 0; o < n; o++)
                    if ((cur_mask >> o) % 2 == 1 && vv[j][o])
                        dp[i][j] += dp[cur_mask][o];
            }
        }
    }
    vector <pair <int, int> > b(n);
    for (int i = 0; i < n; i++) {
        b[i].first = a[i];
        b[i].second = i;
    }
    sort(b.begin(), b.end());
    vector <int> ans, used(n);
    ll sum(0);
    for (int i = 0; i < n; i++)
        sum += dp[mask - 1][i];
    if (sum < m)
        return cout << -1, 0;
    int tmp = mask - 1;
    for (int cnt = 0; cnt < n; cnt++) {
        for (int i = 0; i < n; i++) {
            int id = 0;
            if (int(ans.size()) > 0)
                id = ans.back();
            if (dp[tmp][b[i].s] >= m && !used[b[i].s] && (cnt == 0 || vv[id][b[i].s])) {
                ans.push_back(b[i].second);
                tmp ^= (1 << b[i].second);
                used[b[i].second] = 1;
                break;
            }
            if (dp[tmp][b[i].s] < m && (cnt == 0 || vv[id][b[i].s]))
                m -= dp[tmp][b[i].second];
        }
    }

    for (int i : ans)
        cout << a[i] << " ";
}

