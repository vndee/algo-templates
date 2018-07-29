#include <iostream>
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

/// sieve of eratosthenes
bitset<10000001> bs;
vi primes, numDiff;
ll _sieve_size;

void sieve(ll upperbound) {
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for (ll i = 2; i <= _sieve_size; i++)
        if (bs[i]) {
            for (ll j = i*i; j <= _sieve_size; j += i) bs[j] = 0;
            primes.push_back((ll)i);
        }
}

/// check if N is prime
bool isPrime(ll N) {
    if (N <= _sieve_size) return bs[N];
    for (ll i = 0, v; i < primes.size() && (v = primes[i]) <= trunc(sqrt(N)); i++)
        if (N % v == 0) return false;
    return true;
}

/// gcd and lcm
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a * (b / gcd(a, b)); }

/// prime factors
vi primeFactors(ll N) {
    vi factors;
    ll PF_idx = 0, PF = primes[PF_idx];
    while (PF*PF <= N) {
        while (N % PF == 0) {
            N /= PF;
            factors.push_back(PF);
        }
        PF = primes[++PF_idx];
    }
    if (N != 1) factors.push_back(N);
    return factors;
}

/// count the number of prime factors
ll numPF(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (PF*PF <= N) {
        while (N % PF == 0) N /= PF, ans++;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans++;
    return ans;
}

/// count the number of different prime factors of N
ll numDiffPF(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (PF*PF <= N) {
        while (N % PF == 0) N /= PF;
        ans++;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans++;
    return ans;
}
ll numDiffPF_modified(ll upperbound) {
    numDiff.assign(upperbound, 0);
    for (int i = 2; i < upperbound; i++)
        if (numDiff[i] == 0)
            for (int j = i; j < upperbound; j += i)
                numDiff[j]++;
}

/// sum the prime factors of N
ll sumPF(ll N) {
    ll PF_idx = 0, PF = primes[PF_idx], ans = 0;
    while (PF*PF <= N) {
        while (N % PF == 0) N /= PF, ans += PF;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans += N;
    return ans;
}

/// count the number of divisors of N
ll numDiv(ll N) {
    /*
        N = a^i*b^j*...*c^k;
        => ans = (i+1)*(j+1)*...*(k+1)
        */
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1;
    while (PF*PF <= N) {
        ll power = 0;
        while (N % PF == 0) N /= PF, power++;
        ans *= (power + 1);
        PF = primes[++PF_idx];
    }
    if (N == 1) ans *= 2;
    return ans;
}

/// sum the divisors of N
ll sumDiv(ll N) {
    /*
        N = a^i*b^j*...*c^k;
        => ans = ((a^(i+1)-1)/(a-1))*((b^(j+1)-1)/(b-1))*...*((c^(k+1)-1)/(c-1));
        */
    ll PF_idx = 0, PF = primes[PF_idx], ans = 1; // start from ans = 1
    while (PF * PF <= N) {
        ll power = 0;
        while (N % PF == 0) N /= PF, power++;
        ans *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);
        PF = primes[++PF_idx];
    }
    if (N != 1) ans *= ((ll)pow((double)N, 2.0) - 1) / (N - 1); // last
    return ans;
}

/// count the number positive integer less than N that are relatively prime to N
ll EulerPhi(ll N) {
    /*
        N = a^i*b^j*...*c^k;
        => ans = N*(1-1/a)*(1-1/b)*..*(1-1/c);
        */
    ll PF_idx = 0, PF = primes[PF_idx], ans = N;
    while (PF*PF <= N) {
        if (N % PF == 0) ans -= ans/PF;
        while (N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans -= ans/N;
    return ans;
}

/// solving linear diophantine equation

typedef pair<ll, ll> ii;
ii extendedEuclid(ll a, ll b) {
    ii qr, st;
    if (b == 0) return ii(1, 0);
    else {
        qr = ii(a/b, a%b);
        st = extendedEuclid(b, qr.y);
        return ii(st.y, st.x-qr.x*st.y);
    }
}

int main() {
    /*
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif // ONLINE_JUDGE
    */

    sieve(1000000);
    ii st = extendedEuclid(25, 18);
    cout << st.x << " " << st.y << endl;
    int g = gcd(25, 18);
    cout << 839/g*st.x << " " << 839/g*st.y << endl;

    return 0;
}
