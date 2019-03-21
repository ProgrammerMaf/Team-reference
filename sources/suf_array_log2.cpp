const int max_lvl = 21;
vector<int> cls[max_lvl];
vector<int> suff_arr(const string& s) {
	int n = s.length();
	For (lvl, max_lvl) {
		cls[lvl].resize(n);
		vector<pair<pair<int, int>, int>> order;
		For (i, n) {
			if (lvl == 0)
				order.emplace_back({s[i], -1}, i);
			else
				order.emplace_back({cls[lvl - 1][i], cls[lvl - 1][(i + (1 << (lvl - 1))) % n]}, i);
		}
		stable_sort(all(order));
		auto prev = order[0].first;
		int q = 0;
		For (i, n)
		{
			q += order[i].first != prev;
			cls[lvl][order[i].second] = q;
			prev = order[i].first;
		}
	}
	vector<int> result(n);
	For (i, n)
		result[cls[max_lvl - 1][i]] = i;
	return result;
}