#include <bits/stdc++.h>
 
using namespace std;
 
map <int, int> did;
int mem[20][200], isPrime[200];
 
int dp(int dig, int sum) {
  int &ret = mem[dig][sum];
  if (ret != -1) return ret;
  if (dig == 0) return ret = !isPrime[sum];
 
  ret = 0;
  for (int i = 0; i <= 9; i++)
    ret += dp(dig - 1, sum + i);
 
  return ret;
}
 
int Calc(int X) {
  if (did.count(X)) return did[X];
 
  char digits[20];
  sprintf(digits, "%d", X);
  int len = strlen(digits);
 
  int ret = 0, s = 0;
  for (int i = 0; i < strlen(digits); i++) {
    len--;  int d = digits[i] - '0';
    for (int j = 0; j < d; j++)
      ret += dp(len, s + j);
    s += d;
  }
 
  return did[X] = ret;
}
 
int main() {
  //freopen("in.txt", "r", stdin);
 
  isPrime[0] = isPrime[1] = 1;
  for (int i = 2; i < 200; i++)
    if (!isPrime[i])
      for (int j = i * 2; j < 200; j += i)
        isPrime[j] = 1;
 
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 200; j++)
      mem[i][j] = -1;
 
  int T;  scanf("%d", &T);
  while (T--) {
    int L, R; scanf("%d %d\n", &L, &R);
    printf("%d\n", Calc(R + 1) - Calc(L));
  }
  
  return 0;
}

#include <bits/stdc++.h>
 
using namespace std;
 
map <int, int> did;
int mem[101][101][101], isPrime[201];
 
int dp(int dig, int odd, int eve) {
  int &ret = mem[dig][odd][eve];
  if (ret != -1) return ret;
  if (dig == 0) return ret = eve - odd == 1;
 
  ret = 0;
  for (int i = 0; i <= 9; i++)
    if (dig & 1) ret += dp(dig - 1, odd + i, eve);
    else ret += dp(dig - 1, odd, eve + i);
 
  return ret;
}
 
int Calc(int X) {
  if (did.count(X)) return did[X];
 
  char digits[50];
  sprintf(digits, "%d", X);
  int len = strlen(digits);
 
  int ret = 0, odd = 0, eve = 0;
  for (int i = 0; i < strlen(digits); i++) {
    len--;
    int d = digits[i] - '0';
    for (int j = 0; j < d; j++)
      if ((len + 1) & 1) ret += dp(len, odd + j, eve);
      else ret += dp(len, odd, eve + j);
 
    if ((len + 1) & 1) odd += d; else eve += d;
  }
 
  return did[X] = ret;
 
}
 
int main() {
  //freopen("in.txt", "r", stdin);
 
  isPrime[0] = isPrime[1] = 1;
  for (int i = 2; i < 200; i++)
    if (!isPrime[i])
      for (int j = 2 * i; j < 200; j += i)
        isPrime[j] = 1;
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      for (int k = 0; k < 100; k++)
        mem[i][j][k] = -1;
 
  int T;  scanf("%d", &T);
  while (T--) {
    int a, b; scanf("%d %d\n", &a, &b);
    printf("%d\n", Calc(b + 1) - Calc(a));
  }
 
  return 0;
}

#include <bits/stdc++.h>
 
using namespace std;
 
map <int, int> did;
int mem[101][101][101], isPrime[201];
 
int dp(int dig, int odd, int eve) {
  int &ret = mem[dig][odd][eve];
  if (ret != -1) return ret;
  if (dig == 0) return ret = eve - odd < 0 ? 0 : 1 ^ isPrime[eve - odd];
 
  ret = 0;
  for (int i = 0; i <= 9; i++)
    if (dig & 1) ret += dp(dig - 1, odd + i, eve);
    else ret += dp(dig - 1, odd, eve + i);
 
  return ret;
}
 
int Calc(int X) {
  if (did.count(X)) return did[X];
 
  char digits[50];
  sprintf(digits, "%d", X);
  int len = strlen(digits);
 
  int ret = 0, odd = 0, eve = 0;
  for (int i = 0; i < strlen(digits); i++) {
    len--;
    int d = digits[i] - '0';
    for (int j = 0; j < d; j++)
      if ((len + 1) & 1) ret += dp(len, odd + j, eve);
      else ret += dp(len, odd, eve + j);
 
    if ((len + 1) & 1) odd += d; else eve += d;
  }
 
  return did[X] = ret;
 
}
 
