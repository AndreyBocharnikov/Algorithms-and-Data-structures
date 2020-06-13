#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector <multiset<int> > vv;
vector <int> deg;

void euler(int v) {
    // cout << v << " ";
    while (!vv[v].empty()) {
        int to = *vv[v].begin();
        vv[v].erase(vv[v].begin());
        vv[to].erase(vv[to].find(v));
        euler(to);
    }
    cout << v << " ";
}

int main() {
    // ifstream fin("input.txt");
    int n, m = 0;
    cin >> n;
    vv.resize(n + 1);
    deg.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        m += cnt;
        deg[i] = cnt;
        for (int j = 0; j < cnt; j++) {
            int to;
            cin >> to;
            vv[i].insert(to);
        }
    }
    int cnt_odd = 0, s = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 == 1) {
            cnt_odd++;
            if (s == -1)
                s = i;
        }
    }
    if (s == -1)
        s = 1;
    if (cnt_odd == 3)
        return cout << -1, 0;
    cout << m / 2 << '\n';
    euler(s);
}
