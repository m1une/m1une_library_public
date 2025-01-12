// verified by https://atcoder.jp/contests/arc127/submissions/60917781
vector<ll> dton(ll d, ll n) {
    vector<ll> res;
    while (d > 0) {
        res.push_back(d % n);
        d /= n;
    }
    return res;
}