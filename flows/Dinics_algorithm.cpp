#include <bits/stdc++.h>
using namespace std;

vector <int> dist, capacity, flow;
vector <size_t> ptr;
vector <vector <pair<int, int> > > vv;
int start, finish;
const int inf = 1e9 + 7;

bool bfs(int n) {
    dist.assign(n + 1, inf);
    dist[start] = 0;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < vv[v].size(); i++) {
            int to = vv[v][i].first, id = vv[v][i].second;
            if (flow[id] < capacity[id] && dist[to] == inf) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist[finish] != inf;
}

int dfs(int v, int minCapacity) {
    if (v == finish || minCapacity == 0) {
        return minCapacity;
    }

    for (; ptr[v] < vv[v].size(); ++ptr[v]) {
        int to = vv[v][ptr[v]].first, id = vv[v][ptr[v]].second;
        if (dist[to] != dist[v] + 1)
            continue;
        int pushed = dfs(to, min(minCapacity, capacity[id] - flow[id]));
        if (pushed == 0)
            continue;
        flow[id] += pushed;
        flow[id ^ 1] -= pushed;
        return pushed;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    dist.resize(n + 1);
    capacity.resize(2 * m);
    flow.resize(2 * m);
    ptr.resize(n + 1);
    vv.resize(n + 1);
    start = 1;
    finish = n;
    for (int i = 0; i < m; i++) {
        int f, t, c;
        cin >> f >> t >> c;
        vv[f].push_back({t, 2 * i});
        vv[t].push_back({f, 2 * i + 1});
        flow[2 * i] = 0;
        flow[2 * i + 1] = 0;
        capacity[2 * i] = c;
        capacity[2 * i + 1] = 0;
    }

    int64_t answer = 0;
    while (bfs(n)) {
        ptr.assign(n + 1, 0);
        int cur_flow = dfs(start, inf);
        while (cur_flow != 0) {
            answer += cur_flow;
            cur_flow = dfs(start, inf);
        }
    }
    cout << answer;
}

