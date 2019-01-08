#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
class Reader {
       protected:
	static const int BSIZE = 65536;
	int is;
	char ib[BSIZE], *ip;
	FILE *in;

       public:
	inline Reader(FILE *in = stdin) {
		ip = ib + BSIZE, is = 0;
		this->in = in;
	}
	inline Reader(const char *filename) {
        ip = ib + BSIZE, is = 0;
        this->in = fopen(filename, "r");
	}
	inline char getchar() {
		if (ip == ib + BSIZE) is = fread(ib, 1, BSIZE, in), ip = ib;
		return ip == ib + is ? 0 : *ip++;
	}
	inline int getdigit() {
		register char ch = getchar();
		while (!isdigit(ch)) ch = getchar();
		return ch ^ 48;
	}
	inline char getalpha() {
		register char ch = getchar();
		while (!isalpha(ch)) ch = getchar();
		return ch;
	}
	inline int getint() {
		register int x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned getuint() {
		register unsigned x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
	inline long long getint64() {
		register long long x = 0, f = 0;
		register char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) f ^= ch == 45;
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return f ? -x : x;
	}
	inline unsigned long long getuint64() {
		register unsigned long long x = 0;
		register char ch = getchar();
		for (; isdigit(ch); ch = getchar()) x = (((x << 2) + x) << 1) + (ch ^ 48);
		return x;
	}
} userout, input("input"), output("output"), usercode("usercode");
enum SolutionResult {
	WaitingJudge,
	Judging,
	Skipped,
	Accepted,
	WrongAnswer,
	TimeLimitExceeded,
	MemoryLimitExceeded,
	RuntimeError,
	CompileError,
	PresentationError,
	JudgementFailed,
	SystemError,
	OtherError,
};
inline void callback(SolutionResult status, double score, const char *message) {
	assert(score >= 0 && score <= 100);
	printf("%d\n%f\n", status, score);
	if (message)
		printf("%s\n", message);
	exit(0);
}
#define MAXN 3005
#define MOD 59393
using namespace std;
int n, k, a[15];
int std_n, std_val;
int ans_n, ans_val;
int u, v, fa[MAXN], indgr[MAXN];
int sum;
double S;
int find(int u) {
	if (fa[u] != u) fa[u] = find(fa[u]);
	return fa[u];
}
int calc(int d) {
	int ans = 0, x = 1;
	for (int i = 0; i <= k; i++, x *= d, x %= MOD)
		ans += a[i] * x, ans %= MOD;
	return ans % MOD;
}
int main(int argc, char *argv[]) {
	n = input.getint();
	k = input.getint();
	for (int i = 0; i <= k; i++)
		a[i] = input.getint();
	std_n = output.getint();
	std_val = output.getint();
	for (int i = 1; i <= std_n; i++) {
		u = output.getint();
		v = output.getint();
	}
	ans_n = userout.getint();
	ans_val = userout.getint();
	if ((std_n != ans_n) || (std_val != ans_val)) {
		callback(SolutionResult::WrongAnswer, 0, "Wrong answer.");
	}
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	for (int i = 1; i <= ans_n; i++) {
		u = userout.getint();
		v = userout.getint();
		if ((u == v) || (u > n) || (v > n) || (u < 1) || (v < 1)) {
			callback(SolutionResult::WrongAnswer, 0, "Wrong answer.");
		}
		indgr[u]++;
		indgr[v]++;
		if (find(u) == find(v)) {
			callback(SolutionResult::WrongAnswer, 0, "Wrong answer.");
		}
		fa[find(u)] = find(v);
	}
	for (int i = 1; i <= n; i++)
		sum += calc(indgr[i]);
	if (sum != std_val) {
		callback(SolutionResult::WrongAnswer, 0, "Wrong answer.");
	} else {
		callback(SolutionResult::Accepted, 100, "OK.");
	}
	return 0;
}