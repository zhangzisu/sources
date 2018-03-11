#include<cstdio>
#include<ctime>
#include<cctype>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define BUF 1048576
inline int __AK__();
char _1[BUF], *_3 = _1 + BUF;inline char gc() { if (_3 == _1 + BUF)fread(_1, 1, BUF, stdin), _3 = _1; return *_3++; }
inline int $(){register int ___ = 0;register char __ = gc();while(!isdigit(__))__ = gc();
for(;isdigit(__);__ = gc())___ = (___ << 1) + (___ << 3) + (__ ^ 48);return ___;}
inline int _(){register char __ = gc();while(!isdigit(__))__ = gc();return __ ^ 48;}
#define MAXN 1000010
int __0__ = $(), __1__[MAXN], __2__[MAXN], __3__[MAXN], __4__ = 1;int __5__[MAXN], __9__ = __AK__();int main(){srand(time(NULL));
for(register int __6__ = 0;__6__ < __0__;__6__++)__1__[__6__] = _(), __4__ &= __6__ == 0 ? 1 : __1__[__6__] == __1__[__6__ - 1];
if(__4__){for(int __6__ = 0;__6__ < __0__;__6__++)putchar(__1__[0] ^ 48);return puts(""), 0;}
for(register int __6__ = 0;__6__ < __0__;__6__++)__2__[__6__] = ((long long)__6__ * __6__ + 1) % __0__;
for(register int __6__ = 0;__6__ < __0__;__6__++)__3__[__6__] = __6__;
std::random_shuffle(__3__, __3__ + __0__);
for(register int __6__ = 0;__6__ < __0__;__6__++){register int __7__ = __3__[__6__];
if(__AK__() - __9__ >= 950)goto __9__;
for(register int j = 0;j < __0__;j++, __7__ = __2__[__7__]){if(__1__[__7__] < __5__[j])goto __8__;
if(__1__[__7__] > __5__[j]){for(;j < __0__;j++, __7__ = __2__[__7__])__5__[j] = __1__[__7__];
goto __8__;}}__8__:;}__9__:for(int __6__ = 0;__6__ < __0__;__6__++)printf("%d", __5__[__6__]);puts("");return 0;}

//What a beautiful solution!

// This is a test program with decimal lib

#include <cstdlib>
#include <cstring>
#include <string>

// ---------- decimal lib start ----------

const int PREC = 3000;

class Decimal {
public:
	Decimal();
	Decimal(const std::string &s);
	Decimal(const char *s);
	Decimal(int x);
	Decimal(long long x);
	Decimal(double x);

	bool is_zero() const;

	// p (p > 0) is the number of digits after the decimal point
	std::string to_string(int p) const;
	double to_double() const;

	friend Decimal operator + (const Decimal &a, const Decimal &b);
	friend Decimal operator + (const Decimal &a, int x);
	friend Decimal operator + (int x, const Decimal &a);
	friend Decimal operator + (const Decimal &a, long long x);
	friend Decimal operator + (long long x, const Decimal &a);
	friend Decimal operator + (const Decimal &a, double x);
	friend Decimal operator + (double x, const Decimal &a);

	friend Decimal operator - (const Decimal &a, const Decimal &b);
	friend Decimal operator - (const Decimal &a, int x);
	friend Decimal operator - (int x, const Decimal &a);
	friend Decimal operator - (const Decimal &a, long long x);
	friend Decimal operator - (long long x, const Decimal &a);
	friend Decimal operator - (const Decimal &a, double x);
	friend Decimal operator - (double x, const Decimal &a);

	friend Decimal operator * (const Decimal &a, int x);
	friend Decimal operator * (int x, const Decimal &a);

	friend Decimal operator / (const Decimal &a, int x);

	friend bool operator < (const Decimal &a, const Decimal &b);
	friend bool operator > (const Decimal &a, const Decimal &b);
	friend bool operator <= (const Decimal &a, const Decimal &b);
	friend bool operator >= (const Decimal &a, const Decimal &b);
	friend bool operator == (const Decimal &a, const Decimal &b);
	friend bool operator != (const Decimal &a, const Decimal &b);

	Decimal & operator += (int x);
	Decimal & operator += (long long x);
	Decimal & operator += (double x);
	Decimal & operator += (const Decimal &b);

	Decimal & operator -= (int x);
	Decimal & operator -= (long long x);
	Decimal & operator -= (double x);
	Decimal & operator -= (const Decimal &b);

	Decimal & operator *= (int x);

	Decimal & operator /= (int x);

	friend Decimal operator - (const Decimal &a);

