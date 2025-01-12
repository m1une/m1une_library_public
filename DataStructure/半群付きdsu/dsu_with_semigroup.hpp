// verified by https://atcoder.jp/contests/abc372/submissions/61084969
// S : 半群の型
// op(S a, S b) : 結合法則を満たす これはa,bを破壊してもよい
template <class S, auto op>
struct dsu_with_semigroup {
    static_assert(
        std::is_convertible_v<decltype(op), std::function<S(S, S)>> ||
            std::is_convertible_v<decltype(op), std::function<S(S &&, S)>> ||
            std::is_convertible_v<decltype(op), std::function<S(S, S &&)>> ||
            std::is_convertible_v<decltype(op), std::function<S(S &&, S &&)>>,
        "op must work as S(S, S)");

   private:
    int _n;
    std::vector<int> par_or_size;
    std::vector<S> d;

   public:
    dsu_with_semigroup() : _n(0) {}
    dsu_with_semigroup(int n) : _n(n), par_or_size(n, -1), d(n) {}
    dsu_with_semigroup(const std::vector<S> &v)
        : _n(int(v.size())), par_or_size(_n, -1), d(v) {}

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (par_or_size[a] < 0) return a;
        return par_or_size[a] = leader(par_or_size[a]);
    }

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-par_or_size[x] >= -par_or_size[y]) {
            par_or_size[x] += par_or_size[y];
            par_or_size[y] = x;
            d[x] = op(move(d[x]), move(d[y]));
            return x;
        } else {
            par_or_size[y] += par_or_size[x];
            par_or_size[x] = y;
            d[y] = op(move(d[x]), move(d[y]));
            return y;
        }
    }

    bool same(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    S &operator[](int a) {
        assert(0 <= a && a < _n);
        return d[leader(a)];
    }

    int size(int a) {
        assert(0 <= a && a < _n);
        return -par_or_size[leader(a)];
    }

    std::vector<std::vector<int>> groups() {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; ++i) {
            leader_buf[i] = leader(i);
            ++group_size[leader_buf[i]];
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; ++i) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; ++i) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(
                         result.begin(), result.end(),
                         [&](const std::vector<int> &v) { return v.empty(); }),
                     result.end());
        return result;
    }

    std::vector<S *> values() {
        std::vector<S *> result;
        result.reserve(_n);
        for (int i = 0; i < _n; ++i) {
            if (par_or_size[i] < 0) result.push_back(&d[i]);
        }
        return result;
    }
};