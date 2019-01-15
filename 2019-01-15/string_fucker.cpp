#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
int table[100][100];
int main() {
	table[1][1] = 2;
	table[2][1] = 3;
	table[2][2] = 12;
	table[3][1] = 4;
	table[3][2] = 34;
	table[3][3] = 114;
	table[4][1] = 5;
	table[4][2] = 88;
	table[4][3] = 447;
	table[4][4] = 1400;
	table[5][1] = 6;
	table[5][2] = 220;
	table[5][3] = 1674;
	table[5][4] = 6984;
	table[5][5] = 21070;
	table[6][1] = 7;
	table[6][2] = 532;
	table[6][3] = 6063;
	table[6][4] = 33688;
	table[6][5] = 126895;
	table[6][6] = 374412;
	table[7][1] = 8;
	table[7][2] = 1258;
	table[7][3] = 21408;
	table[7][4] = 158348;
	table[7][5] = 745000;
	table[7][6] = 2635878;
	table[7][7] = 7665728;
	table[8][1] = 9;
	table[8][2] = 2912;
	table[8][3] = 74085;
	table[8][4] = 729384;
	table[8][5] = 4287065;
	table[8][6] = 18195384;
	table[8][7] = 61711797;
	table[8][8] = 177672560;
	table[9][1] = 10;
	table[9][2] = 6644;
	table[9][3] = 252378;
	table[9][4] = 3306160;
	table[9][5] = 24277010;
	table[9][6] = 123629220;
	table[9][7] = 489139714;
	table[9][8] = 609172281;
	table[9][9] = 598716382;
	table[10][1] = 11;
	table[10][2] = 14972;
	table[10][3] = 848793;
	table[10][4] = 14792504;
	table[10][5] = 135693575;
	table[10][6] = 829188996;
	table[10][7] = 827800256;
	table[10][8] = 392257870;
	table[10][9] = 269781697;
	table[10][10] = 482008183;

	int T, n, m;
	for (scanf("%d", &T); T; T--) {
		scanf("%d%d", &n, &m);
		printf("%d\n", table[n][m]);
	}
}