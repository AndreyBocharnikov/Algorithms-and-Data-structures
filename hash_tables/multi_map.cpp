#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

#define ll long long

using std::vector;
using std::string;
using std::list;
using std::pair;
// using std::cout;
// using std::cin;
using std::endl;

std::ifstream cin("multimap.in");
std::ofstream cout("multimap.out");

struct Set {
    explicit Set() : size(5), cur_size(0) {
        set.resize(size);
    }

    explicit Set(size_t sz) : cur_size(0) {
        size = sz;
        set.resize(size);
    }

    void insert(string const &str) {
        size_t cur_hesh = hesh(str);
        if (find(set[cur_hesh], str))
            return;
        cur_size++;
        set[cur_hesh].push_back(str);
        if (cur_size >= 10 * size)
            resize();
    }

    bool find(list<string> const &cur, string const &fnd) {
        for (string it : cur) {
            if (it == fnd)
                return true;
        }
        return false;
    }

    bool find(string const &str) {
        size_t cur_hesh = hesh(str);
        return find(set[cur_hesh], str);
    }

    void dlt(string const &str) {
        size_t cur_hesh = hesh(str);
        if (!find(set[cur_hesh], str))
            return;
        cur_size--;
        for (auto it = set[cur_hesh].begin(); it != set[cur_hesh].end(); it++) {
            if (*it == str) {
                set[cur_hesh].erase(it);
                break;
            }
        }
    }

    void resize() {
        Set new_set(size * 2);
        for (size_t i = 0; i < size; i++) {
            for (const string &it : set[i]) {
                // std::cout << i << " " << it << std::endl;
                new_set.insert(it);
            }
        }
        swap(new_set);
        // new_set.set.clear();
    }

    void swap(Set& old) {
        std::swap(set, old.set);
        std::swap(size, old.size);
    }

    size_t get_size() {
        return cur_size;
    }

    void get_all() {
        for (size_t i = 0; i < size; i++)
            for (string it : set[i])
                cout << it << " ";
    }

 private:
    size_t hesh(std::string const &str) {
        ll res = 0;
        for (char i : str) {
            res = (p * res + (i - 'A' + 1)) % mod;
        }
        return res % size;
    }
    size_t size, cur_size;
    int p = 71, mod = static_cast<int>(1e9 + 207);
    vector <list<string> > set;
};

struct MultiMap {
    explicit MultiMap() : size_(1000000), cur_size(0) {
        map.resize(size_);
    }

    explicit MultiMap(size_t sz) : cur_size(0) {
        size_ = sz;
        map.resize(size_);
    }

    void insert(string const &key, string const &val) {
        size_t cur_hesh = hesh(key);
        bool found = false;
        for (auto &it : map[cur_hesh]) {
            if (it.first == key) {
                found = true;
                if (find(it.second, val))
                    break;
                it.second.insert(val);
            }
        }
        if (!found) {
            Set tmp;
            tmp.insert(val);
            map[cur_hesh].push_back({key, tmp});
        }
    }

    bool find(Set &cur, const string &val) {
        return cur.find(val);
    }

    void deleteAll(string const &key) {
        size_t cur_hesh = hesh(key);
        for (auto it = map[cur_hesh].begin(); it != map[cur_hesh].end(); it++) {
            if (it->first == key) {
                map[cur_hesh].erase(it);
                break;
            }
        }
    }

    void get(string const &key) {
        size_t cur_hesh = hesh(key);
        bool found = false;
        for (auto &it : map[cur_hesh]) {
            if (it.first == key) {
                found = true;
                cout << it.second.get_size() << " ";
                it.second.get_all();
            }
        }
        if (!found)
            cout << 0 << '\n';
        else
            cout << '\n';
    }

    void dlt(string const &key, string const &val) {
        size_t cur_hesh = hesh(key);
        for (auto &it : map[cur_hesh]) {
            if (it.first == key) {
                it.second.dlt(val);
                break;
            }
        }
    }

 private:
    size_t hesh(std::string const &str) {
        ll res = 0;
        for (char i : str) {
            res = (p * res + (i - 'A' + 1)) % mod;
        }
        return res % size_;
    }

    vector<list<pair<string, Set > > > map;
    size_t size_, cur_size;
    int p = 71, mod = static_cast<int>(1e9 + 207);
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, key, val;
    MultiMap mm;
    while (cin >> s) {
        if (s == "put") {
            cin >> key >> val;
            mm.insert(key, val);
        }
        if (s == "get") {
            cin >> key;
            mm.get(key);
        }
        if (s == "delete") {
            cin >> key >> val;
            mm.dlt(key, val);
        }
        if (s == "deleteall") {
            cin >> key;
            mm.deleteAll(key);
        }
    }
    return 0;
}


