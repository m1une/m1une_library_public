// verified by https://atcoder.jp/contests/abc387/submissions/61625033
// なもりグラフを森に分解する
struct Namori {
    int N;
    vector<int> parent, depth, root;
    vector<vector<int>> g;
    vector<vector<int>> loops;
    struct Node {
        int idx;
        vector<int> children;
    };
    vector<vector<Node>> forest;
    Namori(const vector<int> &par) : parent(par) {
        N = par.size();
        depth.assign(N, -1);
        root.assign(N, -1);
        g.resize(N);
        for (int i = 0; i < N; ++i) {
            g[parent[i]].push_back(i);
        }
        detect_loop();
        build();
    }

    void detect_loop() {
        vector<int> visited(N, -1);
        for (int i = 0; i < N; ++i) {
            if (visited[i] != -1) continue;
            queue<int> que;
            int cur = i;
            while (visited[cur] == -1) {
                que.push(cur);
                visited[cur] = i;
                cur = parent[cur];
            }
            if (visited[cur] != i) continue;
            dump(cur, que);
            while (!que.empty() && que.front() != cur) {
                que.pop();
            }
            vector<int> loop;
            while (!que.empty()) {
                loop.push_back(que.front());
                depth[que.front()] = 0;
                root[que.front()] = loop.size() - 1;
                que.pop();
            }
            loops.push_back(loop);
        }
    }

    void build() {
        forest.resize(loops.size());
        auto dfs = [&](auto &&self, int cur, int d, int r) -> void {
            int id = 0;
            if (d != 0) {
                forest[r].push_back({cur, {}});
                id = forest[r].size() - 1;
            }
            depth[cur] = d;
            root[cur] = r;
            for (int nxt : g[cur]) {
                if (depth[nxt] != -1) continue;
                forest[r][id].children.push_back(forest[r].size());
                self(self, nxt, d + 1, r);
            }
        };
        for (int i = 0; i < (int)loops.size(); ++i) {
            forest[i].push_back({i, {}});
            for (int j = 0; j < (int)loops[i].size(); ++j) {
                dfs(dfs, loops[i][j], 0, i);
            }
        }
    }
};