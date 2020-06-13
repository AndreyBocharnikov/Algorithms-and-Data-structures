#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

int64_t gcdex(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t d = gcdex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int64_t a, b, n, m;
        cin >> a >> b >> n >> m;
        int64_t x, y;
        gcdex(n, m, x, y);
        x = (x % m + m) % m;
        int64_t k = (((b - a) * x) % m + m) % m;
        cout << 1LL * a + n * k << '\n';
    }
}


