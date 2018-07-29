#include <bits/stdc++.h>

#define _LOCAL_

#ifdef _LOCAL_
  #define task "DBG"
#else
  #define task ""
#endif // _LOCAL_

using namespace std;

namespace HashSuffixArray {
  typedef unsigned long long hash;
  const hash BASE = 137;
  const int MAXN = 100001;

  int N;
  string S;
  int sa[MAXN];
  hash h[MAXN], hPow[MAXN];

  #define getHash(lo, size) (h[lo] - h[(lo) + (size)] * hPow[size])

  inline bool sufCmp(int i, int j) {
    int lo = 1, hi = min(N - i, N - j);
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      if (getHash(i, mid) == getHash(j, mid))
        lo = mid + 1;
      else
        hi = mid - 1;
      }
      return S[i + hi] < S[j + hi];
  }

  void buildSA (string s) {
    S = s;
    N = S.length();
    hPow[0] = 1;
    for (int i = 1; i <= N; ++i)
      hPow[i] = hPow[i - 1] * BASE;
    h[N] = 0;
    for (int i = N - 1; i >= 0; --i)
      h[i] = h[i + 1] * BASE + S[i], sa[i] = i;

    stable_sort(sa, sa + N, sufCmp);
  }
}

namespace SuffixArray {
  const int MAXN = 100001;
  string S;
  int n, gap;
  int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

  bool sufCmp(int i, int j) {
    if (pos[i] != pos[j])
      return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < n && j < n) ? pos[i] < pos[j] : i > j;
  }

  void buildSA(string ss) {
    S = ss;
    n = S.size();
    for (int i = 0; i < n; i++) sa[i] = i, pos[i] = S[i];

    for (gap = 2; ; gap *= 2) {
      sort(sa, sa + n, sufCmp);
      for (int i = 0; i < n - 1; i++)
        tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
      for (int i = 0; i < n; i++)
        pos[sa[i]] = tmp[i];
      if (tmp[n - 1] == n - 1) break;
    }
  }

  void buildLCP() {
    for (int i = 0, k = 0; i < n; i++)
      if (pos[i] != n - 1) {
        for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
          k++;
        lcp[pos[i]] = k;
        if (k) k--;
      }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  assert(freopen(task".INP", "r", stdin));
  assert(freopen(task".OUT", "w", stdout));
#endif // ONLINE_JUDGE

  ios_base::sync_with_stdio(0); cin.tie(NULL);

  SuffixArray::buildSA("aa");
  SuffixArray::buildLCP();

  for (int i = 0; i < 6; i++) cout << SuffixArray::sa[i] << " ";
  cout << endl;
  for (int i = 0; i < 6; i++) cout << SuffixArray::lcp[i] << " ";

  return 0;
}
