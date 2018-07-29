#include <bits/stdc++.h>
 
#define _LOCAL_
 
#ifdef _LOCAL_
  #define task "DBG"
#else
  #define task ""
#endif // _LOCAL_
 
#define lc(x) x << 1
#define rc(x) x << 1 | 1
 
using namespace std;
 
typedef long long ll;
 
const int N = 200001;
 
struct line {
  ll a, b;
};
 
line it[4*N];
int n, m;
 
ll get(line d, ll x) {
  return d.a * x + d.b;
}
 
void update(int id, int l, int r, int u, int v, line val) {
  if (l > v || r < u) return;
 
  int mid = (l + r) >> 1;
  if (u <= l && r <= v) {
    ll l_id = get(it[id], l), r_id = get(it[id], r);
    ll l_val = get(val, l), r_val = get(val, r);
 
    if (l_id >= l_val && r_id >= r_val) return;
    if (l_id <= l_val && r_id <= r_val) {
      it[id] = val;
      return;
    }
 
    ll m_id = get(it[id], mid), m_val = get(val, mid);
 
    if (l_id >= l_val && m_id >= m_val) {
      update(rc(id), mid + 1, r, u, v, val);
      return;
    }
    if (l_id <= l_val && m_id <= m_val) {
      update(rc(id), mid + 1, r, u, v, it[id]);
      it[id] = val;
      return;
    }
 
    //m_id = get(it[id], mid + 1), m_val = get(val, mid + 1);
    if (m_id >= m_val && r_id >= r_val) {
      update(lc(id), l, mid, u, v, val);
      return;
    }
    if (m_id <= m_val && r_id <= r_val) {
      update(lc(id), l, mid, u, v, it[id]);
      it[id] = val;
      return;
    }
  }
 
  update(lc(id), l, mid, u, v, val);
  update(rc(id), mid + 1, r, u, v, val);
}
 
ll range_query(int id, int l, int r, int pos) {
  if (l > pos || r < pos) return 0LL;
  ll ret = get(it[id], pos);
  if (l == r) return ret;
 
  int mid = (l + r) >> 1;
  ret = max(ret, range_query(lc(id), l, mid, pos));
  ret = max(ret, range_query(rc(id), mid + 1, r, pos));
  return ret;
}
 
int main() {
#ifndef ONLINE_JUDGE
  assert(freopen(task".INP", "r", stdin));
  assert(freopen(task".OUT", "w", stdout));
#endif // ONLINE_JUDGE
 
  ios_base::sync_with_stdio(0); cin.tie(NULL);
 
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    ll s, e, v, d; cin >> s >> e >> v >> d;
    update(1, 1, n, s, e, {d, v - s*d});
  }
 
  for (int i = 1; i <= n; i++)
    cout << range_query(1, 1, n, i) << endl;
 
  return 0;
}