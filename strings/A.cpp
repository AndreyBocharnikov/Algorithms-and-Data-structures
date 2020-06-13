#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string p, t;
    cin >> p >> t;
    size_t p_len = p.length(), t_len = t.length();
    if (p_len > t_len)
        return cout << 0, 0;
    vector <int> ans;
    for (size_t i = 0; i <= t_len - p_len; i++)
        if (t.substr(i, p_len) == p)
            ans.push_back(i);
    cout << ans.size() << '\n';
    for (size_t i : ans)
        cout << i + 1 << " ";
}
