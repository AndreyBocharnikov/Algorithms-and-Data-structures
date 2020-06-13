#include <iostream>
#include <vector>

using namespace std;

vector<int> p, s(1000001);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    p.reserve(5000);
    for (int i = 2; i <= 1000000; i++) {
        if (s[i] == 0) {
            s[i] = i;
            p.push_back(i);
        }
        for (size_t j = 0; j < p.size(); j++) {
            if (i * p[j] <= 1000000) {
                s[i * p[j]] = p[j];
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while (s[x] != x) {
            cout << s[x] << " ";
            x /= s[x];
        }
        cout << s[x] << '\n';
    }
}
