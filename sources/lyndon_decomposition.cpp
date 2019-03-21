vector<string> factorize(const string& s) {
    vector<string> result;
    for (int i = 0; i < sz(s); ) {
        int j = i;
        int k = i + 1;
        while (k < sz(s) && s[j] <= s[k]) {
            if (s[j] < s[k])
                j = i;
            else
                j++;
            k++;
        }
        while (i <= j) {
            result.push_back(s.substr(i, k - j));
            i += k - j;
        }
    }
    return result;
}
