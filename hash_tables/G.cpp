#include <iostream>
#include <vector>
#include <algorithm>

#define  ll long long
using namespace std;

vector <vector<int> > vv, children;
vector <int> sz;
int root = -1, mod = 1005007, p = 1020247;

void dfs(int v, int p) {
    sz[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (to == p)
            continue;
        children[v].push_back(to);
        dfs(to, v);
        sz[v] += sz[to];
    }
}

void dfs2(int v) {
    size_t n = children[v].size();
    if (n == 0)
        return;
    for (size_t i = 0; i < children[v].size(); i++) {
        int to = children[v][i];
        if (vv[to].size() == 2 &&  2 * (sz[1] - sz[to]) == sz[1] - 1)
            root  = to;
        dfs2(to);
    }
}

vector <ll> eqviv;
ll my_hash(vector <ll> &a) {
    ll sum = 0;
    for (ll i : a) {
        sum = (sum * mod + i) % p;
    }
    return sum;
}

void solve(int v) {
    size_t n = children[v].size();
    // cout << v << " " << n << '\n';
    if (n == 0) {
        eqviv[v] = 1;
        return;
    }
    vector <ll> cur;
    for (size_t i = 0; i < n; i++) {
        int to = children[v][i];
        solve(to);
        cur.push_back(eqviv[to]);
    }
    sort(cur.begin(), cur.end());
    eqviv[v] = my_hash(cur);
    // cout << v << " " << eqviv[v] << endl;
}

int main() {
    size_t n;
    cin >> n;
    vv.resize(n + 1);
    children.resize(n + 1);
    sz.resize(n + 1);
    eqviv.resize(p);
    for (size_t i = 0; i < n - 1; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        vv[t].push_back(f);
    }
    dfs(1, 1);
    dfs2(1);
    // cout << root << endl;
    if (vv[1].size() == 2 && sz[vv[1][0]] == sz[vv[1][1]] && 2 * sz[vv[1][0]] == sz[1] - 1)
        root = 1;
    if (root == -1) {
        cout << "NO";
        return 0;
    }
    children.clear();
    children.resize(n + 1);
    dfs(root, root);
    solve(root);
    if (eqviv[vv[root][0]] == eqviv[vv[root][1]])
        cout << "YES";
    else
        cout << "NO";
}
