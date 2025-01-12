// verfied by https://atcoder.jp/contests/abc385/submissions/60977784
#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> depth;
vector<int> subtree_size;
void subtr_dfs(const vector<vector<int>> &G, int v, int p, int d) {
    depth[v] = d;
    for (auto nv : G[v]) {
        if (nv == p) continue;  // nv が親 p だったらダメ
        subtr_dfs(G, nv, v, d + 1);
    }

    // 帰りがけ時に、部分木サイズを求める
    subtree_size[v] = 1;  // 自分自身
    for (auto c : G[v]) {
        if (c == p) continue;
        subtree_size[v] += subtree_size[c];  // 子のサイズを加える
    }
}

int subtr_size(int p, int v) {
    if (p == -1) {
        return subtree_size[v];
    }
    if (depth[p] > depth[v]) {
        return N - subtree_size[p];
    } else {
        return subtree_size[v];
    }
}