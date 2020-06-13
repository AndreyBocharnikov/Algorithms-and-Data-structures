#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    uint32_t h = 0, x;
    cin >> n >> x;
    int sqrtn = int(sqrt(n));
    vector<int> is_prime(sqrtn + 1), primes;
    for (int i = 2; i <= sqrtn; i++) {
        if (!is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= sqrtn; j += i) {
                is_prime[j] = true;
            }
        }
    }

    vector <int> block(sqrtn);
    for (int k = 0, maxk = n / sqrtn; k <= maxk; k++) {
        block.assign(sqrtn, 0);
        int start = k * sqrtn;
        // cout << "start " << start << " ";
        for (size_t j = 0; j < primes.size(); j++) {
            int sp = max(2, (start + primes[j] - 1) / primes[j]);
            // cout << "prime " << primes[j] << " ";
            for (sp = sp * primes[j] - start; sp < sqrtn; sp += primes[j]) {
                // cout << sp << " ";
                block[sp] = true;
            }
            // cout << '\n';
        }
        if (k == 0) {
            block[0] = block[1] = true;
        }

        for (int i = 0; i < sqrtn && start + i <= n; i++) {
            if (!block[i]) {
                // cout << "res " << start + i << " ";
                h = h * x + start + i;
            }
        }
    }
    cout << h;
}
