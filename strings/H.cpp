// polynomial hash
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

struct hesher {
    hesher(string const& s) {
        size_t len = s.length();
        pows.resize(len);
        pows[0] = pow;
        for (size_t i = 1; i < len; i++)
            pows[i] = mul(pows[i - 1], pow);

        heshes.resize(len + 1);
        heshes[len - 1] = s.back() - 'a' + 1;
        for (int i = int(len) - 2; i >= 0; i--)
            heshes[i] = add(s[i] - 'a' + 1, mul(heshes[i + 1], pow));
    }

    static int mul(int a, int b) {
        return int((1LL * a * b) % mod);
    }

    static int add(int a, int b) {
        return (a + b) % mod;
    }

    static int sub(int a, int b) {
        if (a - b < 0)
            return a - b + mod;
        else
            return a - b;
    }

 private:
    static const int mod = 998244353;
    int pow = 31;

 public:
    vector <int> pows, heshes;
};

int main() {
    string s;
    cin >> s;
    hesher hesh = hesher(s);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (hesher::sub(hesh.heshes[a - 1], hesher::mul(hesh.heshes[b], hesh.pows[b - a])) ==
            hesher::sub(hesh.heshes[c - 1], hesher::mul(hesh.heshes[d], hesh.pows[d - c])))
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}
