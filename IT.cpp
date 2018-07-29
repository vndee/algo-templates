#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxN = 100001;
const ll inf  = 2*1e9;
ll A[maxN], N, Q;

class Segment_Tree {
private:
    ll it_sum[4*maxN], it_max[4*maxN], it_min[4*maxN], lazy[4*maxN];
public:
    void par_update(int x) {
        it_sum[x] = it_sum[2*x] + it_sum[2*x+1];
        it_max[x] = max(it_max[2*x], it_max[2*x+1]);
        it_min[x] = min(it_min[2*x], it_min[2*x+1]);
    }
    void Build(int x, int L, int R) {
        if (L == R) {
            it_sum[x] = it_max[x] = it_min[x] = A[L];
        } else {
            int mid = (L + R) >> 1;
            Build(2*x, L, mid);
            Build(2*x+1, mid+1, R);
            par_update(x);
        }
    }
    void lazy_update(int x) {
        if (!lazy[x]) return;
        lazy[2*x] += lazy[x];
        it_max[2*x] += lazy[x];
        it_min[2*x] += lazy[x];
        it_sum[2*x] += lazy[x];
        lazy[2*x+1] += lazy[x];
        it_max[2*x+1] += lazy[x];
        it_min[2*x+1] += lazy[x];
        it_sum[2*x+1] += lazy[x];
        lazy[x] = 0;
    }
    void Update(int x, int L, int R, int u, int v, ll val) {
        if (L > v || R < u) return;
        if (L >= u && R <= v) {
            lazy[x] += val;
            it_max[x] += val;
            it_min[x] += val;
            it_sum[x] += val*(R - L + 1);
            return;
        }
        lazy_update(x);
        int mid = (L + R) >> 1;
        Update(2*x, L, mid, u, v, val);
        Update(2*x+1, mid+1, R, u, v, val);
        par_update(x);
    }
    ll getMax(int x, int L, int R, int u, int v) {
        if (L > v || R < u) return -inf;
        if (L >= u && R <= v) return it_max[x];
        lazy_update(x);
        int mid = (L + R) >> 1;
        ll left = getMax(2*x, L, mid, u, v);
        ll right = getMax(2*x+1, mid+1, R, u, v);
        return max(left, right);
    }
    ll getMin(int x, int L, int R, int u, int v) {
        if (L > v || R < u) return inf;
        if (L >= u && R <= v) return it_min[x];
        lazy_update(x);
        int mid = (L + R) >> 1;
        ll left = getMin(2*x, L, mid, u, v);
        ll right = getMin(2*x+1, mid+1, R, u, v);
        return min(left, right);
    }
    ll getSum(int x, int L, int R, int u, int v) {
        if (L > v || R < u) return 0;
        if (L >= u && R <= v) return it_sum[x];
        lazy_update(x);
        int mid = (L + R) >> 1;
        ll left = getSum(2*x, L, mid, u, v);
        ll right = getSum(2*x+1, mid+1, R, u, v);
        return left + right;
    }
} IT;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> A[i];
    IT.Build(1, 1, N);
    while (Q--) {
        int c, u, v;
        cin >> c >> u >> v;
        if (!c) IT.Update(1, 1, N, u, u, v);
        else cout << IT.getSum(1, 1, N, u, v) << endl;
    }

    return 0;
}
