#include <iostream>
#include <vector>
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
        int sum = 0;
        for (; b; b -= LSOne(b)) sum += ft[b];
        return sum;
    }

    int rsq(int a, int b) {
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1));
    }

    int sicf(int frec) { // smallest index with a given cumulative frequency (only positive values)
        int k = 1, prev = 0;
        for (; k < (int)ft.size() && ft[k] < frec; k += LSOne(k)) prev = k;
        if (k >= (int)ft.size()) k = (int)ft.size() - 1;
        int max = rsq(k);
        if (frec <= max) {
            int i = 0;
            while (i < 10) {
                if (prev == k || prev == k - 1) return k;
                //printf("T %d %d: %d %d\n", prev, k, rsq(prev), rsq(k));
                k--;
                int diff = rsq(k) - frec, limit1 = prev + 1, limit2 = k + 1;
                prev = 0;
                //if (diff >= 0) return k + 1;
                for (;k >= limit1 && diff >= 0; k -= LSOne(k)) diff -= ft[k], prev = k;//, printf("L1 %d\n", k);
                if (diff >= 0) return limit1;
                limit1 = prev = k;
                //printf("P1 %d %d\n", k, diff);
                if (limit1 == limit2) return limit1;
                //limit2--;
                diff = -diff;
                k++;
                for (;k < limit2 && ft[k] < diff; k += LSOne(k)) prev = k; //, printf("L2 %d %d\n", k, ft[k]);
                //printf("P2 %d %d\n", k, prev);
                if (k < limit2) return k;
                //if (ft[k] >= diff) return limit1 + 1;
                i++;
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
    int f[] = { 2,4,5,5,6,6,6,7,7,8,9 };
    Fenwick fen(10);
    for (int i = 0; i < 11; i++) fen.insertDiff(f[i], 1);
    printf("%d\n", fen.rsq(1, 1));
    printf("%d\n", fen.rsq(1, 2));
    printf("%d\n", fen.rsq(1, 6));
    printf("%d\n", fen.rsq(1, 10));
    printf("%d\n", fen.rsq(3, 6));
    printf("---------\n");
    printf("0 %d\n", fen.sicf(0));
    printf("1 %d\n", fen.sicf(1));
    printf("2 %d\n", fen.sicf(2));
    printf("3 %d\n", fen.sicf(3));
    printf("4 %d\n", fen.sicf(4));
    printf("5 %d\n", fen.sicf(5));
    printf("6 %d\n", fen.sicf(6));
    printf("7 %d\n", fen.sicf(7));
    printf("8 %d\n", fen.sicf(8));
    printf("9 %d\n", fen.sicf(9));
    printf("10 %d\n", fen.sicf(10));
    printf("11 %d\n", fen.sicf(11));
    printf("12 %d\n", fen.sicf(12));
    return 0;
}
