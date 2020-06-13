#include <bits/stdc++.h>

using namespace std;

set <pair<int, int> > dist_dij;
vector <int> capacity, flow, cost, dist_fb, dist, parent, init_cost, used;
vector <pair<int, int> > edges;
vector <vector <pair<int, int> > > vv;
int n, inf = 1e9, start, finish, N;

bool check_dfs(int v) {
    used[v] = true;
    if (v == finish)
        return true;
    bool ok = false;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i].first, id = vv[v][i].second;
        if (used[to] || capacity[id] == flow[id] || cost[id] < 0)
            continue;
        ok |= check_dfs(to);
    }
    return ok;
}

void Ford_Bellman() {
    dist_fb[start] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
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
    for (int i = 1; i <= N; i++) {
        dist_dij.insert({inf, i});
        dist[i] = inf;
    }
    dist_dij.insert({0, 0});
    dist[0] = 0;
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
    int m, x;
    cin >> n;
    m = n * n + 2 * n;
    start = 0;
    N = 2 * n + 1;
    finish = N;
    dist_fb.resize(N + 1, inf);
    edges.resize(2 * m);
    vv.resize(N + 1);
    capacity.resize(2 * m);
    flow.resize(2 * m);
    cost.resize(2 * m);
    dist.resize(N + 1);
    used.resize(N + 1);
    parent.resize(N + 1);
    init_cost.resize(2 * m);

    for (int i = 1; i <= n; i++) {
        int id = 2 * i - 2;
        vv[0].push_back({i, id});
        vv[i].push_back({0, id + 1});
        edges[id] = {0, i};
        edges[id + 1] = {i, 0};
        capacity[id] = 1;
        capacity[id + 1] = 0;
        flow[id] = 0;
        flow[id + 1] = 0;
        cost[id] = 0;
        cost[id + 1] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> x;
            int id = 2 * i * n + 2 * j - 2;
            vv[i].push_back({n + j, id});
            vv[n + j].push_back({i, id + 1});
            edges[id] = {i, n + j};
            edges[id + 1] = {n + j, i};
            capacity[id] = 1;
            capacity[id + 1] = 0;
            flow[id] = 0;
            flow[id + 1] = 0;
            cost[id] = x;
            cost[id + 1] = -x;
        }
    }

    for (int i = 1; i <= n; i++) {
        int id = 2 * n * n + 2 * n + 2 * i - 2;
        vv[n + i].push_back({2 * n + 1, id});
        vv[2 * n + 1].push_back({n + i, id + 1});
        edges[id] = {n + i, 2 * n + 1};
        edges[id + 1] = {2 * n + 1, n + i};
        capacity[id] = 1;
        capacity[id + 1] = 0;
        flow[id] = 0;
        flow[id + 1] = 0;
        cost[id] = 0;
        cost[id + 1] = 0;
    }

    init_cost = cost;
    Ford_Bellman();
    for (int i = 0; i <= N; i++) {
        for (size_t j = 0; j < vv[i].size(); j++) {
            int to = vv[i][j].first, id = vv[i][j].second;
            cost[id] = cost[id] + dist_fb[i] - dist_fb[to];
        }
    }

    while (true) {
        Dijkstra();
        if (dist[finish] == inf)
            break;
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
        for (int i = 0; i <= N; i++) {
            for (size_t j = 0; j < vv[i].size(); j++) {
                int to = vv[i][j].first, id = vv[i][j].second;
                cost[id] = cost[id] + dist[i] - dist[to];
            }
        }
        used.assign(N + 1, false);
    }
    int64_t answer = 0;
    vector <pair<int, int> > matching;
    for (int i = 0; i <= N; i++)
        for (size_t j = 0; j < vv[i].size(); j++) {
            int to = vv[i][j].first, id = vv[i][j].second;
            if (flow[id] > 0) {
                answer += 1LL * flow[id] * init_cost[id];
                if (i != 0 && to != N)
                    matching.push_back({i, to});
            }
    }
    cout << answer << '\n';
    for (auto par : matching)
        cout << par.first << " " << par.second - n << '\n';
}

