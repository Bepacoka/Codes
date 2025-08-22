#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using lll = __int128_t;

mt19937_64 rnd(1337228666);

ll add(ll a, ll b, ll mod) { // лишь бы числа были меньше модуля
    if (a + b > mod) return a + b - mod;
    if (a + b < 0) return a + b + mod;
    return a + b;
}

ll mult(ll a, ll b, ll mod) {
    ll res = (lll)a * b % mod;
    if (res < 0) return res + mod;
    return res;
}

lll binpow(ll a, ll b) {
    if (b == 0) return 1;
    lll x = binpow(a, b / 2);
    if (b & 1) return (lll)a * x * x;
    return (lll)x * x;
}

ll binpow(ll a, ll b, ll mod) {
    if (b == 0) return 1;
    ll x = binpow(a, b / 2, mod);
    if (b & 1) return mult(a, mult(x, x, mod), mod);
    return mult(x, x, mod);
}

ll gcdext(ll a, ll b, ll &x, ll &y) { // ax + by = d
    if (b == 0) {
        x = 1;
        if (a < 0) x = -1;
        y = 0;
        return abs(a);
    }
    ll d = gcdext(b, a % b, x, y);
    ll t = x;
    x = y;
    y = t - y * (a / b);
    return d;
}

ll crt(ll r1, ll m1, ll r2, ll m2) {
    ll k1, k2;
    ll d = gcdext(m2, -m1, k2, k1);
    const ll M = m1 / d * m2;
    if ((r1 - r2) % d) return -1;
    k1 *= (r1 - r2) / d;
    return add(mult(k1, m1, M), r1 % M, M);
}

ll crt(vector <ll> &r, vector <ll> &m) {

}

bool isprime(ll x) {
    if (x == 1) return false;
    if (x == 2) return true;
    if (x == 3) return true; // там x - 3 плохо
    int n = 1;
    while (!((x - 1) & ((1ll << n) - 1))) ++n;
    --n;
    ll m = (x - 1) / (1ll << n);
    for (int k = 0; k < 20; k++) {
        ll a = rnd() % (x - 3) + 2;
        ll r = binpow(a, m, x);
        if (r == 1 || r == x - 1) continue;
        bool flag = false;
        for (int i = 0; i < n; i++) {
            r = binpow(r, 2, x); // да.
            if (r == x - 1) {
                flag = true;
                break;
            }
        }
        if (!flag) return false;
    }
    return true;
}

typedef long long ll;

ll rho_pollard(ll n, ll a = 1) {
    ll x = rnd() % (n - 3) + 1, y = 1;
    ll d = 1;
    ll i = 0, stage = 2;
    while (d == 1) {
        if (i == stage) {
            y = x;
            stage *= 2;
        }
        x = add(mult(x, x, n), a, n);
        d = __gcd(n, abs(x - y));
        i++;
    }
    if (d == n) return rho_pollard(n, a + 1);
    return d;
}

vector <pair <ll, int>> factorize(ll n) {
    if (n == 1) return {};
    if (isprime(n)) return {{n, 1}};
    ll d = rho_pollard(n);
    auto ans1 = factorize(n / d);
    auto ans2 = factorize(d);
    vector <pair <ll, int>> ans;
    int i = 0, j = 0;
    while (i < ans1.size() && j < ans2.size()) {
        if (ans1[i].first == ans2[j].first) {
            ans.emplace_back(ans1[i].first, ans1[i].second + ans2[j].second);
            i++;
            j++;
            continue;
        }
        if (ans1[i].first < ans2[j].first) {
            ans.emplace_back(ans1[i]);
            i++;
        } else {
            ans.emplace_back(ans2[j]);
            j++;
        }
    }
    while (i < ans1.size()) ans.emplace_back(ans1[i++]);
    while (j < ans2.size()) ans.emplace_back(ans2[j++]);
    return ans;
}

void sieve(ll n, vector <ll> &lp, vector <ll> &vec) {
    lp.resize(n + 1, -1);
    for (ll i = 2; i <= n; i++) {
        if (lp[i] == -1) {
            lp[i] = i;
            vec.push_back(i);
        }
        for (ll j = 0; j < vec.size() && vec[j] * i <= n && lp[i] >= vec[j]; j++) {
            lp[vec[j] * i] = vec[j];
        }
    }
}
