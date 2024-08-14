#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> dis(0.0, 1.0);

// функция, переводит что-то в численный результат
int check(vector <int> a) {
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            if (i != j && abs(a[i] - a[j]) == abs(i - j)) cnt++;
        }
    }
    return cnt;
}

int rnd_int(int l, int r) {
    if (l > r) swap(l, r);
    return rnd() % (r - l + 1) + l;
}

vector <int> rnd_swap(vector <int> a) {
    int i = rnd_int(0, a.size() - 1), j;
    do {
        j = rnd_int(0, a.size() - 1);
    } while (j == i);
    swap(a[i], a[j]);
    return a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector <int> a(n); iota(a.begin(), a.end(), 0);
    int res = 0;
    do {
        shuffle(a.begin(), a.end(), rnd);
        res = check(a);
        int new_res;
        // меняй константы чтобы было хорошо
        double T = 1000;
        int iter = 50000;
        while (iter && res != 0) {
            vector <int> b = rnd_swap(a); // тут должно происходить небольшое изменение
            new_res = check(b);
            if (new_res <= res || exp(-(new_res - res) / T) > dis(rnd)) {
                a = b;
                res = new_res;
            }
            T *= 0.999;
            iter--;
        }
    } while (res != 0);
    for (auto el: a) cout << el + 1 << " ";
}
