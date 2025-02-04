// verified by https://atcoder.jp/contests/abc379/submissions/62393196
template <class F, auto composition, auto id>
struct dual_segtree {
    static_assert(
        std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
        "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
                  "id must work as F()");

   private:
    int _n, size, log;
    std::vector<F> lz;

   public:
    dual_segtree() : dual_segtree(0) {}
    explicit dual_segtree(int n) : dual_segtree(std::vector<F>(n, id())) {}
    explicit dual_segtree(const std::vector<F> &v) : _n(int(v.size())) {
        size = (int)std::bit_ceil((unsigned int)(_n));
        log = std::countr_zero((unsigned int)size);
        lz = std::vector<F>(2 * size, id());
    }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        lz[p] = composition(f, lz[p]);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) {
                lz[l] = composition(f, lz[l]);
                ++l;
            }
            if (r & 1) {
                --r;
                lz[r] = composition(f, lz[r]);
            }
            l >>= 1;
            r >>= 1;
        }
    }
    F get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        F res = lz[p];
        while (p >>= 1) res = composition(res, lz[p]);
        return res;
    }
};