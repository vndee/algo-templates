#include <iostream>
#include <cstdio>

using namespace std;

long long cat[100];

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    cat[0] = cat[1] = 1;
    for (int i = 2; i <= 33; i++) cat[i] = cat[i-1]*(4*i - 6)/i;
    for (int i = 0; i <= 33; i++) cout << cat[i] << " ";

    return 0;
}
