// modulo operations required
vector<lint> bm(const vector<lint> & values) {
    int k = -1;
    For(i, sz(values))
        if (values[i] != 0) {
            k = i;
            break;
        }
    if (k == -1)
        return{ 0 };
    vector<lint> prev(k + 1, 0);
    prev[0] = 1;
    int worked_to = k;
    lint prev_err = values[k];
    int second_pos = -1;
    for (int i = k + 1; i < sz(values); i++) {
        if (values[i] != 0) {
            second_pos = i;
            break;
        }
    }
    if (second_pos == -1)
        return{ 1 , sub(0, 1) };
    vector<lint> cur(second_pos + 1, 0);
    cur[0] = 1;
    for (int it = second_pos; it < sz(values); it++) {
        lint generated = 0;
        For(i, sz(cur))
            generated = add(generated, mul(cur[i], values[it - i]));

        if (generated == 0)
            continue;
        lint err = generated;
        lint coeff = mul(err, inv(prev_err));
        int new_size = max(sz(cur), sz(prev) + it - worked_to);
        vector<lint> nxt(new_size, 0);
        For(i, sz(prev))
            nxt[i + it - worked_to] = sub(0, mul(prev[i], coeff));
        For(i, sz(cur))
            nxt[i] = add(cur[i], nxt[i]);
        if (new_size > sz(cur)) {
            prev = cur;
            worked_to = it;
            prev_err = err;
        }
        cur = nxt;
    }
    return cur;
}

lint apply(const vector<lint> & poly, lint x) {
    lint ans = 0;
    lint p = 1;
    for (auto a : poly) {
        ans = add(ans, mul(a, p));
        p = mul(p, x);
    }
    return ans;
}

vector<lint> derivative(vector<lint> poly) {
    if (poly.size() == 0)
        return{ 0 };
    for (int i = 1; i < sz(poly); i++)
        poly[i - 1] = mul(poly[i], i);
    poly.pop_back();
    return poly;
}

void solve() { // calc expected value
    // of first pizda step
    vector<lint> prob = { distr[n - 1] }; 
    auto rec = bm(prob);
    // using generative function
    int k = sz(rec);
    vector<lint> numerator(k - 1, 0);
    vector<lint> denominator = rec;
    For(i, k) {
        lint multiplier = rec[i];
        for (int j = i; j < k - 1; j++) {
            numerator[j] = add(numerator[j], mul(multiplier, prob[j - i]));
        }
    }

    lint fst = mul(
        apply(derivative(numerator), 1),
        apply(denominator, 1)
    );

    lint snd = mul(
        apply(derivative(denominator), 1),
        apply(numerator, 1)
    );
    lint x = apply(derivative(denominator), 1);
    lint y = apply(numerator, 1);

    lint num = sub(fst, snd);
    lint den = apply(denominator, 1);
    lint den2 = mul(den, den);
    lint ans = mul(num, inv(den2));
    printf("%lld", ans);
}