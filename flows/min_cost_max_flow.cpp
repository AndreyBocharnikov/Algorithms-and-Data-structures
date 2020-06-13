#include <bits/stdc++.h>

using namespace std;

set <pair<int, int> > dist_dij;
vector <int> capacity, flow, cost, dist_fb, dist, parent, init_cost, used;
vector <pair<int, int> > edges;
vector <vector <pair<int, int> > > vv;
int n, inf = 1e9, start, finish;

bool check_dfs(int v) {
    used[v] = true;
    if (v == finish)
        return true;
    bool ok = false;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].first, id = vv[v][i].second;
        if (used[to] || capacity[id] == flow[id])
            continue;
        ok |= check_dfs(to);
    }
    return ok;
}

void Ford_Bellman() {
    dist_fb[start] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            for (size_t k = 0; k < vv[j].size(); k++) {
                int to = vv[j][k].first, id = vv[j][k].second;
                if (id % 2 == 1)
                    continue;
                dist_fb[to] = min(dist_fb[to], dist_fb[j] + cost[id]);
            }
        }
    }
}

void Dijkstra() {
    dist_dij.clear();
    for (int i = 2; i <= n; i++) {
        dist_dij.insert({inf, i});
        dist[i] = inf;
    }
    dist_dij.insert({0, 1});
    dist[1] = 0;
    while (!dist_dij.empty()) {
        auto par = dist_dij.begin();;
        dist_dij.erase(par);
        int v = (*par).second;
        for (size_t i = 0; i < vv[v].size(); i++) {
            int to = vv[v][i].first, id = vv[v][i].second;
            if (flow[id] < capacity[id] && cost[id] >= 0 && dist[to] > dist[v] + cost[id]) {
                dist_dij.erase({dist[to], to});
                dist[to] = dist[v] + cost[id];
                dist_dij.insert({dist[to], to});
                parent[to] = id;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m;
    cin >> n >> m;
    start = 1;
    finish = n;
    dist_fb.resize(n + 1, inf);
    edges.resize(2 * m);
    vv.resize(n + 1);
    capacity.resize(2 * m);
    flow.resize(2 * m);
    cost.resize(2 * m);
    dist.resize(n + 1);
    used.resize(n + 1);
    parent.resize(n + 1);
    init_cost.resize(2 * m);
    for (int i = 0; i < m; i++) {
        int f, t, cap, cost_;
        cin >> f >> t >> cap >> cost_;
        vv[f].push_back({t, 2 * i});
        vv[t].push_back({f, 2 * i + 1});
        edges[2 * i] = {f, t};
        edges[2 * i + 1] = {t, f};
        capacity[2 * i] = cap;
        capacity[2 * i + 1] = 0;
        flow[2 * i] = 0;
        flow[2 * i + 1] = 0;
        cost[2 * i] = cost_;
        cost[2 * i + 1] = -cost_;
    }
    init_cost = cost;
    Ford_Bellman();
    for (int i = 1; i <= n; i++) {
        for (size_t j = 0; j < vv[i].size(); j++) {
            int to = vv[i][j].first, id = vv[i][j].second;
            cost[id] = cost[id] + dist_fb[i] - dist_fb[to];
        }
    }
    while (check_dfs(start)) {
        Dijkstra();
        int tmp_vertex = finish, par = edges[parent[tmp_vertex]].first;
        vector <int> current_path;
        while (true) {
            current_path.push_back(parent[tmp_vertex]);
            if (par == start)
                break;
            tmp_vertex = par;
            par = edges[parent[tmp_vertex]].first;
        }
        int min_cap = 1e9;
        for (int i : current_path)
            min_cap = min(min_cap, capacity[i] - flow[i]);
        for (int i : current_path)
            flow[i] += min_cap,
            flow[i ^ 1] -= min_cap;
        for (int i = 1; i <= n; i++) {
            for (size_t j = 0; j < vv[i].size(); j++) {
                int to = vv[i][j].first, id = vv[i][j].second;
                cost[id] = cost[id] + dist[i] - dist[to];
            }
        }
        used.assign(n + 1, false);
    }
    int64_t answer = 0;
    for (int i = 1; i <= n; i++)
        for (size_t j = 0; j < vv[i].size(); j++) {
            int id = vv[i][j].second;
            answer += 1LL * flow[id] * init_cost[id];
    }
    cout << answer / 2;
}
