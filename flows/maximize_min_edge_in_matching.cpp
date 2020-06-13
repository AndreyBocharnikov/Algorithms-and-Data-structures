#include <bits/stdc++.h>
using namespace std;

vector <int> dist, capacity, flow, cost;
vector <size_t> ptr;
vector <vector <pair<int, int> > > vv;
vector <pair<int, int> > edges;
int start, finish, N;
const int inf = 1e6;

bool bfs(int n, int limitation) {
    dist.assign(n + 1, inf);
    dist[start] = 0;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < vv[v].size(); i++) {
            int to = vv[v][i].first, id = vv[v][i].second;
            if (cost[id] < limitation)
                continue;
            if (flow[id] < capacity[id] && dist[to] == inf) {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist[finish] != inf;
}

int dfs(int v, int minCapacity, int limitation) {
    if (v == finish || minCapacity == 0) {
        return minCapacity;
    }

    for (; ptr[v] < vv[v].size(); ++ptr[v]) {
        int to = vv[v][ptr[v]].first, id = vv[v][ptr[v]].second;
        if (cost[id] < limitation)
                continue;
        if (dist[to] != dist[v] + 1)
            continue;
        int pushed = dfs(to, min(minCapacity, capacity[id] - flow[id]), limitation);
        if (pushed == 0)
            continue;
        flow[id] += pushed;
        flow[id ^ 1] -= pushed;
        return pushed;
    }
    return 0;
}

int max_flow(int limitation) {
    int answer = 0;
    while (bfs(N, limitation)) {
        ptr.assign(N + 1, 0);
        int cur_flow = dfs(start, inf, limitation);
        while (cur_flow != 0) {
            answer += cur_flow;
            cur_flow = dfs(start, inf, limitation);
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    N = 2 * n + 1;
    int m = n * n + 2 * n;
    dist.resize(N + 1);
    capacity.resize(2 * m);
    flow.resize(2 * m);
    ptr.resize(N + 1);
    vv.resize(N + 1);
    cost.resize(2 * m);
    edges.resize(2 * m);
    start = 0;
    finish = N;

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
        cost[id] = inf;
        cost[id + 1] = inf;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x;
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
            cost[id + 1] = x;
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
        cost[id] = inf;
        cost[id + 1] = inf;
    }

    int l = 0, r = inf + 1;
    while (r - l > 1) {
        flow.assign(2 * m, 0);
        int mid = (r + l) / 2;
        int current_flow = max_flow(mid);
        if (current_flow == n)
            l = mid;
        else
            r = mid;
    }
    cout << l;
}
