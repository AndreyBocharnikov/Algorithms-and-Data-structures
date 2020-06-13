#include <bits/stdc++.h>
using namespace std;

vector <vector <pair<int, int> > > vv;
vector <int> used, flow, capacity;
int inf = 1e9;

int dfs(int v, int t, int min_c) {
    if (v == t) {
        return min_c;
    }
    used[v] = true;
    for (size_t i = 0; i < vv[v].size(); i++) {
        auto par = vv[v][i];
        int to = par.first, id = par.second;
        if (!used[to] && flow[id] < capacity[id]) {
            int current_flow = dfs(to, t, min(min_c, capacity[id] - flow[id]));
            if (current_flow > 0) {
                flow[id] += current_flow;
                int rev_id = id / 2 * 2;
                if (rev_id != id) {
                    flow[rev_id] -= current_flow;
                } else {
                    flow[rev_id + 1] -= current_flow;
                }
                return current_flow;
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, s, t;
    cin >> n >> m;
    s = 1;
    t = n;
    vv.resize(n + 1);
    used.resize(n + 1);
    capacity.resize(2 * m);
    flow.resize(2 * m);
    for (int i = 0; i < m; i++) {
        int f, t, c;
        cin >> f >> t >> c;
        vv[f].push_back({t, 2 * i});
        vv[t].push_back({f, 2 * i + 1});
        capacity[2 * i] = c;
        capacity[2 * i + 1] = 0;
    }
    int answer = 0;
    while (true) {
        used.assign(n + 1, 0);
        int end_ = dfs(s, t, inf);
        if (end_ == 0) {
            break;
        }
    }
    for (size_t i = 0; i < vv[s].size(); i++) {
        answer += flow[vv[s][i].second];
    }
    cout << answer;
}

