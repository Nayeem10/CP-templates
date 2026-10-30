using PLL = pair <LL,LL>;
// EGCD
tuple <bool, LL, LL, LL> get_solution(LL a, LL b, LL c) {
	auto [x, y, g] = EGCD(abs(a), abs(b));
	x *= (a < 0) ? -c / g : c / g;
	y *= (b < 0) ? -c / g : c / g;
	return {c % g == 0, x, y, g} ; }
PLL shift_solution(LL a, LL b, LL x, LL y, LL shift) {
	return {x + shift * b, y - shift * a}; }