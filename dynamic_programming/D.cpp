#include <fstream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

int main() {
    ifstream cin("knapsack.in");
    ofstream cout("knapsack.out");
    int n, M;
    cin >> n >> M;
    vector <int> c(n + 1), m(n + 1);
    vector <vector <int > > dp(M + 1, vector <int> (n + 1));
    for (int i = 1; i <= n; i++)
        cin >> m[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    for (int i = 0; i <= M; i++) {
        for (int j = 1; j <= n; j++) {
            if (i >= m[j])
                dp[i][j] = max(dp[i][j - 1], dp[i - m[j]][j - 1] + c[j]);
            else
                dp[i][j] = dp[i][j - 1];
        }
    }
    int cop = n, mas = M;
    vector <int> ans;
    while (cop != 0) {
        while (dp[mas][cop] == dp[mas][cop - 1])
            cop--;
        if (cop == 0)
            break;
        ans.push_back(cop);
        mas -= m[cop];
        cop--;
    }
    cout << ans.size() << '\n';
    for (int i : ans)
        cout << i << " ";
}
