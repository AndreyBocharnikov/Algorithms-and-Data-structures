#include <iostream>
#include <vector>
#include <set>
using namespace std;

vector <multiset<int> > vv;
vector <int> deg, ans;
set <pair<int, int> > fake;

void euler(int v) {
    // cout << v << " ";
    while (!vv[v].empty()) {
        int to = *vv[v].begin();
        vv[v].erase(vv[v].begin());
        auto tmp = vv[to].find(v);
        if (tmp != vv[to].end())
            vv[to].erase(tmp);
        euler(to);
    }
    ans.push_back(v);
}

int main() {
    int n, m;
    cin >> n >> m;
    vv.resize(n + 1);
    deg.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int f, t;
        cin >> f >> t;
        vv[f].insert(t);
        vv[t].insert(f);
        deg[f]++;
        deg[t]++;
    }
    vector <int> odd;
    for (int i = 1; i <= n; i++)
        if (deg[i] % 2 == 1)
            odd.push_back(i);
    /*for (int i = 0; i < odd.size(); i++)
        cout << odd[i] << " ";
    cout << '\n';*/
    for (size_t i = 1; i < odd.size(); i += 2) {
        fake.insert({odd[i - 1], odd[i]}),
        fake.insert({odd[i], odd[i - 1]});
        vv[odd[i - 1]].insert(odd[i]);
        vv[odd[i]].insert(odd[i - 1]);
    }
    euler(1);
    vector <vector <int> > answers;
    vector <int> tmp_ans;
    tmp_ans.push_back(ans[0]);
    // cout << ans[0] << " ";
    for (size_t i = 1; i < ans.size(); i++) {
        // cout << ans[i] << " ";
        if (fake.find({ans[i - 1], ans[i]}) == fake.end()) {
            tmp_ans.push_back(ans[i]);
        } else {
            fake.erase({ans[i - 1], ans[i]});
            fake.erase({ans[i], ans[i - 1]});
            answers.push_back(tmp_ans);
            tmp_ans.clear();
            tmp_ans.push_back(ans[i]);
        }
        // cout << "!" << answers.size() << " " << tmp_ans.size() << '\n';
    }
    cout << max(int(answers.size()), 1) << '\n';
    for (size_t i = 0; i < tmp_ans.size() - 1; i++)
        cout << tmp_ans[i] << " ";
    if (answers.size() == 0)
        cout << tmp_ans[0];
    for (size_t i = 0; i < answers.size(); i++) {
        for (size_t j = 0; j < answers[i].size(); j++)
            cout << answers[i][j] << " ";
        cout << '\n';
    }
}
