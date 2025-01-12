// verified by https://judge.yosupo.jp/problem/matrix_product
template <typename T>
vector<vector<T>> matmul(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    int n = a.size(), m = a[0].size(), l = b[0].size();
    vector<vector<T>> res(n, vector<T>(l, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {
            for (int k = 0; k < m; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}