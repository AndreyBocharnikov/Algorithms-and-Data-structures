#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <int> > vv;
vector <int> used;
set <pair<int, int> > ans, no_edge;
int n;

void dfs(int v) {
    used[v] = 1;
    for (int i = 1; i <= n; i++) {
        if (v > i && !used[i] && !vv[v][i])
            no_edge.insert({i, v}),
            no_edge.insert({v, i});

        bool fuck_pcms = v < i && ans.find({i, v}) == ans.end();
        if (used[i] && fuck_pcms && no_edge.find({i, v}) == no_edge.end()) {
            ans.insert({v, i});
        }
        if (vv[v][i] && !used[i])
            dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ifstream cin("dfs.in");
    ofstream cout("dfs.out");
    int m;
    cin >> n >> m;
    vv.resize(n + 1, vector <int> (n + 1));
    used.resize(n + 1);
    vector <int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    auto it = a.begin();
    bool change = true;
    while (change) {
        change = false;
        it = a.begin();
        for (; it < a.end() - 2;) {
            if (*it == *(it + 2)) {
                vv[*it][*(it + 1)] = 1;
                // cout << (*it) << " " << *(it + 1) << '\n';
                ans.insert({(*it), *(it + 1)});
                a.erase(it + 1, it + 3);
                change = true;
            } else {
                it++;
            }
        }
    }

    // cout << "!" << endl;
    for (int i = 1; i <= n; i++) {
        if (!used[i])
            dfs(i);
    }

    cout << ans.size() << '\n';
    for (auto i = ans.begin(); i != ans.end(); i++)
        cout << (*i).f << " " << (*i).s << '\n';
}

