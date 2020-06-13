#include <iostream>
#include <vector>

using namespace std;

vector<int> p, s(20000001);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    p.reserve(5000);
    for (int i = 2; i <= 20000000; i++) {
        if (s[i] == 0) {
            s[i] = i;
            p.push_back(i);
        }
        for (size_t j = 0; j < p.size(); j++) {
            if (i * p[j] <= 20000000) {
                s[i * p[j]] = p[j];
            } else {
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (s[x] == x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
