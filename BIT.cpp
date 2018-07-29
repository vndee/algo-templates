#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

typedef long long ll;
const int maxN = 1001;

ll A[maxN][maxN];
int N, Q;

class Frenwick_Tree_1D {
private:
    ll bit[maxN];
public:
    void Update(int x, int val) {
        for (; x <= N; x += x & (-x)) bit[x] += val;
    }
    ll Sum(int x) {
        ll ans = 0;
        for (; x; x -= x & (-x)) ans += bit[x];
        return ans;
    }
    ll getSum(int u, int v) {
        return Sum(v) - Sum(u-1);
    }

} BIT_1D;

class Frenwick_Tree_2D {
private:
    ll bit[maxN][maxN];
public:
    void Update(int x, int y, int val) {
        for (int i = x; i <= N; i += i & (-i))
            for (int j = y; j <= N; j += j & (-j))
                bit[i][j] += val;
    }
    ll Sum(int x, int y) {
        ll ans = 0;
        for (int i = x; i; i -= i & (-i))
            for (int j = y; j; j -= j & (-j))
                ans += bit[i][j];
        return ans;
    }
    ll getSum(int x, int y, int u, int v) {
        return Sum(u, v) - Sum(u, y-1) - Sum(x-1, v) + Sum(x-1, y-1);
    }
} BIT_2D;

int main() {
    #ifndef ONLINE_JUDGE
        assert(freopen("in.txt", "r", stdin));
        assert(freopen("out.txt", "w", stdout));
    #endif // ONLINE_JUDGE

    /*
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) BIT_1D.Update(i, A[i]);

    while (Q--) {
        int c, u, v;
        cin >> c >> u >> v;
        if (!c) BIT_1D.Update(u, v);
        else cout << BIT_1D.getSum(u, v) << endl;
    }
    */
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) cin >> A[i][j];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) BIT_2D.Update(i, j, A[i][j]);

    while (Q--) {
        int c, u, v, k, l;
        cin >> c >> u >> v >> k >> l;
        if (!c) BIT_2D.Update(u, v, k);
        else cout << BIT_2D.getSum(u, v, k, l) << endl;
    }

    return 0;
}
