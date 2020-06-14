#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, bool> > > t, lie;
vector <pair<char, pair<int, int> > > edges;
vector <int> used[2], mem[2];
vector <int> save;

bool dfs(int v, bool tru) {
    used[tru][v] = 1;
    mem[tru][v] = 1;
    save.push_back(v);
    if (mem[tru][v] && mem[!tru][v])
        return 1;
    size_t sz = 0;
    if (tru) {
        sz = lie[v].size();
    } else {
        sz = t[v].size();
    }

    bool res = false;
    for (size_t i = 0; i < sz; i++) {
        int to = 0;
        bool next = true;
        if (tru) {
            to = lie[v][i].f;
            next = lie[v][i].s;
        } else {
            to = t[v][i].f;
            next = t[v][i].s;
        }
        if (used[next][to])
            continue;
        res |= dfs(to, next);
    }
    return res;
}

int main() {
    // ifstream cin("truth.in");
    // ofstream cout("truth.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    t.resize(n + 1);
    lie.resize(n + 1);
    for (int i = 0; i < 2; i++)
        mem[i].resize(n + 1),
        used[i].resize(n + 1);

    for (int i = 0; i < m; i++) {
        int from, to;
        char c;
        cin >> from >> to >> c;
        edges.push_back({c, {from, to}});
    }

    int l = 0, r = m + 1;
    while (r - l > 1) {
        int mid = (r + l) / 2;

        for (int i = 1; i <= n; i++)
            t[i].clear(),
            lie[i].clear();

        for (int i = 0; i < mid; i++) {
            char c = edges[i].first;
            int from = edges[i].s.f, to = edges[i].s.s;
            if (c == 'L') {
                t[from].push_back({to, 1});
                lie[to].push_back({from, 0});
                lie[from].push_back({to, 0});
                t[to].push_back({from, 1});
            } else {
                lie[from].push_back({to, 1});
                lie[to].push_back({from, 1});
                t[from].push_back({to, 0});
                t[to].push_back({from, 0});
            }
        }

        bool res = false;
        for (int i = 1; i <= n; i++) {
            if (!used[0][i]) {
                res |= dfs(i, 0);
                for (size_t j = 0; j < save.size(); j++)
                    mem[0][save[j]] = 0,
                    mem[1][save[j]] = 0;
                save.clear();
            }
        }

        used[0].assign(n + 1, 0);
        used[1].assign(n + 1, 0);

        if (res)
            r = mid;
        else
            l = mid;
    }
    cout << l;
}
/*
3 3
1 2 L
2 3 L
3 1 L
*/
