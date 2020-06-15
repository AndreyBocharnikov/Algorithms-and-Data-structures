#include <iostream>
#include <vector>
#include <algorithm>
#define f first
#define s second
#define ll long long

using namespace std;
int dp[2001][2001], mem[2001][2001];
int a[2001];
int mod = 1000000000;

int add(int b, int c) {
    return (b + c) % mod;
}

int mns(int b, int c) {
    if (b - c < 0)
        return b - c + mod;
    else
        return b - c;
}

int mul(int k, int val) {
    return (k * val) % mod;
}

int fnd(int l, int r) {
    if (r < l)
        return 0;
    if (mem[l][r])
        return dp[l][r];
    int val;
    if (a[l] == a[r])
        val = add(add(fnd(l + 1, r), fnd(l, r - 1)), 1);
    else
        val = mns(add(fnd(l + 1, r), fnd(l, r - 1)), fnd(l + 1, r - 1));
    // cout << l << " " << r << " " << val << '\n';
    dp[l][r] = val;
    mem[l][r] = 1;
    return val;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
        mem[i][i] = 1;
    }
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << fnd(0, n - 1);
}

