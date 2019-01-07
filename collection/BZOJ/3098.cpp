#include<cstdio>
#include<cstdlib>
#define BUF 65536
char _2[BUF], *_4 = _2;
inline void $(char c) { if (_4 == _2 + BUF)fwrite(_2, 1, BUF, stdout), _4 = _2; *_4++ = c; }
inline int _() { fwrite(_2, 1, _4 - _2, stdout); return 0; }
int main(){
	freopen("sb.cpp", "w", stdout);
	$('1');$('0');$('0');$('0');$('0');$('0');$(' ');$('2');$('0');$(10);
	for(register int i = 100000;i;i--)$(rand()%26+97);
	return _();
}
