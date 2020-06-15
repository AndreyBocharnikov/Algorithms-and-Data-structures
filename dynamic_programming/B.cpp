#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
#define f first
#define s second

using namespace std;
int inf = 1e9;
int main() {
    ifstream cin("lis.in");
    ofstream cout("lis.out");
    int n;
    cin >> n;
    vector <int> a(n), dp(n + 1, inf);
    vector <vector <int> > p(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    dp[0] = -inf;
    for (int i = 0; i < n; i++) {
        int id = int(upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin());
        if (dp[id - 1] < a[i] && dp[id] > a[i])
            dp[id] = a[i],
            p[id].push_back(i);
    }
    int mx = 0;
    for (int i = n; i >= 0; i--)
        if (dp[i] != inf) {
            mx = i;
            break;
        }
    cout << mx << "\n";
    int cop = mx;
    vector <int> ans;
    while (cop != 0) {
        for (int i = 0; i < int(p[cop].size()); i++) {
            int id = p[cop][i];
            if (int(ans.size() == 0) || (id < ans.back() && a[id] < a[ans.back()])) {
                ans.push_back(p[cop][i]);
                cop--;
                break;
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans)
        cout << a[i] << " ";
}
