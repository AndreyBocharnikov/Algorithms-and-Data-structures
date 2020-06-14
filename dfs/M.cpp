#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> order, used;

void dfs(int v) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (used[to] == 1) {
            cout << "No";
            exit(0);
        }
        if (used[to] == 2)
            continue;
        dfs(to);
    }
    used[v] = 2;
    order.push_back(v);
}

int main() {
    ifstream cin("tiv.in");
    ofstream cout("tiv.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, alf = 26;
    cin >> n;
    vector <string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vv.resize(alf);
    used.resize(alf);
    set <int> first;
    vector <bool> deg(alf);
    if (a[0].length() != 1)
        first.insert(a[0][0] - 'a');
    for (int i = 1; i < n; i++) {
        if (a[i].length() != 1)
            first.insert(a[i][0] - 'a');
        if (a[i] == a[i - 1])
            return cout << "No", 0;
        size_t id = 0, len = a[i].length(), len2 = a[i - 1].length();
        if (len < len2)
            return cout << "No", 0;
        if (len != len2)
            continue;
        while (id < min(len, len2) && a[i][id] == a[i - 1][id])
            id++;
        vv[a[i - 1][id] - 'a'].push_back(a[i][id] - 'a');
        deg[a[i][id] - 'a'] = true;
    }

    for (int i = 0; i < alf; i++)
        if (!used[i])
            dfs(i);

    int zero = -1;
    for (int i = 0; i < alf; i++) {
        if (first.find(i) == first.end() && deg[i] == false) {
            zero = i;
            break;
        }
    }
    if (zero == -1)
        return cout << "No", 0;
    vector <int> ans(alf);
    int kek = 1;
    for (int i = alf - 1; i >= 0; i--) {
        if (order[i] == zero)
            ans[order[i]] = 0,
            kek = 0;
        else
            ans[order[i]] = alf - 1 - i + kek;
    }
    cout << "Yes\n";
    for (int i : ans)
        cout << i << " ";
    /*vector <int> ans(alf);
    for (int i = alf - 1; i >= 0; i--)
        ans[order[i]] = alf - 1 - i;
    cout << "Yes\n";
    for (int i : ans)
        cout << i << " ";*/
}
/*
6
a
b
aa
ac
bc
bb

4
bcb
bcc
cbb
cbc

4
bca
bbc
bbd
bea
*/
