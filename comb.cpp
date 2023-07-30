#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

vector <unsigned long long> fact = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000, 6402373705728000};

vector <vector <unsigned long long>> memC;

unsigned long long C(int n, int k) {
    if (memC[n][k] != 0) return memC[n][k];
    if (k > n) return 0;
    if (n == 0) return 1;
    if (k == 0) return 1;
    if (memC[n - 1][k] == 0) memC[n - 1][k] = C(n - 1, k);
    if (memC[n - 1][k - 1] == 0) memC[n - 1][k - 1] = C(n - 1, k - 1);
    memC[n][k] = memC[n - 1][k] + memC[n - 1][k - 1];
    return memC[n][k];
}

unsigned long long pow(unsigned long long a, unsigned long long b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    unsigned long long x = pow(a, b / 2);
    if (b % 2 == 0) return x * x;
    else return x * x * a;
}

vector <int> alphabet;

vector <int> next_permutation(vector <int> a) {
    for (int i = a.size() - 2; i >= 0; i--) {
        if (a[i] < a[i + 1]) {
            int l = i, r = a.size();
            while (r - l > 1) {
                int m = l + (r - l) / 2;
                if (a[m] > a[i]) {
                    l = m;
                } else {
                    r = m;
                }
            }
            swap(a[i], a[l]);
            reverse(a.begin() + i + 1, a.end());
            return a;
        }
    }
    return {alphabet[0] - 1};
}

vector <int> next_permutation_with_repeats(vector <int> a) {
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != alphabet.back()) {
            a[i] = *(lower_bound(alphabet.begin(), alphabet.end(), a[i]) + 1);
            for (int j = i + 1; j < a.size(); j++) a[j] = alphabet[0];
            return a;
        }
    }
    return {alphabet[0] - 1};
}

unsigned long long get_num_by_permutation(vector <int> a) {
    unsigned long long ans = 0;
    vector <int> alphabet_copy = alphabet;
    for (int i = 0; i < a.size(); i++) {
        auto num = lower_bound(alphabet_copy.begin(), alphabet_copy.end(), a[i]);
        ans += (num - alphabet_copy.begin()) * fact[alphabet_copy.size() - 1];
        alphabet_copy.erase(num);
    }
    return ans;
}

unsigned long long get_num_by_permutation_with_repeats(vector <int> a) {
    unsigned long long ans = 0;
    for (int i = 0; i < a.size(); i++) {
        auto num = lower_bound(alphabet.begin(), alphabet.end(), a[i]);
        ans += (num - alphabet.begin()) * pow(alphabet.size(), a.size() - i - 1);
    }
    return ans;
}

vector <int> get_permutation_by_num(unsigned long long num) {
    vector <int> alphabet_copy = alphabet, a(alphabet.size());
    for (int i = 0; i < a.size(); i++) {
        a[i] = alphabet_copy[num / fact[alphabet_copy.size() - 1]];
        alphabet_copy.erase(alphabet_copy.begin() + num / fact[alphabet_copy.size() - 1]);
        num %= fact[alphabet_copy.size()];
    }
    return a;
}

vector <int> next_arrangement(vector <int> a) {
    set <int> nums(alphabet.begin(), alphabet.end());
    for (int i = 0; i < a.size(); i++) nums.erase(a[i]);
    for (int i = a.size() - 1; i >= 0; i--) {
        if (!nums.empty() and a[i] < *(nums.rbegin())) {
            auto it = nums.upper_bound(a[i]);
            nums.insert(a[i]);
            nums.erase(it);
            a[i] = *(it);
            for (int j = i + 1; j < a.size(); j++) {
                a[j] = *nums.begin();
                nums.erase(nums.begin());
            }
            return a;
        } else {
            nums.insert(a[i]);
        }
    }
    return {alphabet[0] - 1};
}

