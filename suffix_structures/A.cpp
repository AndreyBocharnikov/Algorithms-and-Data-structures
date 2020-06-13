#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

vector<pair<pair<int, int>, char>> vp;

struct trie {
    explicit trie(int nn) {
        letters.resize(26, nullptr);
        terminal = false;
        node_number = nn;
    }

    static void add(trie* node, string const& s, size_t it, int& node_cnt) {
        if (it == s.length()) {
            node->terminal = true;
            return;
        }

        if (node->letters[s[it] - 'a'] == nullptr) {
            node->letters[s[it] - 'a'] = new trie(node_cnt);
            vp.push_back({{node->node_number, node_cnt}, s[it]});
            node_cnt++;
            // cout << node << " " << s[it] << " " << node->letters[s[it] - 'a'] << '\n';
        }
        add(node->letters[s[it] - 'a'], s, it + 1, node_cnt);
    }

    vector <trie*> letters;
    bool terminal;
    int node_number;
};

int main() {
    std::string s;
    std::cin >> s;
    trie* root = new trie(1);
    int node_cnt = 2;
    for (size_t i = 0; i < s.length(); i++) {
        std::string copy = s.substr(i);
        trie::add(root, copy, 0, node_cnt);
    }
    cout << node_cnt - 1 << " " << node_cnt - 2 << '\n';
    for (int i = 0; i < node_cnt - 2; i++) {
        cout << vp[i].first.first << " " << vp[i].first.second << " " << vp[i].second << '\n';
    }
}
