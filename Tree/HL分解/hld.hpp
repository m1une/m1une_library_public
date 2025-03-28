#include <bits/stdc++.h>

#include <atcoder/lazysegtree>
#include <atcoder/segtree>
using namespace std;

#include <bits/stdc++.h>

#include <atcoder/lazysegtree>
#include <atcoder/segtree>
using namespace std;

struct HeavyLightDecomposition {
    int n;
    vector<vector<int>> G;
    vector<int> sz, in, rin, out, rout, head, par, dep;
    int root = 0;
    void dfs_sz(int v, int p) {
        sz[v] = 1;
        par[v] = p;
        dep[v] = (p == -1 ? 0 : dep[p] + 1);
        for (int &u : G[v]) {
            if (u == p) continue;
            dfs_sz(u, v);
            sz[v] += sz[u];
            if (G[v][0] == p || sz[u] > sz[G[v][0]]) swap(u, G[v][0]);
        }
    }
    void dfs_hld(int v, int p, int &t) {
        in[v] = t++;
        rin[v] = n - t;
        for (int u : G[v]) {
            if (u == p) continue;
            if (u == G[v][0]) {
                head[u] = head[v];
            } else {
                head[u] = u;
            }
            dfs_hld(u, v, t);
        }
        out[v] = t;
        rout[v] = n - t;
    }

