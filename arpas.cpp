/*
  Given array a of n integers, and q queries,
  for each query print the maximum value in range [L, R].

  O((n + q) * akerman(n)) ~ O(n + q).
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;

int par[N], ans[N], n, a[N], l[N], q;
vector <int> Q[N];

int findset(int v) {
  return par[v] == -1 ? v : par[v] = findset(par[v]);
}

int main() {
  freopen("DBG.INP", "r", stdin);
  freopen("DBG.OUT", "w", stdout);

  ios_base::sync_with_stdio(0); cin.tie(NULL);
  memset(par, -1, sizeof par);

  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> q;
  for (int i = 0, r; i < q; i++) {
    cin >> l[i] >> r;
    l[i]--, r--;
    Q[r].push_back(i);
  }

  stack <int> st;
  for (int i = 0; i < n; i++) {
    while (st.size() && a[st.top()] <= a[i])
      par[st.top()] = i, st.pop();
    st.push(i);

    for (auto j : Q[i]) ans[j] = a[findset(l[j])];
  }

  for (int i = 0; i < q; i++) cout << ans[i] << "\n";
  return 0;
}
