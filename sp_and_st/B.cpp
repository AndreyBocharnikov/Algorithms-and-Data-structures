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
    int n, s, t;
    ll inf = 1e18;
    cin >> n >> s >> t;
    vector <vector <int> > vv(n + 1, vector <int> (n + 1));
    vector <ll> dist(n + 1, inf);
    vector <bool> c(n + 1, false);
    dist[s] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> vv[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        ll mn = inf;
        int v = -1;
        for (int j = 1; j <= n; j++)
            if (!c[j] && dist[j] < mn)
                v = j,
                mn = dist[j];
        if (v == -1)
            break;
        c[v] = true;
        for (int j = 1; j <= n; j++) {
            if (vv[v][j] == -1)
                continue;
            dist[j] = min(dist[j], dist[v] + vv[v][j]);
        }
    }
    if (dist[t] == inf)
        cout << -1;
    else
        cout << dist[t];
}


