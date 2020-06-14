#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

struct point{
    int x, y;
};

int len2(point a, point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double len(point a, point b) {
    return sqrt(len2(a, b));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector <point> points(n + 1);
    vector <bool> c(n + 1);
    vector <int> dist(n + 1, 1e9);
    dist[1] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> points[i].x >> points[i].y;
        int tmp = len2(points[1], points[i]);
        dist[i] = tmp;
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
        int mn = 1e9;
        int p = -1;
        for (int j = 1; j <= n; j++)
            if (!c[j] && dist[j] < mn)
                mn = dist[j],
                p = j;
        ans += sqrt(mn);
        c[p] = true;
        for (int j = 1; j <= n; j++)
            if (!c[j])
                dist[j] = min(dist[j], len2(points[p], points[j]));
    }
    cout << fixed;
    cout.precision(10);
    cout << ans;
}

