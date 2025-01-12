// verified by https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_E
ll levendis(const string &s, const string &t) {
    ll n = s.size(), m = t.size();
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0LL));
    for (ll i = 0; i <= n; ++i) dp[i][0] = i;
    for (ll i = 0; i <= m; ++i) dp[0][i] = i;
    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= m; ++j) {
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1,
                            dp[i - 1][j - 1] + (s[i - 1] != t[j - 1])});
        }
    }
    return dp[n][m];
}