unsigned long long get_num_by_arrangement(vector <int> a) {
    unsigned long long ans = 0;
    vector <int> alphabet_copy = alphabet;
    for (int i = 0; i < a.size(); i++) {
        auto num = lower_bound(alphabet_copy.begin(), alphabet_copy.end(), a[i]);
        ans += (num - alphabet_copy.begin()) * (fact[alphabet_copy.size() - 1] / fact[alphabet_copy.size() - 1 - (a.size() - i - 1)]);
        alphabet_copy.erase(num);
    }
    return ans;
}

vector <int> get_arrangement_by_num(unsigned long long num, int k) {
    vector <int> alphabet_copy = alphabet, a(k);
    for (int i = 0; i < a.size(); i++) {
        a[i] = alphabet_copy[num / (fact[alphabet_copy.size() - 1] / fact[alphabet_copy.size() - 1 - (a.size() - i - 1)])];
        alphabet_copy.erase(alphabet_copy.begin() + num / (fact[alphabet_copy.size() - 1] / fact[alphabet_copy.size() - 1 - (a.size() - i - 1)]));
        num %= fact[alphabet_copy.size()] / fact[alphabet_copy.size() - (a.size() - i - 1)];
    }
    return a;
}

vector <int> next_combination(vector <int> a) {
    for (int i = 0; i < a.size(); i++) {
        if (a[a.size() - i - 1] != alphabet[alphabet.size() - i - 1]) {
            auto it = lower_bound(alphabet.begin(), alphabet.end(), a[a.size() - i - 1]);
            a[a.size() - i - 1] = *(it + 1);
            for (int j = a.size() - i; j < a.size(); j++) {
                a[j] = a[j - 1] + 1;
            }
            return a;
        }
    }
    return {alphabet[0] - 1};
}

vector <int> next_combination_with_repeats(vector <int> a) {
    for (int i = 0; i < a.size(); i++) {
        if (a[a.size() - i - 1] != alphabet[alphabet.size() - 1]) {
            auto it = lower_bound(alphabet.begin(), alphabet.end(), a[a.size() - i - 1]);
            a[a.size() - i - 1] = *(it + 1);
            for (int j = a.size() - i; j < a.size(); j++) {
                a[j] = a[j - 1];
            }
            return a;
        }
    }
    return {alphabet[0] - 1};
}

unsigned long long get_num_by_combination(vector <int> a) {
    int prev = 1;
    unsigned long long ans = 0;
    for (int i = 0; i < a.size(); i++) {
        prev++;
        while (a[i] > prev) {
            ans += C(alphabet.size() - prev, a.size() - i - 1);
            prev++;
        }
    }
    return ans;
}

unsigned long long get_num_by_combination_with_repeats(vector <int> a) {
    int prev = 1;
    unsigned long long ans = 0;
    for (int i = 0; i < a.size(); i++) {
        while (a[i] > prev) {
            ans += C(alphabet.size() - prev + a.size() - i - 1, a.size() - i - 1);
            prev++;
        }
    }
    return ans;
}

vector <int> get_combination_by_num(unsigned long long num, int k) {
    vector <int> a(k);
    int prev = 1;
    for (int i = 0; i < a.size(); i++) {
        unsigned long long tmp = C(alphabet.size() - prev, a.size() - i - 1);
        while (num >= tmp) {
            num -= tmp;
            prev++;
            tmp = C(alphabet.size() - prev, a.size() - i - 1);
        }
        a[i] = prev;
        prev++;
    }
    return a;
}

vector <int> get_combination_by_num_with_repeats(unsigned long long num, int k) {
    vector <int> a(k);
    int prev = 1;
    for (int i = 0; i < a.size(); i++) {
        unsigned long long tmp = C(alphabet.size() - prev + a.size() - i - 1, a.size() - i - 1);
        while (num >= tmp) {
            num -= tmp;
            prev++;
            tmp = C(alphabet.size() - prev + a.size() - i - 1, a.size() - i - 1);
        }
        a[i] = prev;
    }
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    memC.resize(n + k, vector <unsigned long long>(n + k));
    alphabet.resize(n);
}