int main() {
  //freopen("in.txt", "r", stdin);
 
  isPrime[0] = isPrime[1] = 1;
  for (int i = 2; i < 200; i++)
    if (!isPrime[i])
      for (int j = 2 * i; j < 200; j += i)
        isPrime[j] = 1;
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++)
      for (int k = 0; k < 100; k++)
        mem[i][j][k] = -1;
 
  int T;  scanf("%d", &T);
  while (T--) {
    int a, b; scanf("%d %d\n", &a, &b);
    printf("%d\n", Calc(b + 1) - Calc(a));
  }
 
  return 0;
}

#include <bits/stdc++.h>

using namespace std;

long long memo[20][200][2000];
vector <int> digits;
map <long long, long long> did;
int GCD[200][2000];

long long dp(int i, int s, int t) {
  if (i == 0) return GCD[s][t];
  long long &res = memo[i][s][t];
  if (res != -1) return res;
  res = 0;
  for (int d = 0; d <= 9; d++)
    res += dp(i - 1, s + d, t + d*d);
  return res;
}

long long Calc(long long X) {
  long long &res = did[X];
  if (res != 0) return res;

  digits.clear();
  while (X > 0) { digits.push_back(X % 10); X /= 10; }

  long long pos = digits.size();
  int s = 0, t = 0;
  for (int i = (int) digits.size() - 1; i >= 0; i--) {
    pos--;
    int d = digits[i];
    for (int j = 0; j < d; j++)
      res += dp(pos, s + j, t + j*j);
    s += d; t += d*d;
  }
  return res;
}

int main() {

#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
#endif // ONLINE_JUDGE

  for (int i = 0; i < 200; i++)
    for (int j = 0; j < 2000; j++) {
      GCD[i][j] = ((int) __gcd(i, j) == 1) ? 1 : 0;
      for (int k = 0; k < 20; k++)
        memo[k][i][j] = -1;
    }

  int T;
  scanf("%d", &T);
  while (T--) {
    long long L, R;
    scanf("%lld %lld", &L, &R);
    printf("%lld\n", max(0LL, Calc(R + 1) - Calc(L)));
  }
}
 
         #include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lint;
//typedef unsigned long long ulint;

const int SIZ = 100000;
const int INF = (1<<29);

int caseno = 0, test, len;
int done[20][3];
lint mem[20][3], N, M;
char str[20];

lint call( int i, int isSmall ){
    int j = len - i - 1;
    if( i > j ) return isSmall != 2 ? 1 : 0;
    lint &ret = mem[i][isSmall];
    int &dn = done[i][isSmall];
    if( dn == test ) return ret;
    lint res = 0;
    if( isSmall == 1 ) res += 10 * call( i + 1, 1 );

    else if( isSmall == 0 ){
        int s = ( i > 0 || len == 1 ) ? 0 : 1;
        res += (str[i] - 48 - s) * call( i + 1, 1 );
        int k = str[i] - 48;
        if( k > str[j] - 48 ) res += call( i + 1, 2 );
        else res += call( i + 1, 0 );
    }
    else{
        int s = ( i > 0 || len == 1 ) ? 0 : 1;
        res += (str[i] - 48 - s ) * call( i + 1, 1 );
        int k = str[i] - 48;
        if( k >= str[j] - 48 ) res += call( i + 1, 2 );
        else res += call( i + 1, 0 );
    }
    dn = test;
    return ret = res;
}

lint f( lint x ){
    if( x < 0 ) return 0;
    char num[20];
    sprintf( num, "%lld", x );
    int i, length = strlen(num);
    lint res = 0;
    for( i = 1; i <= length; i++ ){
        str[i-1] = '9';
        str[i] = 0;
        if( i == length ) strcpy( str, num );
        len = i, test++;
        res += call( 0, 0 );
    }
    return res;
}

int main(){
    //freopen("a.in", "r", stdin);
    //freopen("a.ans", "w", stdout);
    int cases, i, j;
    scanf("%d", &cases);
    memset( done, -1, sizeof(done) );
    test = 0;
    while( cases-- ){
        scanf("%lld %lld", &N, &M);
        if( N > M ) swap( N, M );
        lint res = f( M ) - f( N - 1);
        printf("%lld\n", res);
    }
    return 0;
}
