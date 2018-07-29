#include <bits/stdc++.h>

#define task "main"

using namespace std;

int rmq[10000][30];

int main() {
    #ifndef ONLINE_JUDGE
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    #endif // ONLINE_JUDGE

    int n, q, a[10000];
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) rmq[i][0] = a[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            rmq[i][j] = max(rmq[i][j-1], rmq[i + (1 << (j-1))][j-1]);

    while (q--) {
        int u, v;   scanf("%d %d\n", &u, &v);
        int k = log2(v - u + 1);
        printf("%d\n", max(rmq[u][k], rmq[v - (1 << k) + 1][k]));
    }

    return 0;
}
