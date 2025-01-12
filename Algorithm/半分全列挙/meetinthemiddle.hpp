// O(2^(n/2))
// based on https://atcoder.jp/contests/abc326/editorial/7554
// verified by https://atcoder.jp/contests/abc326/submissions/61627051

template <typename T>
vector<pair<T, long long>> parsum(const vector<T> &a) {
    vector<pair<T, long long>> res = {{0, 0}};
    for (int bit = 0; bit < (int)a.size(); ++bit) {
        T x = a[bit];
        vector<pair<T, long long>> b = res;
        for (int i = 0; i < (int)b.size(); ++i) {
            b[i].first += x;
            b[i].second |= 1 << bit;
        }
        vector<pair<T, long long>> n = move(res);
        for (int i = 0; i < (int)n.size(); ++i) {
            n[i].first -= x;
        }
        res = vector<pair<T, long long>>();
        merge(n.begin(), n.end(), b.begin(), b.end(), back_inserter(res));
    }
    return res;
}

// aの部分集合の和がxになるような部分集合を返す
// 問題に応じて尺取り法の部分を適宜変更する
template <typename T>
long long mitm(T x, const vector<T> &a) {
    vector<T> a1 = vector<T>(a.begin(), a.begin() + a.size() / 2);
    vector<T> a2 = vector<T>(a.begin() + a.size() / 2, a.end());
    int n1 = a1.size();
    vector<pair<T, long long>> s1 = parsum<T>(a1);
    vector<pair<T, long long>> s2 = parsum<T>(a2);
    reverse(s2.begin(), s2.end());
    long long ans = -1;
    int i = 0, j = 0;
    int ns1 = s1.size(), ns2 = s2.size();
    while (i < ns1 && j < ns2) {
        T sum = s1[i].first + s2[j].first;
        if (sum == x) {
            ans = s1[i].second | (s2[j].second << n1);
            break;
        } else if (sum < x) {
            i++;
        } else {
            j++;
        }
    }
    return ans;
}
