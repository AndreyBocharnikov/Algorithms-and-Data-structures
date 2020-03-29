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
struct node {
    string key;
    node *prv, *next;
    node(string cur_key, node *cur_prv, node *cur_next) {
        key = cur_key;
        prv = cur_prv;
        next = cur_next;
    }
};
vector <vector <pair <ll, node*> > > vv;

ifstream cin("linkedmap.in");
ofstream cout("linkedmap.out");

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

void change(node *v) {
    if (v->prv == nullptr && v->next == nullptr) {
        return;
    }
    if (v->prv == nullptr) {
        v->next->prv = nullptr;
        return;
    }
    if (v->next == nullptr) {
        v->prv->next = nullptr;
        return;
    }
    v->next->prv = v->prv;
    v->prv->next = v->next;
    return;
}

void cout_next(node *v) {
    if (v->key == "-1") {
        cout << "none\n";
        return;
    }
    if (v->next == nullptr)
        cout << "none\n";
    else
        cout << v->next->key << '\n';
}

void cout_prv(node *v) {
    if (v->key == "-1") {
        cout << "none\n";
        return;
    }
    if (v->prv == nullptr)
        cout << "none\n";
    else
        cout << v->prv->key << '\n';
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
    node *cur_prv = nullptr, *cur_next = nullptr;
    vv.resize(m);
    while (cin >> s) {
        if (s == "put") {
            cin >> x >> t;
            h = hesh();
            h2 = hesh2();
            node *cur = new node(t, cur_prv, cur_next);
            if (int(vv[h].size()) > 0) {
                bool ok = 0;
                for (int j = 0; j < int(vv[h].size()); j++)
                    if (vv[h][j].first == h2) {
                        if (vv[h][j].second->key != "-1") {
                            vv[h][j].second->key = t;
                        } else {
                            vv[h][j].second = cur;
                            if (cur_prv != nullptr) {
                                cur_prv->next = vv[h][j].second;
                            }
                            cur_prv = cur;
                        }
                        ok = 1;
                    }
                if (!ok) {
                    vv[h].push_back({h2, cur});
                    if (cur_prv != nullptr) {
                        cur_prv->next = vv[h].back().second;
                    }
                    cur_prv = cur;
                }
            } else {
                vv[h].push_back({h2, cur});
                if (cur_prv != nullptr) {
                    cur_prv->next = vv[h].back().second;
                }
                cur_prv = cur;
            }
        }
        if (s == "get") {
            cin >> x;
            h = hesh();
            h2 = hesh2();
            bool ok = 0;
            for (int i = 0; i < int(vv[h].size()); i++)
                if (vv[h][i].first == h2) {
                    if (vv[h][i].second->key == "-1") {
                        cout << "none" << '\n';
                    } else {
                        cout << vv[h][i].second->key << '\n';
                    }
                    ok = 1;
                }
            if (!ok)
                cout << "none" << '\n';
        }
        if (s == "delete") {
            cin >> x;
            h = hesh();
            h2 = hesh2();
            for (int i = 0; i < int(vv[h].size()); i++)
                if (vv[h][i].first == h2 && vv[h][i].second->key != "-1") {
                    if (cur_prv == vv[h][i].second)
                        cur_prv = vv[h][i].second->prv;
                    vv[h][i].second->key = "-1";
                    change(vv[h][i].second);
                }
        }
        if (s == "next" || s == "prev") {
            cin >> x;
            h = hesh();
            h2 = hesh2();
            bool ok = 0;
            for (int i = 0; i < int(vv[h].size()); i++)
                if (vv[h][i].first == h2) {
                    ok = 1;
                    if (s == "next") {
                        cout_next(vv[h][i].second);
                    } else {
                        cout_prv(vv[h][i].second);
                    }
                }
            if (!ok)
                cout << "none\n";
        }
        // cout << endl;
    }
}

