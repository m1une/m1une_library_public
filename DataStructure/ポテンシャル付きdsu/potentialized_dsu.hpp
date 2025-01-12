// verified by https://atcoder.jp/contests/abc087/submissions/56878250
template <typename T>
struct potentialized_dsu {
   private:
    int n;
    vector<int> par_or_size;
    vector<T> pot;

   public:
    potentialized_dsu(int n) : n(n), par_or_size(n, -1), pot(n, 0) {}
    int leader(int a) {
        assert(0 <= a && a < n);
        if (par_or_size[a] < 0)
            return a;
        else {
            int res = leader(par_or_size[a]);
            pot[a] += pot[par_or_size[a]];
            return par_or_size[a] = res;
        }
    }
    T potential(int a) {
        assert(0 <= a && a < n);
        leader(a);
        return pot[a];
    }
    int size(int a) {
        assert(0 <= a && a < n);
        return -par_or_size[leader(a)];
    }
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return leader(a) == leader(b);
    }
    // potential(b) - potential(a) = d
    int merge(int a, int b, T d) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        d += potential(a);
        d -= potential(b);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        if (-par_or_size[x] < -par_or_size[y]) {
            swap(x, y);
            d = -d;
        }
        par_or_size[x] += par_or_size[y];
        par_or_size[y] = x;
        pot[y] = d;
        return x;
    }
    T diff(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        assert(leader(a) == leader(b));
        return potential(b) - potential(a);
    }
    vector<vector<int>> groups() {
        vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; ++i) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; ++i) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(remove_if(result.begin(), result.end(),
                               [&](const vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }
};