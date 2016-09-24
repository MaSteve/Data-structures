#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef vector<int> vi;

inline int LSOne(int i) {
    return (i & (-i));
}

struct Fenwick {
    vi ft, values;

    Fenwick(int n) {
        ft.assign(n + 1, 0);
        values.assign(n, 0);
    }

    int rsq(int b) {
        b++;
        int sum = 0;
        for (; b; b -= LSOne(b)) sum += ft[b];
        return sum;
    }

    int rsq(int a, int b) {
        return rsq(b) - (a == 0 ? 0 : rsq(a - 1));
    }

    int sicf(int frec) { // smallest index with a given cumulative frequency (only positive values)
        int k = 1, prev = 0;
        for (; k < (int)ft.size() && ft[k] < frec; k += LSOne(k)) prev = k;
        if (k >= (int)ft.size()) k = (int)ft.size() - 1;
        int max = rsq(k-1);
        if (frec <= max) {
            while (true) {
                if (prev == k || prev == k - 1) return k;
                k--;
                int diff = rsq(k - 1) - frec, limit1 = prev + 1, limit2 = k + 1;
                prev = 0;
                for (;k >= limit1 && diff >= 0; k -= LSOne(k)) diff -= ft[k], prev = k;
                if (diff >= 0) return limit1;
                limit1 = prev = k;
                if (limit1 == limit2) return limit1;
                diff = -diff;
                k++;
                for (;k < limit2 && ft[k] < diff; k += LSOne(k)) prev = k;
            }
        }
        return -1;
    }

    void insert(int pos, int val) {
        int diff = val - values[pos], k = pos + 1;
        values[pos] = val;
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += diff;
    }

    void insertDiff(int val, int diff) {
        insert(val - 1, values[val-1] + diff);
    }
};

int main() {
    int N = 200;
    srand(time(NULL));
    int f[N];
    int val = rand()%10 + 1;
    for (int i = 0; i < N; i++) f[i] = val, val += rand()%10;
    Fenwick fen(val + 3);
    for (int i = 0; i < N; i++) fen.insertDiff(f[i], 1);

    for (int i = 1; i < N + 4; i++) {
        printf("%d %d\n", i, fen.sicf(i));
        assert(i <= N? fen.sicf(i) == f[i - 1]: fen.sicf(i) == -1);
    }

    return 0;
}
