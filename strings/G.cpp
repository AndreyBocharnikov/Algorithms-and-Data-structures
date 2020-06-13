// Aho-Corasick algorithm
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

struct trie {
    trie() {
        terminal = false;
        visited = false;
        answer_computed = false;
        parent = nullptr;
        suf_link = nullptr;
    }

    void add(string const& s, size_t it, int word_id) {
        if (it == s.length()) {
            terminal = true;
            word_ids.push_back(word_id);
            return;
        }
        if (moves[s[it]] == nullptr) {
            moves[s[it]] = new trie();
            moves[s[it]]->parent = this;
        }
        moves[s[it]]->add(s, it + 1, word_id);
    }

    trie* proceed(char c) {
        return moves[c];
    }

    // should be called only by root
    void make_suf_ref_2() {
        queue<trie*> q;
        q.push(this);
        while (!q.empty()) {
            trie* current_parent = q.front();
            q.pop();
            for (auto pare : current_parent->moves) {
                char c = pare.first;
                trie* v = pare.second;
                trie* parent_link = current_parent->suf_link;
                // cout << current_parent << " " << c << " " << v << " " << parent_link << endl;
                while (parent_link != nullptr && parent_link->moves[c] == nullptr) {
                    parent_link = parent_link->suf_link;
                }
                // cout << parent_link << endl;
                if (parent_link == nullptr) {
                    v->suf_link = this;
                } else {
                    v->suf_link = parent_link->moves[c];
                }
                q.push(v);
            }
        }
    }

    void mark_visited(trie* root, vector <int> &answer) {
        visited = true;
        // cout << this << " " << suf_link << '\n';
        if (suf_link != root && suf_link->visited == false) {
            suf_link->mark_visited(root, answer);
        }
        // cout << this << " " << visited << " " << terminal << '\n';
        if (terminal && !answer_computed) {
            for (int word_id : word_ids)
                answer[word_id] = 1;
            answer_computed = true;
        }
    }

 private:
    void delete_(trie* node) {
        if (node == nullptr)
            return;
        for (auto it : node->moves) {
            delete_(it.second);
        }
        auto it = node->moves.begin();
        ++it;
        for (; it != node->moves.end(); ++it) {
            delete (*prev(it)).second;
        }
        // prev(end()) doesn't work :(
        delete (*prev(node->moves.end())).second;
    }


 public:
    ~trie() {
        for (auto it : moves) {
            delete_(it.second);
        }
    }

    unordered_map <char, trie*> moves;
    vector <int> word_ids;
    bool terminal, visited, answer_computed;
    trie *parent, *suf_link;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector <string> s(n);
    string text;
    for (int i = 0; i < n; i++)
        cin >> s[i];
    cin >> text;
    trie* root = new trie();
    for (int i = 0; i < n; i++)
        root->add(s[i], 0, i);
    root->make_suf_ref_2();  // root should not be in saved_q
    trie* current_state = root;
    vector <trie*> save_states;
    for (char c : text) {
        trie* next_state = current_state->proceed(c);
        // if current_state == root it means that string is empty
        while (next_state == nullptr && current_state != root) {
            current_state = current_state->suf_link;
            next_state = current_state->proceed(c);
        }

        if (next_state != nullptr) {
            next_state->visited = true;
            current_state = next_state;
            save_states.push_back(current_state);
        }
    }
    vector <int> answers(n);
    for (auto it = save_states.begin(); it != save_states.end(); ++it) {
        (*it)->mark_visited(root, answers);
    }
    for (int i = 0; i < n; i++) {
        if (answers[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    // delete root;
}
