pair<lint, lint> gcd_extended(lint a, lint b)
{ // returns x, y such that a * x + b * y = gcd(a, b)
	if (b == 0)
		return { 1, 0 };
	lint x, y;
	tie(x, y) = gcd_extended(b, a % b);
	return { y, x - y * (a / b) };
}

lint sum_floor(lint a, lint b, lint n)
{ // sum(i * a / b for i in range(n + 1))
	if (a == 0 || b == 0)
		return 0;
	if (a >= b)
		return (a / b) * (n * (n + 1) / 2) + sum_floor(a % b, b, n);
	lint cur_number = a * n / b;
	lint cur_number_index = (cur_number * b + a - 1) / a;
	lint res = cur_number * (n - cur_number_index + 1);
	res += (b / a) * (cur_number * (cur_number - 1) / 2);
	res += sum_floor(a, b % a, (cur_number_index - 1) * (b % a) / b);
	return res;
}

lint remainder_theorem(lint a1, lint r1, lint a2, lint r2)
{ // returns x such that 0 <= x < a1 * a2, x % a1 = r1 and x % a2 = r2
  return r1 + mul(sub(r2, r1, a2), inv(a1, a2), a2) * a1;
}