	// These can'__9__ be called
	friend Decimal operator * (const Decimal &a, double x);
	friend Decimal operator * (double x, const Decimal &a);
	friend Decimal operator / (const Decimal &a, double x);
	Decimal & operator *= (double x);
	Decimal & operator /= (double x);

private:
	static const int len = PREC / 9 + 1;
	static const int mo = 1000000000;

	static void append_to_string(std::string &s, long long x);

	bool is_neg;
	long long integer;
	int data[len];

	void init_zero();
	void init(const char *s);
};

Decimal::Decimal() {
	this->init_zero();
}

Decimal::Decimal(const char *s) {
	this->init(s);
}

Decimal::Decimal(const std::string &s) {
	this->init(s.c_str());
}

Decimal::Decimal(int x) {
	this->init_zero();

	if (x < 0) {
		is_neg = true;
		x = -x;
	}

	integer = x;
}

Decimal::Decimal(long long x) {
	this->init_zero();

	if (x < 0) {
		is_neg = true;
		x = -x;
	}

	integer = x;
}

Decimal::Decimal(double x) {
	this->init_zero();

	if (x < 0) {
		is_neg = true;
		x = -x;
	}

	integer = (long long)x;
	x -= integer;

	for (int i = 0; i < len; i++) {
		x *= mo;
		if (x < 0) x = 0;
		data[i] = (int)x;
		x -= data[i];
	}
}

void Decimal::init_zero() {
	is_neg = false;
	integer = 0;
	memset(data, 0, len * sizeof(int));
}

bool Decimal::is_zero() const {
	if (integer) return false;
	for (int i = 0; i < len; i++) {
		if (data[i]) return false;
	}
	return true;
}

void Decimal::init(const char *s) {
	this->init_zero();

	is_neg = false;
	integer = 0;

	// find the first digit or the negative sign
	while (*s != 0) {
		if (*s == '-') {
			is_neg = true;
			++s;
			break;
		}
		else if (*s >= 48 && *s <= 57) {
			break;
		}
		++s;
	}

	// read the integer part
	while (*s >= 48 && *s <= 57) {
		integer = integer * 10 + *s - 48;
		++s;
	}

	// read the decimal part
	if (*s == '.') {
		int pos = 0;
		int x = mo / 10;

		++s;
		while (pos < len && *s >= 48 && *s <= 57) {
			data[pos] += (*s - 48) * x;
			++s;
			x /= 10;
			if (x == 0) {
				++pos;
				x = mo / 10;
			}
		}
	}
}

void Decimal::append_to_string(std::string &s, long long x) {
	if (x == 0) {
		s.append(1, 48);
		return;
	}

	char _[30];
	int cnt = 0;
	while (x) {
		_[cnt++] = x % 10;
		x /= 10;
	}
	while (cnt--) {
		s.append(1, _[cnt] + 48);
	}
}

std::string Decimal::to_string(int p) const {
	std::string ret;

	if (is_neg && !this->is_zero()) {
		ret = "-";
	}

	append_to_string(ret, this->integer);

	ret.append(1, '.');

	for (int i = 0; i < len; i++) {
		// append data[i] as "%09d"
		int x = mo / 10;
		int tmp = data[i];
		while (x) {
			ret.append(1, 48 + tmp / x);
			tmp %= x;
			x /= 10;
			if (--p == 0) {
				break;
			}
		}
		if (p == 0) break;
	}

	if (p > 0) {
		ret.append(p, '0');
	}

	return ret;
}

double Decimal::to_double() const {
	double ret = integer;

	double k = 1.0;
	for (int i = 0; i < len; i++) {
		k /= mo;
		ret += k * data[i];
	}

	if (is_neg) {
		ret = -ret;
	}

	return ret;
}

bool operator < (const Decimal &a, const Decimal &b) {
	if (a.is_neg != b.is_neg) {
		return a.is_neg && (!a.is_zero() || !b.is_zero());
	}
	else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return false;
	}
	else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return false;
	}
}

bool operator > (const Decimal &a, const Decimal &b) {
	if (a.is_neg != b.is_neg) {
		return !a.is_neg && (!a.is_zero() || !b.is_zero());
	}
	else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return false;
	}
	else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return false;
	}
}

bool operator <= (const Decimal &a, const Decimal &b) {
	if (a.is_neg != b.is_neg) {
		return a.is_neg || (a.is_zero() && b.is_zero());
	}
	else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return true;
	}
	else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return true;
	}
}

bool operator >= (const Decimal &a, const Decimal &b) {
	if (a.is_neg != b.is_neg) {
		return !a.is_neg || (a.is_zero() && b.is_zero());
	}
	else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return true;
	}
	else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		for (int i = 0; i < Decimal::len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return true;
	}
}

