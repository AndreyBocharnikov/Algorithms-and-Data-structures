#include <iostream>
#include <vector>
#define ll long long

using namespace std;

int main() {
    int x, a, y, b, l;
    cin >> x >> a >> y >> b >> l;
    int left = 1, r = 5 * 1e4;
    vector < vector <int> > dp(301, vector <int> (301));
    while (r - left > 1) {
        for (int i = 0; i < 301; i++)
            for (int j = 0; j < 301; j++)
                dp[i][j] = 0;
        int m = (r + left) / 2;
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= y; j++)
                for (int k = 0; k <= x; k++) {
                    int cnt = (m - a * k + b - 1) / b;
                    cnt = max(cnt, 0);
                    if (j + cnt <= y && i + k <= x)
                        dp[i + k][j + cnt] = max(dp[i][j] + 1, dp[i + k][j + cnt]);
                }
        // cout << m << " " << dp[x][y] << '\n';
        if (dp[x][y] >= l)
            left = m;
        else
            r = m;
    }
    cout << left;
}
