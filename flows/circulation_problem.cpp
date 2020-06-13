#include <bits/stdc++.h>
using namespace std;

vector <int> dist, capacity, flow, used;
vector <pair<int, int> > edges;
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

int64_t max_flow(int n) {
    int64_t answer = 0;
    while (bfs(n)) {
        ptr.assign(n + 1, 0);
        int cur_flow = dfs(start, inf);
        while (cur_flow != 0) {
            answer += cur_flow;
            cur_flow = dfs(start, inf);
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    dist.resize(n + 2);
    used.resize(n + 2);
    edges.resize(6 * m);
    capacity.resize(6 * m);
    flow.resize(6 * m);
    ptr.resize(n + 2);
    vv.resize(n + 2);
    start = 0;
    finish = n + 1;
    for (int i = 0; i < m; i++) {
        int f, t, l, c;
        cin >> f >> t >> l >> c;
        vv[start].push_back({t, 6 * i});
        vv[t].push_back({start, 6 * i + 1});

        vv[f].push_back({finish, 6 * i + 2});
        vv[finish].push_back({f, 6 * i + 3});

        vv[f].push_back({t, 6 * i + 4});
        vv[t].push_back({f, 6 * i + 5});
        flow[6 * i] = 0;
        flow[6 * i + 1] = 0;
        flow[6 * i + 2] = 0;
        flow[6 * i + 3] = 0;
        flow[6 * i + 4] = 0;
        flow[6 * i + 5] = 0;
        capacity[6 * i] = l;
        capacity[6 * i + 1] = 0;
        capacity[6 * i + 2] = l;
        capacity[6 * i + 3] = 0;
        capacity[6 * i + 4] = c - l;
        capacity[6 * i + 5] = 0;
    }
    uint64_t mf = max_flow(n + 1), sum_from_start = 0;
    for (size_t i = 0; i < vv[start].size(); i++)
        sum_from_start += capacity[vv[start][i].second];
    if (mf != sum_from_start)
        return cout << "NO", 0;
    cout << "YES\n";
    for (int i = 0; i < m; i++) {
        cout << flow[6 * i + 4] + capacity[6 * i + 2] << '\n';
    }
}
