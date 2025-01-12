// warning: not verified
// n[i]: i-th digit from the right
ll ntod(const vector<ll> &n, ll d) {
    ll res = 0;
    for (ll i = n.size() - 1; i >= 0; --i) {
        res = res * d + n[i];
    }
    return res;
}