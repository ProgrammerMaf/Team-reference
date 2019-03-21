typedef complex<double> base;

const int P = 21;
const int T = 1 << P;

void fft(base * a, bool inv) {
	for (int i = 0; i < T; ++i) {
		int t = 0;
		for (int j = 0; j < P; ++j) {
			t = (t << 1) | ((i >> j) & 1);
		}
		if (i < t)
			swap(a[i], a[t]);
	}
	for (int l = 2; l <= T; l *= 2) {
		double alpha = 2 * PI / l;
		if (inv) {
			alpha *= -1;
		}                                
		base wrot(cos(alpha), sin(alpha));
		for (int i = 0; i < T; i += l) {
			base w(1, 0);
			for (int j = 0; j < l / 2; ++j) {
				base u = a[i + j];
				base v = w * a[i + l / 2 + j];
				a[i + j] = u + v;
				a[i + l / 2 + j] = u - v;
				w *= wrot;
			}
		}
	}
	if (inv) {
		for (int i = 0; i < T; ++i) {
			a[i] /= T * 1.;
		}
	}
}