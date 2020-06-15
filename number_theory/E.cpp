#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

int gcdex(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcdex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int64_t pow(int64_t x, int64_t s, int64_t n) {
    int64_t res = 1;
    while (s > 0) {
        if (s % 2 == 1) {
            res *= x;
            res %= n;
        }
        s /= 2;
        x *= x;
        x %= n;
    }
    return res;
}

bool is_prime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, e, C;
    cin >> n >> e >> C;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i != 0) {
            continue;
        }
        if (is_prime(i) && is_prime(n / i)) {
            int phi = (i - 1) * (n / i - 1);
            if (__gcd(phi, e) == 1) {
                int x, y;
                int d = gcdex(e, phi, x, y);
                assert(d == 1);
                cout << pow(C, (x % phi + phi) % phi, n);
                return 0;
            }
        }
    }
}

