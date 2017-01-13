#include <iostream>
#include <vector>
#include <set>
#include <utility>
using namespace std;

struct node {
    int center;
    int low;
    int up;
    node * left;
    node * right;
    int mini;
    int maxi;
    bool empty;

    node(int low, int up) {
        //printf("C: %d %d\n", low, up);
        center = (low + up)/2;
        this->low = low;
        this->up = up;
        empty = true;
        left = NULL;
        right = NULL;
    }
    ~node() {
        if (left != NULL) delete left;
        if (right != NULL) delete right;
    }
    void insert(int l, int u) {
        //printf("I: %d %d %d %d: %d\n", low, l, u, up, center);
        if (l <= center && center <= u) {
            if (empty) {
                empty = false;
                mini = l;
                maxi = u;
            } else {
                mini = min(mini, l);
                maxi = max(maxi, u);
            }
        } else if (u < center) {
            if (left == NULL) left = new node(low, center);
            left->insert(l, u);
        } else /*if (l > center)*/ {
            if (right == NULL) right = new node(center, up);
            right->insert(l, u);
        }
    }
    bool intersection(int p) {
        //printf("Q: %d %d: %d\n", low, up, p);
        //if (p > up || p < low) return false;
        if (p == center) return !empty;
        else if (p < center) {
            return (!empty && mini <= p) || (left != NULL && left->intersection(p));
        } else /*if (p > center)*/ {
            return (!empty && maxi >= p) || (right != NULL && right->intersection(p));
        }
    }
};

struct intervaltree {
	node * root;
	intervaltree(int low, int up) { root = new node(low, up); }
	~intervaltree() { delete root; }
    void insert(int l, int u) { root->insert(l, u); }
    bool intersection(int p) { return root->intersection(p); }
};

int main() {
    int low = -100, up = 100;
    intervaltree t(low, up);
    int n, q;
    cin >> n >> q;
    while (n--) {
        int l, u;
        cin >> l >> u;
        t.insert(l, u);
    }
    while (q--) {
        int p;
        cin >> p;
        printf("%d\n", t.intersection(p));
    }
    return 0;
}
