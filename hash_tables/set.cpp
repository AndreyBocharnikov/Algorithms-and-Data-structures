#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

struct Set {
    explicit Set() : size_(5), cur_size(0), a(rand() * rand() + 1), b(rand() * rand()) {
        set.resize(size_);
    }

    explicit Set(size_t sz) : cur_size(0), a(rand() * rand() + 1), b(rand() * rand()) {
        size_ = sz;
        set.resize(size_);
    }

    void insert(int val) {
        size_t cur_hesh = hesh(val);
        if (find(set[cur_hesh], val))
            return;
        cur_size++;
        set[cur_hesh].push_back(val);
        if (cur_size >= 10 * size_)
            resize();
    }

    bool find(std::list<int> const &cur, int const &fnd) {
        for (int it : cur) {
            if (it == fnd)
                return true;
        }
        return false;
    }

    bool find(int val) {
        size_t cur_hesh = hesh(val);
        return find(set[cur_hesh], val);
    }

    void dlt(int val) {
        size_t cur_hesh = hesh(val);
        if (!find(set[cur_hesh], val))
            return;
        cur_size--;
        for (auto it = set[cur_hesh].begin(); it != set[cur_hesh].end(); it++) {
            if (*it == val) {
                set[cur_hesh].erase(it);
                break;
            }
        }
    }

    void resize() {
        Set new_set(size_ * 10);
        for (size_t i = 0; i < size_; i++) {
            for (int it : set[i]) {
                // std::cout << i << " " << it << std::endl;
                new_set.insert(it);
            }
        }
        swap(new_set);
        // new_set.set.clear();
    }

    void swap(Set& old) {
        std::swap(set, old.set);
        std::swap(a, old.a);
        std::swap(b, old.b);
        std::swap(mod, old.mod);
        std::swap(size_, old.size_);
    }

 private:
    size_t hesh(int val) {
        return (a * val + b) % mod % size_;
    }

    std::vector<std::list<int> > set;
    size_t size_, cur_size;
    int a, b, mod = static_cast<int>(1e9 + 207);
};

int main() {
    std::ifstream cin("set.in");
    std::ofstream cout("set.out");
    std::string s;
    Set st;
    int val;
    while (cin >> s) {
        cin >> val;
        if (s == "insert")
            st.insert(val);
        if (s == "delete")
            st.dlt(val);
        if (s == "exists") {
            if (st.find(val)) {
                cout << "true" << std::endl;
            } else {
                cout << "false" << std::endl;
            }
        }
    }
    return 0;
}
