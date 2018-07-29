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