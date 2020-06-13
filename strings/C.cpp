// prefix-function
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    string s;
    cin >> s;
    size_t len = s.length();
    s = '%' + s;
    vector <int> pref(len + 1);
    for (size_t i = 2; i <= len; i++) {
        int k = pref[i - 1];
        while (k > 0 && s[k + 1] != s[i]) {
            k = pref[k];
        }
        if (s[k + 1] == s[i])
            k++;
        pref[i] = k;
    }
    for (size_t i = 1; i <= len; i++)
        cout << pref[i] << " ";
}
