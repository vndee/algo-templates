#include <bits/stdc++.h>

using namespace std;

const int MaxN = (int)(1e3 + 3);

int n, q, a[MaxN][MaxN], ansMax, ansMin;
int stMax[4 * MaxN * MaxN], stMin[4 * MaxN * MaxN];

inline void Build(int k, int a1, int b1, int a2, int b2) {
   if (a1 > a2 || b1 > b2) return;
   if (a1 == a2 && b1 == b2) {
      stMax[k] = stMin[k] = a[a1][b1];
      return;
   }
   int midx = (a1 + a2) >> 1;
   int midy = (b1 + b2) >> 1;
   Build(4 * k - 2, a1, b1, midx, midy);
   Build(4 * k - 1, midx + 1, b1, a2, midy);
   Build(4 * k + 0, a1, midy + 1, midx, b2);
   Build(4 * k + 1, midx + 1, midy + 1, a2, b2);
   stMax[k] = max(stMax[4 * k - 2], max(stMax[4 * k - 1], max(stMax[4 * k + 0], stMax[4 * k + 1])));
   stMin[k] = min(stMin[4 * k - 2], min(stMin[4 * k - 1], min(stMin[4 * k + 0], stMin[4 * k + 1])));
}
inline void Update(int k, int a1, int b1, int a2, int b2, int x, int y, int val) {
   if (a1 > a2 || b1 > b2) return;
   if (x > a2 || y > b2 || x < a1 || y < b1) return;
   if (x == a1 && y == b1 && x == a2 & y == b2) {
      stMax[k] = stMin[k] = val;
      return;
   }
   int midx = (a1 + a2) >> 1;
   int midy = (b1 + b2) >> 1;
   Update(4 * k - 2, a1, b1, midx, midy, x, y, val);
   Update(4 * k - 1, midx + 1, b1, a2, midy, x, y, val);
   Update(4 * k + 0, a1, midy + 1, midx, b2, x, y, val);
   Update(4 * k + 1, midx + 1, midy + 1, a2, b2, x, y, val);
   stMax[k] = max(stMax[4 * k - 2], max(stMax[4 * k - 1], max(stMax[4 * k + 0], stMax[4 * k + 1])));
   stMin[k] = min(stMin[4 * k - 2], min(stMin[4 * k - 1], min(stMin[4 * k + 0], stMin[4 * k + 1])));
}
inline void Query(int k, int a1, int b1, int a2, int b2, int x1, int y1, int x2, int y2) {
   if (x1 > a2 || y1 > b2 || x2 < a1 || y2 < b1 || a1 > a2 || b1 > b2) return;
   if (x1 <= a1 && y1 <= b1 && a2 <= x2 && b2 <= y2) {
      ansMax = max(ansMax, stMax[k]);
      ansMin = min(ansMin, stMin[k]);
      return;
   }
   int midx = (a1 + a2) >> 1;
   int midy = (b1 + b2) >> 1;
   Query(4 * k - 2, a1, b1, midx, midy, x1, y1, x2, y2);
   Query(4 * k - 1, midx + 1, b1, a2, midy, x1, y1, x2, y2);
   Query(4 * k + 0, a1, midy + 1, midx, b2, x1, y1, x2, y2);
   Query(4 * k + 1, midx + 1, midy + 1, a2, b2, x1, y1, x2, y2);
}

int main() {
   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   cin >> n;
   for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= n; ++j)
         cin >> a[i][j];
   for(int i = 1; i <= 4 * n * n; ++i) {
      stMax[i] = -2e9;
      stMin[i] = 2e9;
   }
   Build(1, 1, 1, n, n);
   cin >> q;
   while(q--) {
      char c; cin >> c;
      int u, v; cin >> u >> v;
      if(c == 'c') {
         int w; cin >> w;
         Update(1, 1, 1, n, n, u, v, w);
      } else if(c == 'q') {
         int x, y; cin >> x >> y; ansMax = -2e9; ansMin = 2e9;
         Query(1, 1, 1, n, n, u, v, x, y);
         cout << ansMax << " " << ansMin << endl;
      }
   }
   return 0;
}
