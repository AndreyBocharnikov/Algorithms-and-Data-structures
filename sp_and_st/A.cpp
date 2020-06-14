#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, inf = 1e9;
    cin >> n >> m;
    vector <vector <int> > vv(n + 1);
    vector <int> dist(n + 1, inf);
    dist[1] = 0;
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].push_back(t);
        vv[t].push_back(f);
    }
    queue <int> q;
    q.push(1);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < vv[v].size(); i++) {
            int to = vv[v][i];
            if (dist[to] != inf)
                continue;
            dist[to] = dist[v] + 1;
            q.push(to);
        }
    }
    for (int i = 1; i <= n; i++)
        cout << dist[i] << " ";
}

