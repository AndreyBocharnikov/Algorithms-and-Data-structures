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
            ++cnt[s[i] - '0' + 1];
        }
        for (size_t i = 1; i <= alphabet_size; i++) {
            cnt[i] += cnt[i - 1];
        }

        permutation[0] = int(n - 1);
        for (size_t i = 0; i < n - 1; ++i) {
            --cnt[s[i] - '0' + 1];
            permutation[cnt[s[i] - '0' + 1]] = int(i);
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
    size_t n, m;
    std::cin >> n >> m;
    for (size_t i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        s += char(x + '0' - 1);
        // std::cout << char(x + '0' - 1) << " " << s << '\n';
    }
    if (n == 1) {
        std::cout << 1 << '\n' << 1 << '\n';
        if (s == "9") {
            std::cout << 10;
        } else {
            std::cout << char(s[0] + 1);
        }
        return 0;
    }
    suffix_array sa = suffix_array(s);
    auto answer = sa.make_answer();
    auto lcps = sa.count_lcps(answer);
    // for (int i : lcps) {
    //    std::cout << i << ' ';
    // }
    // std::cout << std::endl;
    std::vector<std::pair<int, int >> vp(n - 1);
    for (size_t i = 0; i < n - 1; i++) {
        vp[i].first = lcps[i];
        vp[i].second = int(i);
    }

    std::sort(vp.begin(), vp.end());
    long long result = n;
    int cnt = int(n), pos = -1;
    long long prev_value = vp[0].first;
    std::vector<int> prev_value_pos;
    prev_value_pos.push_back(vp[0].second);
    std::set<int> boundaries;
    for (size_t i = 1; i < n - 1; i++) {
        long long current_value = vp[i].first;
        int current_pos = vp[i].second;
        if (current_value > prev_value) {
            for (int j : prev_value_pos) {
                boundaries.insert(j);
            }
            prev_value_pos.clear();
            prev_value = current_value;
        }
        prev_value_pos.push_back(current_pos);
        auto it_right = boundaries.upper_bound(current_pos);
        int right_bound;
        if (it_right == boundaries.end()) {
            right_bound = int(n - 1);
        } else {
            right_bound = *it_right;
        }
        int left_bound;
        if (it_right == boundaries.begin()) {
            left_bound = -1;
        } else {
            auto it_left = --it_right;
            left_bound = *it_left;
        }
        if (current_value * (right_bound - left_bound) > result) {
            cnt = right_bound - left_bound;
            result = current_value * cnt;
            pos = int(i);
        }
    }
    if (pos == -1) {
        std::cout << n << '\n' << n << '\n';
        for (char c : s.substr(0, n)) {
            if (char(c + 1) == ':') {
                std::cout << 10;
            } else {
                std::cout << char(c + 1);
            }
            std::cout << " ";
        }
    } else {
        long long length = result / cnt;
        std::cout << result << '\n' << length << '\n';
        auto index = size_t(answer[vp[pos].second + 1] - 1);
        // std::cout << pos << " " << index << '\n';
        // std::cout << answer[index + 1] << '\n';
        for (auto j = index; j < index +length; j++) {
            if (char(s[j] + 1) == ':') {
                std::cout << 10;
            } else {
                std::cout << char(s[j] + 1);
            }
            std::cout << " ";
            // std::cout << char(s[j] + 1) << " ";
        }
    }
}
