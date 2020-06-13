#include <iostream>
#include <vector>
#include <tuple>

struct suffix_array {
    explicit suffix_array(std::string s) {
        s += '$';
        n = s.length();
        cnt.resize(std::max(n, alphabet_size + 1));
        equivalence.resize(n);
        permutation.resize(n);
        cnt[0] = 1;
        for (size_t i = 0; i < n - 1; ++i) {
            ++cnt[s[i] - 'a' + 1];
        }
        for (size_t i = 1; i <= alphabet_size; i++) {
            cnt[i] += cnt[i - 1];
        }

        permutation[0] = int(n - 1);
        for (size_t i = 0; i < n - 1; ++i) {
            --cnt[s[i] - 'a' + 1];
            permutation[cnt[s[i] - 'a' + 1]] = int(i);
        }
        equivalence[permutation[0]] = 0;
        num_classes = 1;
        for (size_t i = 1; i < n; ++i) {
            if (s[permutation[i]] != s[permutation[i - 1]]) {
                ++num_classes;
            }
            equivalence[permutation[i]] = num_classes - 1;
        }

        new_permutation.resize(n);
        new_equivalence.resize(n);
        for (int k = 0; (1 << k) < int(n); ++k) {
            int shift = (1 << k);
            for (size_t i = 0; i < n; ++i) {
                new_permutation[i] = permutation[i] - shift;
                if (new_permutation[i] < 0)
                    new_permutation[i] += n;
            }
            cnt.assign(num_classes, 0);
            for (size_t i = 0; i < n; ++i) {
                ++cnt[equivalence[new_permutation[i]]];
            }
            for (int i = 1; i < num_classes; ++i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = int(n) - 1; i >= 0; --i) {
                permutation[--cnt[equivalence[new_permutation[i]]]] = new_permutation[i];
            }

            new_permutation[permutation[0]] = 0;
            num_classes = 1;
            for (size_t i = 1; i < n; ++i) {
                size_t right = (permutation[i] + shift) % n,
                        right2 = (permutation[i - 1] + shift) % n;
                if (equivalence[permutation[i]] != equivalence[permutation[i - 1]] ||
                    equivalence[right] != equivalence[right2]) {
                    ++num_classes;
                }
                new_equivalence[permutation[i]] = num_classes - 1;
            }
            equivalence = new_equivalence;
        }
    }

 private:
    size_t alphabet_size = 27;
    size_t n;
    int num_classes;
    std::vector<int> permutation, cnt, new_permutation, new_equivalence;

 public:
    std::vector<int> equivalence;
};


int main() {
    std::string s;
    std::cin >> s;
    int n = int(s.length()) + 1;
    suffix_array sa = suffix_array(s);
    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        answer[sa.equivalence[i]] = i + 1;
    }
    for (int i = 1; i < n; i++) {
        std::cout << answer[i] << " ";
    }
    return 0;
}
