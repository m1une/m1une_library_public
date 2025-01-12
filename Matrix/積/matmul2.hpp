template <typename T>
vector<T> matmul(const vector<vector<T>>& a, const vector<T>& b) {
    assert(a[0].size() == b.size());
    int n = a.size(), m = a[0].size();
    vector<T> res(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < m; ++k) {
            res[i] += a[i][k] * b[k];
        }
    }
    return res;
}