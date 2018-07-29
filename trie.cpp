#include <bits/stdc++.h>

using namespace std;

struct trie_tree {
    int finish, pass;
    trie_tree *child[2];
};

typedef trie_tree *trie;
trie root;

trie new_node() {
    trie p = new trie_tree;
    p->pass = p->finish = 0;
    p->child[0] = p->child[1] = NULL;
    return p;
}

void insert(string x) {
    trie p = root;
    for (int i = 0; i < x.size(); i++) {
        p->pass++;
        if (p->child[x[i] - 48] == NULL)
            p->child[x[i] - 48] = new_node();
        p = p->child[x[i] - 48];
    }
    p->finish++;
}

int search(string x) {
    int res = 0;
    trie p = root;
    for (int i = 0; i < x.size(); i++) {
        if (p->child[x[i] - 48] == NULL) return res;
        p = p->child[x[i] - 48];
        res += p->finish;
    }
    return res + p->pass;
}

int main() {
    //freopen("in.txt", "r", stdin);
    root = new_node();
    int n, m;
    scanf("%d %d\n", &m, &n);
    for (int i = 1; i <= m; i++) {
        int L;
        string str = "";
        scanf("%d ", &L);
        for (int j = 1; j <= L; j++) {
            char c;
            scanf("%c ", &c);
            str += c;
        }
        insert(str);
    }

    for (int i = 1; i <= n; i++) {
        int L;
        string str = "";
        scanf("%d ", &L);
        for (int j = 1; j <= L; j++) {
            char c;
            scanf("%c ", &c);
            str += c;
        }
        printf("%d\n", search(str));
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

int a[1001];
int b[1001][33];
int n, n_node;
int tree[10000001][2], dd[10000001];

int getbit(int bit, int vt) {
    return (bit >> vt) & 1;
}

int onbit(int bit, int vt) {
    return bit | (1 << vt);
}

int get(int x) {
    int node = 0, res = 0;
    for (int j = 30; j >= 0; j--) {
        int b = getbit(x, j);
        if (tree[node][1-b] != 0 && dd[tree[node][1-b]] > 0) {
            res = onbit(res, j);
            node = tree[node][1-b];
        } else node = tree[node][b];
    }
    return res;
}

void insert(int x, int gt) {
    int node = 0;
    for (int j = 30; j >= 0; j--) {
        int b = getbit(x, j);
        if (tree[node][b] != 0) {
            node = tree[node][b];
            dd[node] += gt;
        } else {
            node = tree[node][b] = ++n_node;
            dd[node] += gt;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif // ONLINE_JUDGE

    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans = max(ans, a[i]);
        insert(a[i], 1);
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            insert(a[i] ^ a[j], 1);
            ans = max(ans, a[i] ^ a[j]);
        }

    for (int i = 1; i <= n; i++)
        ans = max(ans, get(a[i]));

    cout << ans;
}
