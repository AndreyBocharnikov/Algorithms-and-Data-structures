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

bool decompose(int v, int n, vector <int> &current_answer) {
    used.assign(n + 1, false);
    vector <int> current_edges;
    while (!used[v]) {
        if (v == finish)
            break;
        int cur_edge = -1, next_vertex = -1;
        for (size_t i = 0; i < vv[v].size(); i++) {
            int to = vv[v][i].first, id = vv[v][i].second;
            if (flow[id] > 0) {
                cur_edge = id;
                next_vertex = to;
                break;
            }
        }
        if (cur_edge == -1)
            return false;
        current_edges.push_back(cur_edge);
        used[v] = 1;
        v = next_vertex;
    }

    int min_flow_on_path = 2 * 1e9;
    for (int ids : current_edges) {
        min_flow_on_path = min(min_flow_on_path, flow[ids]);
    }
    for (int ids : current_edges) {
        flow[ids] -= min_flow_on_path;
    }
    current_edges.push_back(min_flow_on_path);
    current_answer = current_edges;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    dist.resize(n + 1);
    used.resize(n + 1);
    edges.resize(2 * m);
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
        edges[2 * i] = {f, t};
        edges[2 * i + 1] = {t, f};
        flow[2 * i] = 0;
        flow[2 * i + 1] = 0;
        capacity[2 * i] = c;
        capacity[2 * i + 1] = 0;
    }

    max_flow(n);
    vector <vector <int> > answer;
    vector <int> tmp;
    while (decompose(start, n, tmp)) {
        answer.push_back(tmp);
    }
    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].back() << " " << answer[i].size() - 1 << " ";
        for (size_t j = 0; j < answer[i].size() - 1; j++)
            cout << answer[i][j] / 2 + 1 << " ";
        cout << '\n';
    }
}
/*
5 5
1 2 4
2 5 2
2 3 2
3 4 2
4 1 2
*/

