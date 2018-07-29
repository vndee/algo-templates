// z[i] = độ dài xâu con dài nhất bắt đầu từ vị trí i mà trùng với đoạn đầu của v[]
vector<int> zfunc(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

// another version
void z_function() {
  z[0] = n;
  for (int i = 1, l = 0, r = 1; i < n; i++, r = i < r ? r : i)
    for (z[i] = min(r - i, z[i - l]); s[i + z[i]] == s[z[i]]; z[i]++, r = i + z[i], l = i);
}
