#include <iostream>
#include <vector>
#define ll long long
#define vv vector < vector <long long> >

using namespace std;
ll const mod = 999999937;
vv multi(vv a, vv b) {
    vv res(5, vector <ll> (5));
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
        ll sum(0);
        for (int k = 0; k < 5; k++) {
            sum += 1LL * a[i][k] * b[k][j];
            sum %= mod;
        }
        res[i][j] = sum;
    }
    return res;
}

int main() {
    ll n;
    cin >> n;
    vector < vector <ll> > mat(5, vector <ll> (5, 1));
    mat[2][3] = 0;
    mat[2][4] = 0;
    mat[4][3] = 0;
    mat[4][4] = 0;
    while (n) {
        n--;
        ll cop = n;
        vector <vector <ll> > res(5, vector <ll> (5)), cur = mat;
        for (int i = 0; i < 5; i++)
            res[i][i] = 1;
        while (cop) {
            if (cop % 2) {
                res = multi(res, cur);
                cop--;
            }
            cur = multi(cur, cur);
            cop /= 2;
        }
        ll ans(0);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++) {
                ans += res[i][j];
                ans %= mod;
            }
        cout << ans << '\n';
        cin >> n;
    }
}

