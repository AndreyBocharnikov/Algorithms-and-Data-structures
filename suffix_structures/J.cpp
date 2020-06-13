#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

struct suffix_array {
    explicit suffix_array(std::string &s) {
        s += '$';
        n = s.length();
        cnt.resize(std::max(n, alphabet_size + 1));
        two_pow = static_cast<size_t>(std::log2(n - 1)) + 2;
        equivalence.resize(two_pow, std::vector<int>(n));
        permutation.resize(n);
        cnt[0] = 1;
        for (size_t i = 0; i < n - 1; ++i) {
            int index = s[i] - 'a' + 1;
            ++cnt[index];
        }
        for (size_t i = 1; i <= alphabet_size; i++) {
            cnt[i] += cnt[i - 1];
        }

        permutation[0] = int(n - 1);
        for (size_t i = 0; i < n - 1; ++i) {
            int index = s[i] - 'a' + 1;
            --cnt[index];
            permutation[cnt[index]] = int(i);
        }
        equivalence[0][permutation[0]] = 0;
        num_classes = 1;
        for (size_t i = 1; i < n; ++i) {
            if (s[permutation[i]] != s[permutation[i - 1]]) {
                ++num_classes;
            }
            equivalence[0][permutation[i]] = num_classes - 1;
        }

        new_permutation.resize(n);
        for (int k = 0; (1 << k) < int(n); ++k) {
            int shift = (1 << k);
            for (size_t i = 0; i < n; ++i) {
                new_permutation[i] = permutation[i] - shift;
                if (new_permutation[i] < 0)
                    new_permutation[i] += n;
            }
            cnt.assign(num_classes, 0);
            for (size_t i = 0; i < n; ++i) {
                ++cnt[equivalence[k][new_permutation[i]]];
            }
            for (int i = 1; i < num_classes; ++i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = int(n) - 1; i >= 0; --i) {
                permutation[--cnt[equivalence[k][new_permutation[i]]]] = new_permutation[i];
            }

            new_permutation[permutation[0]] = 0;
            num_classes = 1;
            for (size_t i = 1; i < n; ++i) {
                size_t right = (permutation[i] + shift) % n,
                        right2 = (permutation[i - 1] + shift) % n;
                if (equivalence[k][permutation[i]] != equivalence[k][permutation[i - 1]] ||
                    equivalence[k][right] != equivalence[k][right2]) {
                    ++num_classes;
                }
                equivalence[k + 1][permutation[i]] = num_classes - 1;
            }
        }
    }

    std::vector<int> count_lcps(std::vector<int> const& answer) {
        std::vector<int> ans(n - 2);
        for (size_t i = 1; i < n - 1; ++i) {
            size_t cur_ans = 0;
            for (int j = int(two_pow) - 2; j >= 0; j--) {
                size_t id = answer[i] - 1 + cur_ans, id2 = answer[i + 1] - 1 + cur_ans;
                if (equivalence[j][id] == equivalence[j][id2]) {
                    cur_ans += (1 << j);
                }
            }
            ans[i - 1] = int(cur_ans);
        }
        return ans;
    }

    int count_lcp(int i, int j) {
        int res = 0;
        for (int k = int(two_pow) - 2; k >= 0; k--) {
            if (equivalence[k][i + res] == equivalence[k][j + res]) {
                res += 1 << k;
            }
        }
        return res;
    }

    std::vector<int> make_answer() {
        std::vector<int> answer(n);
        for (size_t i = 0; i < n; ++i) {
            answer[equivalence[two_pow - 1][i]] = int(i) + 1;
        }
        return answer;
    }

 private:
    size_t alphabet_size = 27;
    size_t n;
    size_t two_pow;
    int num_classes;
    std::vector<int> permutation, cnt, new_permutation;

 public:
    std::vector<std::vector<int>> equivalence;
};


int main() {
    std::string s;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cin >> s;
    size_t n = s.length();
    std::reverse(s.begin(), s.end());
    suffix_array sa = suffix_array(s);
    auto answer = sa.make_answer();
    std::vector<int> rev_answer(n + 1);
    for (size_t i = 1; i <= n; i++) {
        rev_answer[answer[i]] = int(i);
    }
    std::vector<int> cnt_prefs(n);
    std::vector<std::set<int>> used_letters(26);
    std::vector<int> lcp_cnt(n);
    for (int i = int(n) - 1; i >= 0; i--) {
        auto it = used_letters[s[i] - 'a'].upper_bound(rev_answer[i + 1]);
        int pos_right = -1, pos_left = -1;
        if (it == used_letters[s[i] - 'a'].end()) {
            if (!used_letters[s[i] - 'a'].empty()) {
                it--;
                pos_left = *it;
            }
        } else {
            pos_right = *it;
            if (it != used_letters[s[i] - 'a'].begin()) {
                it--;
                pos_left = *it;
            }
        }
        used_letters[s[i] - 'a'].insert(rev_answer[i + 1]);
        int lcp = 0;
        if (pos_left != -1) {
            lcp = sa.count_lcp(i, answer[pos_left] - 1);
        }
        if (pos_right != -1) {
            lcp = std::max(lcp, sa.count_lcp(i, answer[pos_right] - 1));
        }
        lcp_cnt[i] = int(n - i - lcp);
    }
    std::reverse(lcp_cnt.begin(), lcp_cnt.end());
    long long sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += lcp_cnt[i];
        std::cout << sum << '\n';
    }
}
