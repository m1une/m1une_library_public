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