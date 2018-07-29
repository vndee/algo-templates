#include <bits/stdc++.h>

#define task "main"

using namespace std;

// generating random integer from l to h
long long Rand(long long l, long long h) {
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

// generating random array
void gen_array(int _n, int _upper) {
    int n = rand() % _n + 1;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
        printf("%d ", rand() % _upper + 1);
}

// generating random matrix
void gen_mat(int _m, int _n, int _upper) {
    int n = rand() % _n + 1, m = rand() % _m + 1;
    printf("%d %d\n", m, n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) printf("%d ", rand() % _upper + 1);
        printf("\n");
    }
}

// generating character
void gen_char() {
    printf("%c\n", 'a' + rand() % 26);
}

// generating random string
void gen_string(int _n) {
    int n = rand() % _n + 1;
    for (int i = 1; i <= n; i++)
        printf("%c", 'a' + rand() % 26);
}

// generating random tree
void gen_tree(int _v) {
    int v = rand() % _v + 1;
    printf("%d\n", v);

    vector <int> used;  used.reserve(v);    used.push_back(1);
    for (int j = 2; j <= v; j++) {
        int u = used[rand() % used.size()];
        used.push_back(j);
        printf("%d %d\n", u, j);
    }
}

// generating random directed graph
void gen_graph_directed(int _n, int _m) {
    set < pair<int, int> > container;
    set < pair<int, int> >::iterator it;

    int n = rand() % _n + 1, m = rand() % _m + 1;
    while (m > n*(n-1)/2) m = rand() % _m + 1;

    printf("%d %d\n", n, m);
    for (int j = 1; j <= m; j++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        pair<int, int> p = make_pair(a, b);

        while (container.find(p) != container.end()) {
            a = rand() % n + 1;
            b = rand() % n + 1;
            p = make_pair(a, b);
        }
        container.insert(p);
    }

    for (it = container.begin(); it != container.end(); it++)
        printf("%d %d\n", it->first, it->second);
}

// generating random undirected graph
void gen_graph_undirected(int _n, int _m) {
    set < pair<int, int> > container;
    set < pair<int, int> >::iterator it;

    int n = rand() % _n + 1, m = rand() % _m + 1;
    while (m > n*(n-1)/2) m = rand() % _m + 1;

    printf("%d %d\n", n, m);
    for (int j = 1; j <= m; j++) {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        pair<int, int> p = make_pair(a, b);
        pair<int, int> rp = make_pair(b, a);

        while (container.find(p) != container.end()
               || container.find(rp) != container.end()) {
            a = rand() % n + 1;
            b = rand() % n + 1;
            p = make_pair(a, b);
            rp = make_pair(b, a);
        }
        container.insert(p);
    }

    for (it = container.begin(); it != container.end(); it++)
        printf("%d %d\n", it->first, it->second);
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen(task".inp", "r", stdin);
        freopen(task".out", "w", stdout);
    #endif // ONLINE_JUDGE

    srand(time(NULL));
    gen_graph_undirected(10, 10);

    return 0;
}
