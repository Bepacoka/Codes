#include <vector>

using namespace std;

typedef unsigned long long ull;

int maxlen;

struct PolyHash {
    static const int mod = 100000123;
    static const int base = 100000007;
    static vector<int> pow1;
    static vector<ull> pow2;
    static inline int diff(int a, int b) {
        return (a -= b) < 0 ? a + mod : a;
    }
    vector<int> h1;
    vector<ull> h2;
    explicit PolyHash(string s) : h1(s.size() + 1, 0), h2(s.size() + 1, 0) {
        while (pow1.size() <= s.size()) {
            pow1.push_back(1LL * pow1.back() * base % mod);
            pow2.push_back(pow2.back() * base);
        }
        for (int i = 0; i < s.size(); ++i) {
            h1[i + 1] = (h1[i] + 1LL * s[i] * pow1[i]) % mod;
            h2[i + 1] = h2[i] + s[i] * pow2[i];
        }
    }
    inline pair <int, ull> operator[](pair <int, int> sub) const;
};

inline pair<int, ull> PolyHash::operator[](pair <int, int> sub) const {
    int hash1 = h1[sub.second] - h1[sub.first];
    ull hash2 = h2[sub.second] - h2[sub.first];
    if (hash1 < 0) hash1 += mod;
    hash1 = 1LL * hash1 * pow1[maxlen - sub.second + 1] % mod;
    hash2 *= pow2[maxlen - sub.second + 1];
    return {hash1, hash2};
}

vector<int> PolyHash::pow1{1};
vector<ull> PolyHash::pow2{1};
