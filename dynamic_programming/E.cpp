#include <fstream>
#include <vector>
#include <string>
#define ll long long

using namespace std;

int main() {
    ifstream cin("levenshtein.in");
    ofstream cout("levenshtein.out");
    string s, t;
    cin >> s >> t;
    int n = int(s.length()), m = int(t.length());
    if (n == 0)
        return cout << m, 0;
    if (m == 0)
        return cout << n, 0;
    vector <vector <int> > dp(n + 1, vector <int> (m + 1));
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (i == 0 && j == 0)
                continue;
            dp[i][j] = 1e9;
            if (i > 0 && j > 0) {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            if (i > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            if (j > 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            // cout << i << " " << j << " " << dp[i][j] << '\n';
        }
    cout << dp[n][m];
}
