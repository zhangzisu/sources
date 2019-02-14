#include <cstdio>
const int W = 1000, H = 1000;
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
bool vis[W][H];
int main() {
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			vis[i][j] = gcd(i, j) != 1;
		}
	}
	// for (int i = 0; i < W; i++) {
	// 	for (int j = 0; j < H; j++) {
	// 		if(vis[i][j]&&vis[i+1][j]&&vis[i][j+1]&&vis[i][j])
	// 	}
	// }
}