#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 998244353, PROOT = 31, RPROOT = 128805723;

ll binpow(ll a, ll b) {
    if (b == 0) return 1;
    ll x = binpow(a, b / 2);
    if (b % 2) return a * x % MOD * x % MOD;
    return x * x % MOD;
}

ll rev(ll num, ll lg) {
    ll res = 0;
    for (ll i = 0; i < lg; i++) if (num & (1 << i)) res |= 1 << (lg - i - 1);
    return res;
}

void fft(vector<ll> &p, bool invert) {
    ll lg = __lg(2 * p.size() - 1);

    for (ll i = 0; i < p.size(); ++i)
        if (i < rev(i, lg))
            swap(p[i], p[rev(i, lg)]);

    for (ll l = 1; l < p.size(); l <<= 1) {
        ll w;
        if (invert) w = RPROOT;
        else w = PROOT;
        for (ll i = l; i < (1 << 22); i <<= 1) w = w * w % MOD;
        for (ll s = 0; s < p.size(); s += 2 * l) {
            ll cur_w = 1;
            for (ll a = 0; a < l; ++a) {
                ll u = p[s + a], v = p[s + a + l] * cur_w % MOD;
                p[s + a] = u + v < MOD ? u + v : u + v - MOD;
                p[s + a + l] = u - v >= 0 ? u - v : u - v + MOD;
                cur_w = cur_w * w % MOD;
            }
        }
    }
    if (invert) {
        ll nrev = binpow(p.size(), MOD - 2);
        for (ll &i : p) i = ll(i * 1ll * nrev % MOD);
    }
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
    ll len = 1 << __lg((a.size() + b.size()) * 2 - 1);
    a.resize(len);
    b.resize(len);
    fft(a, false);
    fft(b, false);
    for (ll i = 0; i < a.size(); i++) a[i] = (1LL * a[i] * b[i]) % MOD;
    fft(a, true);
    return a;
}

signed main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> b(m);
    for (ll i = 0; i < m; i++) cin >> b[i];
    auto ans = multiply(a, b);
    ans.resize(n + m - 1);
    for (auto el: ans) cout << el << " ";
}
