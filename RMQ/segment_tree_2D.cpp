#include <bits/stdc++.h>
#define ll long long
#define f first
#define s second
#define all(x) (x).begin(), (x).end()
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
using namespace std;

vector<unsigned int> ar(1 << 17);
vector <vector <unsigned int> > tree(1 << 19);

unsigned int a, b, cur = 0;

unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void build(int v, int l, int r) {
    if (l == r) {
        tree[v] = {ar[l]};
        return;
    }
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    size_t id = 0, id2 = 0;
    while (id < tree[v * 2].size() || id2 < tree[v * 2 + 1].size()) {
        if (id == tree[v * 2].size()) {
            tree[v].push_back(tree[v * 2 + 1][id2]);
            id2++;
            continue;
        }
        if (id2 == tree[v * 2 + 1].size()) {
            tree[v].push_back(tree[v * 2][id]);
            id++;
            continue;
        }
        if (tree[v * 2][id] < tree[v * 2 + 1][id2])
            tree[v].push_back(tree[v * 2][id]),
            id++;
        else
            tree[v].push_back(tree[v * 2 + 1][id2]),
            id2++;
    }
}

unsigned int query(int v, int left, int right, int l, int r, int x, int y) {
    if (left > r || right < l)
        return 0;
    if (l <= left && right <= r) {
        auto up = upper_bound(tree[v].begin(), tree[v].end(), y);
        auto low = lower_bound(tree[v].begin(), tree[v].end(), x);
        return (unsigned int) (up - low);
    }
    int m = (left + right) / 2;
    return query(v * 2, left, m, l, r, x, y) + query(v * 2 + 1, m + 1, right, l, r, x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q;
    cin >> q >> a >> b;
    for (int i = 0; i < 1 << 17; i++)
        ar[i] = nextRand24();
    build(1, 0, (1 << 17) - 1);
    unsigned int ans = 0;
    for (int i = 0; i < q; i++) {
        auto l = nextRand17(), r = nextRand17(), x = nextRand24(), y = nextRand24();
        if (l > r)
            swap(l, r);
        if (x > y)
            swap(x, y);
        auto cur = query(1, 0, (1 << 17) - 1, l, r, x, y);
        b += cur;
        ans += cur;
    }
    cout << ans;
}

