#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <multiset<int> > vv;
vector <int> ans;
bool first = true;

int pow(int v, int p) {
    int res = 1;
    for (int i = 0; i < p; i++)
        res *= v;
    return res;
}

void euler(int v, int base) {
    // cout << v << ' ';
    // cout.flush();
    while (!vv[v].empty()) {
        int to = *vv[v].begin();
        vv[v].erase(vv[v].begin());
        euler(to, base);
    }
    ans.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int d, k, n;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; i++)
            cout << i;
        return 0;
    }
    n = pow(d, k);
    // cout << n << '\n';
    vv.resize(n + 1);
    for (int i = 0; i < n; i++) {
        vector <int> number;
        int cnt = i;
        for (int j = 0; j < k; j++)
            number.push_back(cnt % d),
            cnt /= d;
        int from = 0;
        for (int j = 0; j < k - 1; j++)
            from *= d,
            from += number[j];
        int to = 0;
        for (int j = 1; j < k; j++)
            to *= d,
            to += number[j];
        // cout << from << " " << to << endl;
        vv[from].insert(to);
    }
    euler(0, d);
    /*for (auto it = ans.end(); it != ans.begin();) {
        it--;
        cout << *it;
    }
    cout << '\n';*/
    for (int i = 0; i < k - 1; i++)
        cout << 0;
    for (int i = int(ans.size()) - 2; i >= 0; i--)
        cout << ans[i] % d;
}
