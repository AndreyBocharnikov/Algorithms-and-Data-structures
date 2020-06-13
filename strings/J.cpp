// Найти кол-во различных подстрок для каждого префикса строки
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    size_t len = int(s.length()), l = 0;
    vector <int> z(len);
    string cur_s;
    int ans = 0;
    for (size_t i = 0; i < len; i++) {
        cur_s += s[i];
        reverse(cur_s.begin(), cur_s.end());
        z.assign(0, len);

        l = 0;
        for (size_t i = 1; i < cur_s.length(); i++) {
            int i_ = i - l;
            z[i] = max(0, min(z[i_], z[l] - i_));
            while (i + z[i] < len && cur_s[z[i]] == cur_s[i + z[i]]) {
                z[i]++;
            }
            if (i + z[i] > l + z[l])
                l = i;
        }
        int mx = 0;
        for (size_t i = 1; i < cur_s.length(); i++)
            mx = max(mx, z[i]);
        ans += int(cur_s.length()) - mx;
        cout << ans << '\n';

        reverse(cur_s.begin(), cur_s.end());
    }
}

