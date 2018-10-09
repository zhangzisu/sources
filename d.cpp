#include <iostream>
using namespace std;

int main(void) {
	int a, t, d, s, p;
	cin >> a;

	do {
		t = a;
		a = t / 10;
		d = t - a * 1;
		s = s + d;
		p = p + 1;
	} while (a != 0);

	cout << s << " " << p;
	return 0;
}