#include <fstream>
#include <vector>
#include <algorithm>
#define ll long long
#define f first
#define s second
using namespace std;

ll a, b, m = 1e6, p = 1e9 + 207, p2 = 1e9 + 9, h, h2, a2, b2;
string x;
bool ok;
vector <vector <pair <ll, string> > > vv;

ifstream cin("map.in");
ofstream cout("map.out");

ll hesh() {
    ll sum = 0;
    for (int i = 0; i < int(x.length()); i++)
        sum = (sum * 67 + (x[i] - 'A' + 1)) % p;
    return (((a * sum) + b) % p) % m;
}

ll hesh2() {
    ll sum = 0;
    for (int i = 0; i < int(x.length()); i++)
        sum = (sum * 71 + (x[i] - 'A' + 1)) % p2;
    return (((a2 * sum) + b2) % p2) % m;
}

ll f(ll v) {
    ll cur = rand() * rand();
    if (cur < p2)
        return cur;
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, t;

    for (int i = 0; i < 30; i++) {
        a = f(a) + 1;
        b = f(b);
        a2 = f(a2) + 1;
        b2 = f(b2);
    }
    vv.resize(m);
    while (cin >> s) {
        if (s == "put") {
            cin >> x >> t;
            h = hesh();
            h2 = hesh2();
            if (int(vv[h].size()) > 0) {
                bool ok = 0;
                for (int j = 0; j < int(vv[h].size()); j++)
                    if (vv[h][j].first == h2)
                        vv[h][j].second = t,
                        ok = 1;
                if (!ok)
                    vv[h].push_back({h2, t});
            } else {
                vv[h].push_back({h2, t});
            }
        }
        if (s == "get") {
            cin >> x;
            h = hesh();
            h2 = hesh2();
            bool ok = 0;
            for (int i = 0; i < int(vv[h].size()); i++)
                if (vv[h][i].first == h2) {
                    if (vv[h][i].second == "-1") {
                        cout << "none" << endl;
                    } else {
                        cout << vv[h][i].second << endl;
                    }
                    ok = 1;
                }
            if (!ok)
                cout << "none" << endl;
        }
        if (s == "delete") {
            cin >> x;
            h = hesh();
            h2 = hesh2();
            for (int i = 0; i < int(vv[h].size()); i++)
                if (vv[h][i].first == h2)
                    vv[h][i].second = "-1";
        }
    }
}

