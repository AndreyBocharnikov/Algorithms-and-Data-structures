#include <iostream>
#include <vector>

using namespace std;
int dp[2][10001];
int m, last_id = 0;
void fil() {
    for (int i = 1; i <= m; i++)
        dp[0][i] = 0;
    for (int i = 0; i <= last_id; i++)
        dp[0][i] = 1;
    for (int i = last_id + 1; i <= m; i++)
        dp[0][i] = dp[1][i];
    for (int i = 1; i <= m; i++)
        dp[1][i] = 0;
}

void fill_must(int id) {
    for (int i = last_id + 1; i <= id; i++)
        dp[1][i] = 1;
    last_id = id;
}

int main() {
    // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    string s, t;
    cin >> s >> t;

    int n = int(s.length());
    m = int(t.length());
    t = '$' + t;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        /*for (int j = 1; j <= m; j++)
            cout << dp[0][j] << " ";
        cout << '\n';*/
        if (s[i] == '*') {
            for (int j = 1; j <= m; j++)
                if (dp[0][j] != 1)
                    dp[1][j] = 2;
            fil();
            continue;
        }
        if (dp[0][m] == 1)
            return cout << "NO", 0;
        if (s[i] == '?') {
            bool ok = 1;
            for (int j = 1; j <= m; j++) {
                if (dp[0][j - 1] == 1 && dp[0][j] != 1 && ok)
                    last_id = j,
                    ok = 0;
                if (dp[0][j - 1] == 2)
                    dp[1][j] = 2;
            }
            fil();
            continue;
        }
        bool ok = 1;
        for (int j = 1; j <= m; j++) {
            if (dp[0][j - 1] == 1 && dp[0][j] != 1 && t[j] == s[i] && ok)
                last_id = j,
                ok = 0;
            if (dp[0][j - 1] == 2 && t[j] == s[i]) {
                if (ok)
                    fill_must(j),
                    ok = 0;
                else
                    dp[1][j] = 2;
            }
        }
        fil();
        if (ok)
            return cout << "NO", 0;
    }
    if (dp[0][m] == 1 || dp[0][m] == 2)
        cout << "YES";
    else
        cout << "NO";
}
/*
k?t*n
kitten

??????n
kitten

k*ttten
kitten

*t?n
kitten

k*i*t*t*e*n
kitten

k*i*t*t*?n
kitten
*/