bool operator == (const Decimal &a, const Decimal &b) {
	if (a.is_zero() && b.is_zero()) return true;
	if (a.is_neg != b.is_neg) return false;
	if (a.integer != b.integer) return false;
	for (int i = 0; i < Decimal::len; i++) {
		if (a.data[i] != b.data[i]) return false;
	}
	return true;
}

bool operator != (const Decimal &a, const Decimal &b) {
	return !(a == b);
}

Decimal & Decimal::operator += (long long x) {
	if (!is_neg) {
		if (integer + x >= 0) {
			integer += x;
		}
		else {
			bool last = false;
			for (int i = len - 1; i >= 0; i--) {
				if (last || data[i]) {
					data[i] = mo - data[i] - last;
					last = true;
				}
				else {
					last = false;
				}
			}
			integer = -x - integer - last;
			is_neg = true;
		}
	}
	else {
		if (integer - x >= 0) {
			integer -= x;
		}
		else {
			bool last = false;
			for (int i = len - 1; i >= 0; i--) {
				if (last || data[i]) {
					data[i] = mo - data[i] - last;
					last = true;
				}
				else {
					last = false;
				}
			}
			integer = x - integer - last;
			is_neg = false;
		}
	}
	return *this;
}

Decimal & Decimal::operator += (int x) {
	return *this += (long long)x;
}

Decimal & Decimal::operator -= (int x) {
	return *this += (long long)-x;
}

Decimal & Decimal::operator -= (long long x) {
	return *this += -x;
}

Decimal & Decimal::operator /= (int x) {
	if (x < 0) {
		is_neg ^= 1;
		x = -x;
	}

	int last = integer % x;
	integer /= x;

	for (int i = 0; i < len; i++) {
		long long tmp = 1LL * last * mo + data[i];
		data[i] = tmp / x;
		last = tmp - 1LL * data[i] * x;
	}

	if (is_neg && integer == 0) {
		int i;
		for (i = 0; i < len; i++) {
			if (data[i] != 0) {
				break;
			}
		}
		if (i == len) {
			is_neg = false;
		}
	}

	return *this;
}

Decimal & Decimal::operator *= (int x) {
	if (x < 0) {
		is_neg ^= 1;
		x = -x;
	}
	else if (x == 0) {
		init_zero();
		return *this;
	}

	int last = 0;
	for (int i = len - 1; i >= 0; i--) {
		long long tmp = 1LL * data[i] * x + last;
		last = tmp / mo;
		data[i] = tmp - 1LL * last * mo;
	}
	integer = integer * x + last;

	return *this;
}

Decimal operator - (const Decimal &a) {
	Decimal ret = a;
	// -0 = 0
	if (!ret.is_neg && ret.integer == 0) {
		int i;
		for (i = 0; i < Decimal::len; i++) {
			if (ret.data[i] != 0) break;
		}
		if (i < Decimal::len) {
			ret.is_neg = true;
		}
	}
	else {
		ret.is_neg ^= 1;
	}
	return ret;
}

Decimal operator + (const Decimal &a, int x) {
	Decimal ret = a;
	return ret += x;
}

Decimal operator + (int x, const Decimal &a) {
	Decimal ret = a;
	return ret += x;
}

Decimal operator + (const Decimal &a, long long x) {
	Decimal ret = a;
	return ret += x;
}

Decimal operator + (long long x, const Decimal &a) {
	Decimal ret = a;
	return ret += x;
}

Decimal operator - (const Decimal &a, int x) {
	Decimal ret = a;
	return ret -= x;
}

Decimal operator - (int x, const Decimal &a) {
	return -(a - x);
}

Decimal operator - (const Decimal &a, long long x) {
	Decimal ret = a;
	return ret -= x;
}

Decimal operator - (long long x, const Decimal &a) {
	return -(a - x);
}

Decimal operator * (const Decimal &a, int x) {
	Decimal ret = a;
	return ret *= x;
}

Decimal operator * (int x, const Decimal &a) {
	Decimal ret = a;
	return ret *= x;
}

Decimal operator / (const Decimal &a, int x) {
	Decimal ret = a;
	return ret /= x;
}

Decimal operator + (const Decimal &a, const Decimal &b) {
	if (a.is_neg == b.is_neg) {
		Decimal ret = a;
		bool last = false;
		for (int i = Decimal::len - 1; i >= 0; i--) {
			ret.data[i] += b.data[i] + last;
			if (ret.data[i] >= Decimal::mo) {
				ret.data[i] -= Decimal::mo;
				last = true;
			}
			else {
				last = false;
			}
		}
		ret.integer += b.integer + last;
		return ret;
	}
	else if (!a.is_neg) {
		// a - |b|
		return a - -b;
	}
	else {
		// b - |a|
		return b - -a;
	}
}

