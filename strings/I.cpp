// trie task
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

struct trie {
    trie() {
        letters.resize(26, nullptr);
        terminal = false;
    }

    static void add(trie* node, string const& s, size_t it, int word_id) {
        if (it == s.length()) {
            node->terminal = true;
            node->word_id = word_id;
            return;
        }

        if (node->letters[s[it] - 'a'] == nullptr) {
            node->letters[s[it] - 'a'] = new trie();
            // cout << node << " " << s[it] << " " << node->letters[s[it] - 'a'] << '\n';
        }
        add(node->letters[s[it] - 'a'], s, it + 1, word_id);
    }

    static vector <int> visit(trie* node, string const& s, size_t it = 0) {
        if (node == nullptr)
            return {};
        if (it == s.length()) {
            if (node->terminal)
                return vector<int>(1, node->word_id);
            else
                return {};
        }
        auto cur_res = visit(node->letters[s[it] - 'a'], s, it + 1);
        if (node->terminal)
            cur_res.push_back(node->word_id);
        return cur_res;
    }

    vector <trie*> letters;
    bool terminal;
    int word_id;
};

int main() {
    string s;
    int m;
    cin >> s >> m;
    trie* root = new trie();
    for (int i = 0; i < m; i++) {
        string t;
        cin >> t;
        trie::add(root, t, 0, i + 1);
    }
    set <int> answers;
    for (size_t i = 0; i < s.length(); i++) {
        string sub_str = s.substr(i, min(30, int(s.length() - i)));
        auto res = trie::visit(root, sub_str);
        for (int j : res)
            answers.insert(j);
    }
    for (int i = 1; i <= m; i++)
        if (answers.find(i) != answers.end())
            cout << "Yes\n";
        else
            cout << "No\n";
}
