#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 151;
int lnk[MAXN], used[MAXN], used_n[MAXN];
bool dfs(int v, vector < vector <int> > &vv) {
    used[v] = 1;
    for (size_t i = 0; i < vv[v].size(); i++) {
        int to = vv[v][i];
        if (lnk[to] == -1 || (!used[lnk[to]] && dfs(lnk[to], vv))) {
            lnk[to] = v;
            return 1;
        }
    }
    return 0;
}

void dfs_v(int v, vector<vector<int>> &graf0, vector<vector<int>> &graf1) {
    used[v] = 1;
    for (size_t i = 0; i < graf1[v].size(); i++) {
        int to = graf1[v][i];
        if (!used_n[to]) {
            used_n[to] = 1;
            for (size_t j = 0; j < graf0[to].size(); j++) {
                if (!used[graf0[to][j]])
                    dfs_v(graf0[to][j], graf0, graf1);
            }
        }
    }
}
int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int m, n, val;
        cin >> m >> n;
        vector < vector <int> > vv(m + 1);
        vector <int> flag(n + 1);
        for (int j = 1; j <= n; j++)
            lnk[j] = -1, used_n[j] = 0;
        for (int j = 1; j <= m; j++)
            used[j] = 0;
        for (int j = 1; j <= m; j++) {
            for (int g = 1; g <= n; g++)
                flag[g] = 0;
            cin >> val;
            while (val != 0) {
                flag[val] = 1;
                cin >> val;
            }
            for (int g = 1; g <= n; g++)
                if (!flag[g])
                    vv[j].push_back(g);
        }
        for (int j = 1; j <= m; j++) {
            for (int g = 1; g <= m; g++)
                used[g] = 0;
            dfs(j, vv);
        }
        vector < vector <int> > graf[2];
        graf[0].resize(n + 1);
        graf[1].resize(m + 1);
        vector <int> flag_m(m + 1);
        for (int j = 1; j <= m; j++) {
            for (size_t g = 0; g < vv[j].size(); g++) {
                int to = vv[j][g];
                if (lnk[to] == j)
                    graf[0][to].push_back(j);
                else
                    graf[1][j].push_back(to);
            }
        }
        for (int j = 1; j <= n; j++)
            if (lnk[j] != -1) {
                flag_m[lnk[j]] = 1;
            }
        for (int j = 1; j <= m; j++)
            used[j] = 0;
        for (int j = 1; j <= m; j++)
            if (!flag_m[j])
                dfs_v(j, graf[0], graf[1]);
        vector <int> ans_n, ans_m;
        for (int j = 1; j <= m; j++)
            if (used[j])
                ans_m.push_back(j);
        for (int j = 1; j <= n; j++)
            if (!used_n[j])
                ans_n.push_back(j);
        cout << ans_n.size() + ans_m.size() << '\n';
        cout << ans_m.size() << " " << ans_n.size() << '\n';
        for (size_t j = 0; j < ans_m.size(); j++)
            cout << ans_m[j] << " ";
        cout << '\n';
        for (size_t j = 0; j < ans_n.size(); j++)
            cout << ans_n[j] << " ";
        cout << "\n\n";
    }
}
