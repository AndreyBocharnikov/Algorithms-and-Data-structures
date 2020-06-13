// String searching algorithm
#include <iostream>
#include <string>
#include <vector>

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
    string s = t + '$' + p;
    vector <int> z = z_function(s);
    size_t p_len = p.length(), t_len = t.length();
    vector <size_t> ans;
    for (size_t i = t_len + 1; i < t_len + p_len + 1; i++)
        if (z[i] == int(t_len))
            ans.push_back(i);
    cout << ans.size() << '\n';
    for (size_t i : ans)
        cout << i - t_len << " ";
}


