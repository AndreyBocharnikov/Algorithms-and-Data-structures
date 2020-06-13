// find period of string
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    size_t len = s.length();
    for (size_t i = 1; i <= len; i++) {
        if (len % i != 0)
            continue;
        bool ok = true;
        for (size_t j = 0; j < i; j++) {
            char first = s[j];
            for (size_t k = j; k < len; k += i) {
                ok &= (first == s[k]);
                if (!ok)
                    break;
            }
            if (!ok)
                break;
        }
        if (ok)
            return cout << i, 0;
    }
}
