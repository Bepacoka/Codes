#include <bits/stdc++.h>

using namespace std;

vector <int> build_suffarray(const string &s) { // s += '#'
    size_t n = s.size();
    vector <int> pos(n), unpos(n), npos(n), eq(n), neq(n);
    vector <int> cnt(max(90ul, n + 1)), cnt1(max(90ul, n + 1));
    for (int i = 0; i < n; i++) cnt[s[i] - '#' + 1]++;
    for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];

    for (int i = 0; i < n; i++) {
        pos[cnt[s[i] - '#']++] = i; // признаюсь честно, придумал это не я, но как стабильная сортировка подсчётом выглядит конченно
    }
    char last_char = '#';
    int a = 0;
    for (int i = 0; i < n; i++) {
        if (s[pos[i]] != last_char) {
            last_char = s[pos[i]];
            a++;
        }
        eq[pos[i]] = a;
    }
    // так, у нас есть pos[i] - ...а хер его знает что это, типа... номер подстроки [i: i+shift) в отсортированном списке?..
    // UPD: видимо это обратная фигня к описанной, т.е. pos[i] - такое x, что подстрока [x: x+shift) на i-том месте в отсорте
    // так, у нас есть eq[i] - класс эквивалетности у подстроки [i: i+shift)
    int shift = 1;
    while (shift <= n) {
        // у нас пары {eq[i], eq[(i + shift) % n]}
        cnt.assign(cnt.size(), 0);
        for (int i = 0; i < n; i++) cnt[eq[i] + 1]++;
        for (int i = 1; i < cnt.size(); i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) {
            unpos[cnt[eq[(pos[i] - shift + n) % n]]++] = i; // произошла сортировка подсчётом
        }
        // unpos в итоге какая то лажа, делаем её нормально, чтобы стала как pos
        for (int i = 0; i < n; i++) npos[i] = (pos[unpos[i]] - shift + n) % n;
        neq[npos[0]] = 0; // самый первый видимо
        for (int i = 1; i < n; i++) {
            neq[npos[i]] = neq[npos[i - 1]];
            if (eq[npos[i]] != eq[npos[i - 1]] || eq[(npos[i] + shift) % n] != eq[(npos[i - 1] + shift) % n]) neq[npos[i]]++;
        }
        eq.swap(neq);
        pos.swap(npos);
        shift *= 2;
    }
    return pos;
}
