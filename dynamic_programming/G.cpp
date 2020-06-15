#include <fstream>
#include <vector>
#include <algorithm>
#define ll long long
#define f first
#define s second

using namespace std;
int n;
const int inf = 1e9;
int cnt(int mask) {
    int ans(0);
    for (int i = 0; i < n; i++)
        if ((mask >> i) % 2)
            ans++;
    return ans;
}
int main() {
    ifstream cin("meetings.in");
    ofstream cout("meetings.out");
    int k;
    cin >> n >> k;
    int mask = 1 << n;
    vector < pair <int, int> > a(n);
    vector < vector <int> > vv(n, vector <int> (n));
    vector <int> res(n), dp(mask, inf);
    for (int i = 0; i < n; i++)
        cin >> a[i].f >> a[i].s >> res[i];

    for (int i = 0; i < n; i++)
        if (a[i].f <= k && a[i].s >= k)
            dp[1 << i] = k + res[i];

    for (int i = 0; i < mask; i++) {
        vector <int> relaks;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) == 0)
                relaks.push_back(j);
        }
        for (int j = 0; j < int(relaks.size()); j++) {
            int id = relaks[j], l = a[id].f, r = a[id].s;
            if (dp[i] >= l && dp[i] <= r)
                // cout << i << " " << (i | (1 << id)) << " " << dp[i] << " " << res[id] << '\n',
                dp[i | (1 << id)] = dp[i] + res[id];
        }
    }
    int mx = 0, id = 0;
    for (int i = 0; i < mask; i++) {
        int cur_cnt = cnt(i);
        if (dp[i] != inf && cur_cnt > mx)
            mx = cur_cnt,
            id = i;
    }
    dp[0] = 0;
    vector <int> ans;
    while (id) {
        for (int i = 0; i < n; i++) {
            int val = dp[id] - res[i];
            // cout << id << " " << a[i].f << " " << val << " " << a[i].s << '\n';
            if ((id >> i) % 2 && val >= a[i].f && val <= a[i].s && dp[id ^ (1 << i)] != inf) {
                ans.push_back(i);
                id ^= (1 << i);
                break;
            }
        }
    }
    cout << int(ans.size()) << '\n';
    reverse(ans.begin(), ans.end());
    for (int i : ans)
        cout << i + 1 << " ";
}
