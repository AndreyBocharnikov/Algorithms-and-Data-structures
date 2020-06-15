#include <fstream>
#include <vector>
#include <algorithm>
#define ll long long
#define vv vector <vector <int> >

using namespace std;

vv matr;
int mask, m;
ll mod;
string s;

bool check(int a, int b, int c, int d) {
    int val = a + b + c + d;
    if (val == 4 || val == 0)
        return 0;
    return 1;
}

int pcms(int cur_mask, int id) {
    return (cur_mask >> id) % 2;
}

void make_matr() {
    for (int i = 0; i < mask; i++)
        for (int j = 0; j < mask; j++) {
            bool ok = 1;
            for (int k = 0; k < m - 1; k++) {
                if (!check(pcms(i, k), pcms(i, k + 1), pcms(j, k), pcms(j, k + 1)))
                    ok = 0;
            }
            if (ok)
                matr[i][j] = 1;
        }
}

vv multi(vv &a, vv &b) {
    vv res(mask, vector <int> (mask));
    for (int i = 0; i < mask; i++)
        for (int j = 0; j < mask; j++) {
        ll sum(0);
        for (int k = 0; k < mask; k++) {
            sum += (1ll * a[i][k] * b[k][j]) % mod;
            sum %= mod;
        }
        res[i][j] = int(sum);
    }
    return res;
}

string mns() {
    int id = int(s.length()) - 1, n = int(s.length());
    while (s[id] == '0')
        id--;
    s[id]--;
    for (int i = id + 1; i < n; i++)
        s[i] = '9';
    return s;
}

int main() {
    ifstream cin("nice3.in");
    ofstream cout("nice3.out");
    cin >> s >> m >> mod;
    mask = 1 << m;
    matr.resize(mask, vector <int> (mask));
    make_matr();
    vv ans;
    ans.resize(mask, vector <int> (mask));
    for (int i = 0; i < mask; i++)
        ans[i][i] = 1;
    s = mns();
    while (1) {
        int n = int(s.length());
        if ((s.back() - '0') % 2 == 1) {
            ans = multi(ans, matr);
            s = mns();
        }
        int cnt(0);
        matr = multi(matr, matr);
        int next = 0;
        for (int i = 0; i < n; i++) {
            int val = (s[i] - '0' + 10 * next);
            if (val % 2 == 1)
                next = 1;
            else
                next = 0;
            val /= 2;
            s[i] = char(val + '0');
        }
        for (int i = 0; i < n; i++)
            if (s[i] != '0')
                cnt++;
        if (cnt == 0)
            break;
    }
    ll sum(0);
    for (int i = 0; i < mask; i++) {
        for (int j = 0; j < mask; j++) {
            sum += ans[i][j];
            sum %= mod;
        }
    }
    cout << sum;
}