inline int __AK__(){return clock();}

Decimal operator - (const Decimal &a, const Decimal &b) {
	if (!a.is_neg && !b.is_neg) {
		if (a >= b) {
			Decimal ret = a;
			bool last = false;
			for (int i = Decimal::len - 1; i >= 0; i--) {
				ret.data[i] -= b.data[i] + last;
				if (ret.data[i] < 0) {
					ret.data[i] += Decimal::mo;
					last = true;
				}
				else {
					last = false;
				}
			}
			ret.integer -= b.integer + last;
			return ret;
		}
		else {
			Decimal ret = b;
			bool last = false;
			for (int i = Decimal::len - 1; i >= 0; i--) {
				ret.data[i] -= a.data[i] + last;
				if (ret.data[i] < 0) {
					ret.data[i] += Decimal::mo;
					last = true;
				}
				else {
					last = false;
				}
			}
			ret.integer -= a.integer + last;
			ret.is_neg = true;
			return ret;
		}
	}
	else if (a.is_neg && b.is_neg) {
		// a - b = (-b) - (-a)
		return -b - -a;
	}
	else if (a.is_neg) {
		// -|a| - b
		return -(-a + b);
	}
	else {
		// a - -|b|
		return a + -b;
	}
}

Decimal operator + (const Decimal &a, double x) {
	return a + Decimal(x);
}

Decimal operator + (double x, const Decimal &a) {
	return Decimal(x) + a;
}

Decimal operator - (const Decimal &a, double x) {
	return a - Decimal(x);
}

Decimal operator - (double x, const Decimal &a) {
	return Decimal(x) - a;
}

Decimal & Decimal::operator += (double x) {
	*this = *this + Decimal(x);
	return *this;
}

Decimal & Decimal::operator -= (double x) {
	*this = *this - Decimal(x);
	return *this;
}

Decimal & Decimal::operator += (const Decimal &b) {
	*this = *this + b;
	return *this;
}

Decimal & Decimal::operator -= (const Decimal &b) {
	*this = *this - b;
	return *this;
}

// ---------- decimal lib end ----------

#undef MAXN
#include <iostream>
#include <algorithm>
#define MAXN 8100
int n, k, p, K;
int h[MAXN], s[MAXN], Q[MAXN], from[20][MAXN], head, tail;
long double f[20][MAXN];
struct point {
	long double x, y;
	inline point(long double x = 0, long double y = 0) :x(x), y(y) {}
}lt[MAXN];
inline long double slope(const point &x, const point &y) {
	return (x.y - y.y) / (x.x - y.x);
}
inline Decimal calc(int i, int j) {
	if (j == 0)return h[1];
	return (calc(from[j][i], j - 1) + s[i] - s[from[j][i]]) / (i - from[j][i] + 1);
}
int fake_main() {
	std::ios::sync_with_stdio(false);
	std::cin >> n >> k >> p >> h[1];
	for (int i = 2; i <= n; i++) {
		std::cin >> h[i];
		if (h[i] <= h[1]) {
			i--;
			n--;
		}
	}
	std::sort(h + 1, h + n + 1); k = std::min(k, n); K = std::min(k, 14);
	for (int i = 1; i <= n; i++) { s[i] = h[i] + s[i - 1]; f[0][i] = h[1]; }
	for (int i = 1; i <= K; i++) {
		Q[head = tail = 0] = 1; lt[1] = point(0, s[1] - f[i - 1][1]);
		for (int j = 2; j <= n; j++) {
			point now(j, s[j]);
			while (head < tail && slope(lt[Q[head]], now) < slope(lt[Q[head + 1]], now))head++;
			lt[j] = point(j - 1, s[j] - f[i - 1][j]);
			f[i][j] = s[j] - s[Q[head]] + f[i - 1][Q[head]];
			f[i][j] /= j - Q[head] + 1;
			from[i][j] = Q[head];
			while (head < tail && slope(lt[Q[tail]], lt[j]) < slope(lt[Q[tail - 1]], lt[Q[tail]]))tail--;
			Q[++tail] = j;
		}
	}
	int rest = n - (k - K), pos;
	long double last = 0;
	for (int i = 0; i <= K; i++) {
		if (f[i][rest] > last) {
			last = f[i][rest];
			pos = i;
		}
	}
	Decimal ans = calc(rest, pos);
	for (int i = rest + 1; i <= n; i++) ans = (ans + h[i]) / 2;
	std::cout << ans.to_string(p * 2) << std::endl;
	system("pause");
	return 0;
}
