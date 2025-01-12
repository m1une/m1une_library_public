// verified by https://codeforces.com/contest/620/problem/E
// https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7
// ETの内部は1-indexed
struct EulerTour {
   private:
    int timer;

   public:
    vector<vector<int>>& G;
    vector<int> in, out, parent, ET;
    EulerTour(vector<vector<int>>& G, int root = 0)
        : G(G), in(G.size()), out(G.size()), parent(G.size()) {
        timer = 0;
        ET.reserve(2 * G.size());
        dfs(root, -1);
    }
    void dfs(int v, int p) {
        parent[v] = p;
        in[v] = timer++;
        ET.push_back(v + 1);
        for (int u : G[v]) {
            if (u == p) continue;
            dfs(u, v);
        }
        out[v] = timer++;
        ET.push_back(-v - 1);
    }
    int size() const { return ET.size(); }
    int operator[](int i) { return ET[i]; }
};