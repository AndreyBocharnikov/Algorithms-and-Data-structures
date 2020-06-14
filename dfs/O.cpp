#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector <vector <pair<int, int> > > vv[2], graf[2];
vector <int> visit[2], color[2];
vector <pair<int, int> > order;

void dfs(int v, int lie) {
    visit[lie][v] = 1;
    for (size_t i = 0; i < vv[lie][v].size(); i++) {
        pair<int, int> to = vv[lie][v][i];
        if (!visit[to.s][to.f])
            dfs(to.f, to.s);
    }
    order.push_back({v, lie});
}

void color_dfs(int v, int lie, int col) {
    color[lie][v] = col;
    for (size_t i = 0; i < graf[lie][v].size(); i++) {
        pair<int, int> to = graf[lie][v][i];
        if (!color[to.s][to.f])
            color_dfs(to.f, to.s, col);
    }
}

int main() {
    ifstream cin("chip.in");
    ofstream cout("chip.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector <int> value(n + 1), wire(2 * n), used(n + 1), id(2 * n);
    for (int i = 0; i < 2; i++)
        vv[i].resize(n + 1),
        graf[i].resize(n + 1),
        visit[i].resize(n + 1),
        color[i].resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> value[i];
    for (int i = 0; i < 2 * n; i++) {
        cin >> wire[i];
        if (used[wire[i]])
            id[i] = 1;
        else
            id[i] = 0;
        used[wire[i]] = 1;
    }
    vector <pair<int, int> > rev_wire(n + 1, {-1, -1});
    for (int i = 0; i < 2 * n; i++) {
        if (rev_wire[wire[i]].f != -1)
            rev_wire[wire[i]].s = i;
        else
            rev_wire[wire[i]].f = i;
    }
    for (int i = 0; i < 2 * n; i++) {
        int next = (i + 1) % (2 * n);
        if (value[wire[i]] == value[wire[next]]) {
            int a = id[i], b = id[next];
            vv[!a][wire[i]].push_back({wire[next], b});
            vv[!b][wire[next]].push_back({wire[i], a});
            // cout << "!";
            graf[b][wire[next]].push_back({wire[i], !a});
            graf[a][wire[i]].push_back({wire[next], !b});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visit[0][i])
            dfs(i, 0);
        if (!visit[1][i])
            dfs(i, 1);
    }
    int col = 0;
    for (int i = 2 * n - 1; i >= 0; i--) {
        auto cur = order[i];
        if (!color[cur.s][cur.f])
            col++,
            color_dfs(cur.f, cur.s, col);
    }
    vector <int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        // cout << i << " " << color[0][i] << " " << color[1][i] << '\n';
        if (color[0][i] == color[1][i])
            return cout << "NO", 0;
        if (color[0][i] > color[1][i])
            ans[i] = 2;
        else
            ans[i] = 1;
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        if (ans[i] == 1)
            // cout << value[wire[rev_wire[i].f]] << " ";
            cout << rev_wire[i].f + 1 << " ";
        else
            // cout << value[wire[rev_wire[i].s]] << " ";
            cout << rev_wire[i].s + 1 << " ";
    }
}

