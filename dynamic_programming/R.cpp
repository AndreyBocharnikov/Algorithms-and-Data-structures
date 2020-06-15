#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
#define f first
#define s second

using namespace std;
int dp[1010][1010];
pair <int, int> p[1010][1010];

int main() {
    ifstream cin("number.in");
    ofstream cout("number.out");
    int n;
    cin >> n;
    dp[0][0] = 1;
    p[0][0] = {-1, -1};
    queue <pair<int, int> > q;
    q.push({0, 0});
    while (dp[n][0] != 1) {
        auto v = q.front();
        q.pop();
        int cur_s = v.f, cur_mod = v.s;
        for (int i = 0; i < 10; i++)
            if (!dp[cur_s + i][(cur_mod * 10 + i) % n] && cur_s + i <= n)
                dp[cur_s + i][(cur_mod * 10 + i) % n] = 1,
                p[cur_s + i][(cur_mod * 10 + i) % n] = {i, cur_mod},
                q.push({cur_s + i, (cur_mod * 10 + i) % n});
    }
    string s;
    int cop_n = n, cop_mod = 0;
    while (p[cop_n][cop_mod].f != -1) {
        auto del = p[cop_n][cop_mod];
        cop_n -= del.f;
        cop_mod = del.s;
        s += char(del.f + '0');
    }
    reverse(s.begin(), s.end());
    cout << s;
}
