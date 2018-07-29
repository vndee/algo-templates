#include <bits/stdc++.h>

using namespace std;

const int N = 100001;
const int inf = 0x3f3f3f;

class Splay_Tree {
public:
    struct Node {
        Node * P, * L, * R;
        int value, len, sum, Min;
    };
    Node * nil, * root;
public:
    void init_tree() {
        nil = new Node();
        nil->L = nil->R = nil->P = nil;
        nil->value = nil->len = nil->sum = 0;
        nil->Min = inf;
        root = nil;
    }
    void update(Node * x) {
        x->len = x->L->len + x->R -> len + 1;
        x->sum = x->L->sum + x->R->sum + x->value;
        x->Min = min(x->value, min(x->L->Min, x->R->Min));
    }
    void SetL(Node * x, Node * y) { y->P = x;   x->L = y; }
    void SetR(Node * x, Node * y) { y->P = x;   x->R = y; }
    Node * BuildTree(int a[], int L, int R) {
        Node * x = new Node();
        if (L == R) {
            x->value = x->Min = a[L];
            x->L = x->R = x->P = nil;
            return x;
        }
        int mid = (L + R) >> 1;
        x->value = x->Min = a[mid];
        x->P = nil;
        SetL(x, BuildTree(a, L, mid));
        SetR(x, BuildTree(a, mid + 1, R));
        update(x);
        return x;
    }
    Node * NodeAt(Node * x, int i) {
        while (true) {
            int ord = x->L->len + 1;
            if (ord == i) break;
            if (i < ord) x = x->L;
            else i -= ord, x = x->R;
        }
        return x;
    }
    void UpTree(Node * x) {
        Node * y, * z;
        y = x->P;
        z = y->P;
        if (x == y->L) {
            SetL(y, x->R);
            SetR(x, y);
        } else {
            SetR(y, x->L);
            SetL(x, y);
        }
        if (z->L == y) SetL(z, x); else SetR(z, x);
        update(y);  update(x);
    }
    void Splay(Node * x) {
        Node * y, * z;
        while (true) {
            y = x->P;
            if (y == nil) break;
            z = y->P;
            if (z != nil)
                if ((y == z->L && x == y->L) || (y == z->R && x == y->R))
                    UpTree(y);
                else UpTree(x);
            UpTree(x);
        }
    }
    void Split(Node * T, int i, Node * &T1, Node * &T2) {
        if (i == 0) {
            T1 = nil;
            T2 = T;
        } else {
            T1 = NodeAt(T, i);
            Splay(T1);
            T2 = T1->R;
            T1->R = nil;
            T2->P = nil;
            update(T1);
        }
    }
    Node * Join(Node * T1, Node * T2) {
        if (T1 == nil) return T2;
        while (T1->R != nil) T1 = T1->R;
        Splay(T1);
        SetR(T1, T2);
        update(T1);
        return T1;
    }
    void Insert(int i, int v) {
        if (i > root->len) i = root->len + 1;
        Node * T1, * T2;
        Split(root, i - 1, T1, T2);
        root = new Node();
        root->value = v;
        root->P = nil;
        SetL(root, T1);
        SetR(root, T2);
        update(root);
    }
    void Delete(int i) {
        Node * x, * T1, * T2;
        x = NodeAt(root, i);
        Splay(x);
        T1 = x->L;  T1->P = nil;
        T2 = x->R;  T2->P = nil;
        free(x);
        root = Join(T1, T2);
    }
    void Update(int i, int v) {
        root = NodeAt(root, i);
        Splay(root);
        root->value = v;
        update(root);
    }
    int Query(int i, int j) {
        Node * T1, * T2, * T3;
        Split(root, j, T2, T3);
        Split(T2, i - 1, T1, T2);
        int res = T2->sum;
        return root = Join(Join(T1, T2), T3), res;
    }
    int Query_Min(int i, int j) {
        Node * T1, * T2, * T3;
        Split(root, j, T2, T3);
        Split(T2, i - 1, T1, T2);
        int res = T2->Min;
        return root = Join(Join(T1, T2), T3), res;
    }
} bst_splay;

void Solve() {
    int k;  cin >> k;
    for (int i, v, j; k; k--) {
        char c; cin >> c;
        if (c == 'I') {
            cin >> i >> v;
            bst_splay.Insert(i, v);
        }
        if (c == 'D') {
            cin >> i;
            bst_splay.Delete(i);
        }
        if (c == 'U') {
            cin >> i >> v;
            bst_splay.Update(i, v);
        }
        if (c == 'Q') {
            cin >> i >> j;
            cout << bst_splay.Query(i, j) << endl;
        }
    }
}

int a[N], n, m;

int main() {
    ios_base::sync_with_stdio(0);   cin.tie(NULL);
    //freopen("in.txt", "r", stdin);
    bst_splay.init_tree();
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    bst_splay.root = bst_splay.BuildTree(a, 1, n);
    for (int i = 1; i <= m; i++) {
        int l, r;   cin >> l >> r;
        cout << bst_splay.Query_Min(l, r) << endl;
    }
    return 0;
}