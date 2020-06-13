// z function
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    size_t len = s.length(), l = 0;
    vector <int> z(len + 1);
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
    for (size_t i = 1; i < len; i++)
        cout << z[i] << " ";
}

