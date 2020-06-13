// String searching algorithm
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> z_function(string const& s) {
    size_t len = s.length(), l = 0;
    vector <int> z(len);
    z[1] = 0;
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
    string t, p;
    cin >> t >> p;
    size_t p_len = p.length(), t_len = t.length();
    string s = t + '$' + p;
    reverse(t.begin(), t.end());
    reverse(p.begin(), p.end());
    string s_rev = t + '$' + p;
    vector <int> z = z_function(s);
    vector <int> z_rev = z_function(s_rev), ans;
    reverse(z_rev.begin() + t_len + 1, z_rev.end());
    for (size_t i = t_len + 1; i <= p_len + 1; i++) {
        if (z[i] == int(t_len)) {
            ans.push_back(i);
            continue;
        }

        if (z[i] + z_rev[i + t_len - 1] + 1 == int(t_len)) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans)
        cout << i - t_len << ' ';
}



