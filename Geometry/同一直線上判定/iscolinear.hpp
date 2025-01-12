// verified by https://atcoder.jp/contests/arc173/submissions/60921104
template <typename T>
bool iscolinear(const vector<pair<T, T>> &A) {
    if (A.size() <= 2) return true;
    T x0 = A[0].first, y0 = A[0].second;
    T x1 = A[1].first, y1 = A[1].second;
    T dx = x1 - x0, dy = y1 - y0;
    for (int i = 2; i < A.size(); ++i) {
        T x = A[i].first, y = A[i].second;
        if (dx * (y - y0) != dy * (x - x0)) return false;
    }
    return true;
}