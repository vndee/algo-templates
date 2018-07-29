#include <iostream>
#include <cstdio>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ii extended_gcd(ll a, ll b) {
    ii qr, st;
    if (!b) return ii(1, 0);
    else {
        qr = ii(a/b, a%b);
        st = extended_gcd(b, qr.y);
        return ii(st.y, st.x-qr.x*st.y);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    ll a, b, c;
    cin >> a >> b >> c;
    ll g = __gcd(a, b);
    ii st = extended_gcd(a, b);
    cout << c/g*st.x << " " << c/g*st.y;

    return 0;
}