    HeavyLightDecomposition(int _n)
        : n(_n),
          G(n),
          sz(n),
          in(n),
          rin(n),
          out(n),
          rout(n),
          head(n),
          par(n),
          dep(n) {}
    HeavyLightDecomposition(vector<vector<int>> &_G, int _root = 0)
        : n(_G.size()),
          G(_G),
          sz(n),
          in(n),
          rin(n),
          out(n),
          rout(n),
          head(n),
          par(n),
          dep(n),
          root(_root) {
        build(root);
    }
    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    void build(int _root = 0) {
        root = _root;
        dfs_sz(root, -1);
        int t = 0;
        dfs_hld(root, -1, t);
    }
    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] > dep[head[v]]) {
                u = par[head[u]];
            } else {
                v = par[head[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int distance(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    vector<int> ord() {
        vector<int> ord(n);
        for (int i = 0; i < n; i++) {
            ord[in[i]] = i;
        }
        return ord;
    }

    struct iter {
        int l, r;
        bool rev, last;
        iter(int _l, int _r, bool _rev, bool _last)
            : l(_l), r(_r), rev(_rev), last(_last) {}
    };

    vector<iter> path(int u, int v) {
        int lca = this->lca(u, v);
        vector<iter> res;
        while (head[u] != head[lca]) {
            res.emplace_back(in[head[u]], in[u] + 1, true, false);
            u = par[head[u]];
        }
        vector<iter> stk;
        while (head[v] != head[lca]) {
            stk.emplace_back(in[head[v]], in[v] + 1, false, false);
            v = par[head[v]];
        }
        if (in[u] < in[v]) {
            stk.emplace_back(in[u], in[v] + 1, false, true);
        } else {
            stk.emplace_back(in[v], in[u] + 1, true, true);
        }
        for (auto it = stk.rbegin(); it != stk.rend(); it++) {
            res.push_back(*it);
        }
        return res;
    }

    // ord順のsegtreeとordと逆順のsegtreeを渡す(非可換モノイドにも対応)
    template <class S, auto op, auto e>
    S path_query(int s, int t, atcoder::segtree<S, op, e> &seg,
                 atcoder::segtree<S, op, e> &rseg, bool edge = false) {
        S prds = e(), prdt = e();
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                prdt = op(seg.prod(in[head[t]], in[t] + 1), prdt);
                t = par[head[t]];
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[head[s]] + 1));
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s] + 1, in[t] + 1));
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[t]));
            }
        } else {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s], in[t] + 1));
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[t] + 1));
            }
        }
        return op(prds, prdt);
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    S path_query(
        int s, int t,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &rseg,
        bool edge = false) {
        S prds = e(), prdt = e();
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                prdt = op(seg.prod(in[head[t]], in[t] + 1), prdt);
                t = par[head[t]];
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[head[s]] + 1));
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s] + 1, in[t] + 1));
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[t]));
            }
        } else {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s], in[t] + 1));
            } else {
                prds = op(prds, rseg.prod(rin[s], rin[t] + 1));
            }
        }
        return op(prds, prdt);
    }

    // 可換モノイドの場合、ord順のsegtreeを渡す
    template <class S, auto op, auto e>
    S path_query(int s, int t, atcoder::segtree<S, op, e> &seg,
                 bool edge = false) {
        S prds = e(), prdt = e();
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                prdt = op(seg.prod(in[head[t]], in[t] + 1), prdt);
                t = par[head[t]];
            } else {
                prds = op(prds, seg.prod(in[head[s]], in[s] + 1));
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s] + 1, in[t] + 1));
            } else {
                prds = op(prds, seg.prod(in[t] + 1, in[s] + 1));
            }
        } else {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s], in[t] + 1));
            } else {
                prds = op(prds, seg.prod(in[t], in[s] + 1));
            }
        }
        return op(prds, prdt);
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    S path_query(
        int s, int t,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        bool edge = false) {
        S prds = e(), prdt = e();
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                prdt = op(seg.prod(in[head[t]], in[t] + 1), prdt);
                t = par[head[t]];
            } else {
                prds = op(prds, seg.prod(in[head[s]], in[s] + 1));
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s] + 1, in[t] + 1));
            } else {
                prds = op(prds, seg.prod(in[t] + 1, in[s] + 1));
            }
        } else {
            if (in[s] < in[t]) {
                prds = op(prds, seg.prod(in[s], in[t] + 1));
            } else {
                prds = op(prds, seg.prod(in[t], in[s] + 1));
            }
        }
        return op(prds, prdt);
    }

    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void path_apply(
        int s, int t,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &rseg, F f,
        bool edge = false) {
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                seg.apply(in[head[t]], in[t] + 1, f);
                rseg.apply(rin[t], rin[head[t]] + 1, f);
                t = par[head[t]];
            } else {
                seg.apply(in[head[s]], in[s] + 1, f);
                rseg.apply(rin[s], rin[head[s]] + 1, f);
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                seg.apply(in[s] + 1, in[t] + 1, f);
                rseg.apply(rin[t], rin[s], f);
            } else {
                seg.apply(in[t] + 1, in[s] + 1, f);
                rseg.apply(rin[s], rin[t], f);
            }
        } else {
            if (in[s] < in[t]) {
                seg.apply(in[s], in[t] + 1, f);
                rseg.apply(rin[t], rin[s] + 1, f);
            } else {
                seg.apply(in[t], in[s] + 1, f);
                rseg.apply(rin[s], rin[t] + 1, f);
            }
        }
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void path_apply(
        int s, int t,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg, F f,
        bool edge = false) {
        while (head[s] != head[t]) {
            if (dep[head[s]] < dep[head[t]]) {
                seg.apply(in[head[t]], in[t] + 1, f);
                t = par[head[t]];
            } else {
                seg.apply(in[head[s]], in[s] + 1, f);
                s = par[head[s]];
            }
        }
        if (edge) {
            if (in[s] < in[t]) {
                seg.apply(in[s] + 1, in[t] + 1, f);
            } else {
                seg.apply(in[t] + 1, in[s] + 1, f);
            }
        } else {
            if (in[s] < in[t]) {
                seg.apply(in[s], in[t] + 1, f);
            } else {
                seg.apply(in[t], in[s] + 1, f);
            }
        }
    }

    // 可換モノイドのみ対応
    template <class S, auto op, auto e>
    S subtree_query(int v, atcoder::segtree<S, op, e> &seg, bool edge = false) {
        if (edge) {
            return seg.prod(in[v] + 1, out[v]);
        } else {
            return seg.prod(in[v], out[v]);
        }
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    S subtree_query(
        int v,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        bool edge = false) {
        if (edge) {
            return seg.prod(in[v] + 1, out[v]);
        } else {
            return seg.prod(in[v], out[v]);
        }
    }

    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void subtree_apply(
        int v,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &rseg, F f,
        bool edge = false) {
        if (edge) {
            seg.apply(in[v] + 1, out[v], f);
            rseg.apply(rout[v], rin[v], f);
        } else {
            seg.apply(in[v], out[v], f);
            rseg.apply(rout[v], rin[v] + 1, f);
        }
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void subtree_apply(
        int v,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg, F f,
        bool edge = false) {
        if (edge) {
            seg.apply(in[v] + 1, out[v], f);
        } else {
            seg.apply(in[v], out[v], f);
        }
    }

    template <class S, auto op, auto e>
    void set(int v, S x, atcoder::segtree<S, op, e> &seg,
             atcoder::segtree<S, op, e> &rseg) {
        seg.set(in[v], x);
        rseg.set(rin[v], x);
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void set(
        int v, S x,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &rseg) {
        seg.set(in[v], x);
        rseg.set(rin[v], x);
    }
    template <class S, auto op, auto e>
    void set(int v, S x, atcoder::segtree<S, op, e> &seg) {
        seg.set(in[v], x);
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    void set(
        int v, S x,
        atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg) {
        seg.set(in[v], x);
    }

    template <class S, auto op, auto e>
    S get(int v, atcoder::segtree<S, op, e> &seg) {
        return seg.get(in[v]);
    }
    template <class S, auto op, auto e, class F, auto mapping, auto composition,
              auto id>
    S get(int v,
          atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> &seg) {
        return seg.get(in[v]);
    }
};