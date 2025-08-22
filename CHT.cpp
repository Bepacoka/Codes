#include <bits/stdc++.h>

using namespace std;
using ll = long long; 

constexpr ll INF = 1e18;

struct line {
    int k = 0;
    ll b = INF, x0 = -INF;
    ll operator()(int x) const {
        return 1LL * k * x + b;
    }
};

ll divide(ll a, ll b) {
    assert(b != 0);
    int delta = 0;
    if (a % b) delta = 1;
    if (a > 0 && b > 0 || a < 0 && b < 0) return a / b + delta;
    return -(abs(a) / abs(b));
}

signed main() {
    int n;
    cin >> n;
    vector <int> a(n);
    vector <int> b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector <line> st;
    vector <ll> dp(n);
    dp[0] = 0;
    st.push_back({b[0], dp[0], -INF});
    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (pos > st.size()) pos = st.size();
        while (pos < st.size() && st[pos].x0 <= a[i]) pos++;
        pos--;
        dp[i] = st[pos](a[i]);

        ll x = -INF;
        if (i < n) {
            while (!st.empty()) {
                x = divide(st.back().b - dp[i], b[i] - st.back().k);
                if (x > st.back().x0) break;
                st.pop_back();
            }
        }
        st.push_back({b[i], dp[i], x});
    }

    cout << dp.back();
}
