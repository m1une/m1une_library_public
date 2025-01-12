vector<pair<char, int>> rle(string s) {
    vector<pair<char, int>> vec;
    int cnt = 1;
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] != s[i - 1]) {
            vec.push_back({s[i - 1], cnt});
            cnt = 0;
        }
        ++cnt;
    }
    vec.push_back({s.back(), cnt});
    return vec;
}