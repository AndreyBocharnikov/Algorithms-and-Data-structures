#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct node {
    node *l, *r;
    int key;
    int priority;
    int index;
    int pr_s;
    int lev_s;
    int pred;

    node(int new_key, int new_priority, int ind) {
        key = new_key;
        priority = new_priority;
        index = ind;
        l = nullptr;
        r = nullptr;
        pr_s = 0;
        lev_s = 0;
        pred = 0;
    }
};

bool cmp(node *a, node *b) {
    if (a->key >= b->key)
        return 1;
    else
        return 0;
}

bool cmp1(node *a, node *b) {
    if (a->index >= b->index)
        return 0;
    else
        return 1;
}

int main() {
    int n, k, p;
    cin >> n;
    vector<node *> nodes;
    stack<node *> st;
    node *last = nullptr;
    for (int i = 0; i < n; i++) {
        cin >> k >> p;
        node *v = new node(k, p, i + 1);
        nodes.push_back(v);
    }
    sort(nodes.begin(), nodes.end(), cmp);
    for (int i = 0; i < int(nodes.size()); i++) {
        while (!st.empty()) {
            if (st.top()->priority < nodes[i]->priority)
                break;
            last = st.top();
            st.pop();
        }
        nodes[i]->l = last;
        if (last != nullptr) {
            nodes[i]->pr_s = last->index;
            nodes[i]->l->pred = nodes[i]->index;
        }
        if (!st.empty()) {
            st.top()->r = nodes[i];
            nodes[i]->pred = st.top()->index;
            st.top()->lev_s = nodes[i]->index;
        }
        st.push(nodes[i]);
        last = nullptr;
    }
    sort(nodes.begin(), nodes.end(), cmp1);
    cout << "YES" << '\n';
    for (int i = 0; i < n; i++)
        cout << nodes[i]->pred << " " << nodes[i]->lev_s << " " << nodes[i]->pr_s << '\n';
}
