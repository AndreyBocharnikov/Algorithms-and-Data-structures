// find period of string
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> z_function(string const& s) {
    size_t len = s.length(), l = 0;
    vector <int> z(len);
    for (size_t i = 1; i < len; i++) {
        int i_ = i - l;
        z[i] = max(0, min(z[i_], z[l] - i_));
        while (i + z[i] < len && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > l + z[l])
            l = i;
    }
    return z;
}

int main() {
    string s;
    cin >> s;
    vector <int> z = z_function(s);
    int n = int(s.length());
    for (int i = 1; i < n; i++) {
        if (n % i == 0 && i + z[i] == n)
            return cout << i, 0;
    }
    cout << n;
}
