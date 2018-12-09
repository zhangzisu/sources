inline void solve(int len, int bg) {
	for (int i = 1; i < len - 1; i++) {
		printf("%d %d %d %d\n", 1, bg + i - 1, bg + i, bg + i + 1);
		fflush(stdout);
		scanf("%d", &a[i]);
	}
	printf("%d %d %d %d\n", 1, bg + len - 2, bg + len - 1, bg);
	fflush(stdout);
	scanf("%d", &a[len - 1]);
	printf("%d %d %d %d\n", 1, bg + len - 1, bg, bg + 1);
	fflush(stdout);
	scanf("%d", &a[len]);
	int sum = 0;
	for (int i = 1; i <= len; i++) sum ^= a[i];
	int tmp = 0;
	for (int i = 2; i <= len; i += 3) tmp ^= a[i];
	anss[++cntt] = tmp ^ sum;
	int a1 = tmp ^ sum;
	tmp = 0;
	for (int i = 3; i <= len; i += 3) tmp ^= a[i];
	int a2 = tmp ^ sum;
	anss[++cntt] = a2;
	fflush(stdout);
	for (int i = 1; i < len - 1; i++) {
		int tmpp = a[i] ^ a1 ^ a2;
		anss[++cntt] = tmpp;
		a1 = a2;
		a2 = tmpp;
	}
}
