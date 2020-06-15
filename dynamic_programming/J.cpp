#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s, t, s_rev, t_rev;
int n, m;
int prv[10001], L1[10001], L2[10001];

vector <char> ans;

void kek() {
    for (int i = 0; i <= 10000; i++)
        L1[i] = 0;
}

void kek2() {
    for (int i = 0; i <= 10000; i++)
        L2[i] = 0;
}

void find_ans(int l, int r, int l2, int r2) {
    if (r2 < l2)
        return;
    int mid = l + (r - l) / 2;
    if (r - l == 0) {
        for (int i = l2; i <= r2; i++)
            if (s[l] == t[i]) {
                ans.push_back(s[l]);
                return;
            }
        return;
    }
    kek();
    for (int i = l; i <= mid; i++) {
        for (int j = l2; j <= r2 + 1; j++)
            prv[j] = L1[j];
        for (int j = l2; j <= r2; j++) {
            if (s[i] == t[j])
                L1[j + 1] = prv[j] + 1;
            else
                L1[j + 1] = max(prv[j + 1], L1[j]);
        }
    }
    kek2();
    for (int i = r; i >= mid + 1; i--) {
        for (int j = r2 + 2; j >= l2 + 1; j--)
            prv[j] = L2[j];
        for (int j = r2; j >= l2; j--) {
            if (s[i] == t[j])
                L2[j + 1] = prv[j + 2] + 1;
            else
                L2[j + 1] = max(prv[j + 1], L2[j + 2]);
        }
    }

    int mx = 0, id = -1;
    for (int i = l2; i <= r2 + 1; i++)
        if (L1[i] + L2[i + 1] > mx)
            mx = L1[i] + L2[i + 1],
            id = i;
    if (id == -1)
        return;
    find_ans(l, mid, l2, id - 1);
    find_ans(mid + 1, r, id, r2);
}

int main() {
    cin >> s >> t;
    n = int(s.length());
    m = int(t.length());

    s_rev = s;
    t_rev = t;
    reverse(s_rev.begin(), s_rev.end());
    reverse(t_rev.begin(), t_rev.end());
    find_ans(0, n - 1, 0, m - 1);
    for (int i = 0; i < int(ans.size()); i++)
        cout << ans[i];
    cout << '\n';
}
