#include <bits/stdc++.h>
 
//#define _LOCAL_
 
#ifdef _LOCAL_
  #define task "DBG"
#else
  #define task "COMP_STR"
#endif // _LOCAL_
 
#define X first
#define Y second
#define lc(x) x << 1
#define rc(x) x << 1 | 1
 
#define long unsigned long long
 
using namespace std;
 
typedef pair<int, long> hash_t;
 
const int N = 300005;
int n, m;
char b[N];
hash_t Hash[4*N];
long M[N];
 
hash_t operator + (hash_t a, hash_t b) {
  return hash_t(a.X + b.X, a.Y * M[b.X] + b.Y);
}
 
struct Segment_Tree {
  int ll, rr, id;
  Segment_Tree(int L, int X) {
    ll = L, id = X;
    rr = ll + Hash[id].X - 1;
  }
 
  Segment_Tree left() {
    return Segment_Tree(ll, id << 1);
  }
 
  Segment_Tree right() {
    return Segment_Tree(ll + Hash[id << 1].X, id << 1 | 1);
  }
 
  void Remove(int X) {
    if (ll > X || X > rr) return ;
    if (ll == rr) {
      Hash[id] = hash_t(0, 0);
      return ;
    }
 
    right().Remove(X), left().Remove(X);
    Hash[id] = Hash[id << 1] + Hash[id << 1 | 1];
  }
 
  hash_t Query(int L, int R) {
    if (ll > R || L > rr || L > R)
      return hash_t(0, 0);
    if (L <= ll && rr <= R)
      return Hash[id];
    return left().Query(L, R) + right().Query(L, R);
  }
 
  void build(int L, int R) {
    if (L == R) {
      Hash[id] = hash_t(1, b[ll]);
      return ;
    }
 
    int mid = (L + R) >> 1;
    left().build(L, mid);
    right().build(mid + 1, R);
    Hash[id] = Hash[id << 1] + Hash[id << 1 | 1];
  }
};
 
void solve() {
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    char c; int x, y, z;
    scanf(" %c%d", &c, &x);
    if (c == '-')
      Segment_Tree(1, 1).Remove(x);
    else {
      scanf("%d%d", &y, &z);
      hash_t H1 = Segment_Tree(1, 1).Query(x, x + z - 1);
      hash_t H2 = Segment_Tree(1, 1).Query(y, y + z - 1);
      puts(H1 == H2 ? "YES" : "NO");
    }
  }
}
 
int main() {
#ifndef ONLINE_JUDGE
  assert(freopen(task".INP", "r", stdin));
  assert(freopen(task".OUT", "w", stdout));
#endif // ONLINE_JUDGE
 
  M[0] = 1; M[1] = 2309;
  for (int i = 2; i < N; i++)
  M[i] = M[i-1] * M[1];
 
  scanf("%s", b + 1);
  n = strlen(b + 1);
  Segment_Tree(1, 1).build(1, n);
 
  solve();
 
  return 0;
}