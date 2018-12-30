#ifndef PERILLA_HEADER
#define PERILLA_HEADER
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
#endif