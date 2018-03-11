#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 1010
char s1[MAXN], s2[MAXN], s3[MAXN];
bool e2 = 1, e3 = 1;
int main(){
	// freopen("ZGODAN.IN", "r", stdin);
	// freopen("ZGODAN.OUT", "w", stdout);

	scanf("%s", s1);
	memcpy(s2, s1, sizeof(s2));
	memcpy(s3, s1, sizeof(s3));
	for(int i = 1;s1[i];i++){
		if(e2 && e3){
			if((s2[i] & 1) == (s2[i - 1] & 1))s2[i]--;
			if((s3[i] & 1) == (s3[i - 1] & 1))s3[i]++;
			if(s2[i] < '0')e2 = 0;
			if(s3[i] > '9')e3 = 0;
			if(s1[i] - s2[i] < s3[i] - s1[i])e3 = 0;
			if(s1[i] - s2[i] > s3[i] - s1[i])e2 = 0;
		}else if(e2){
			if((s2[i] & 1) == (s2[i - 1] & 1)){
				s2[i] = s2[i - 1] & 1 ? '8' : '9';
			}
		}else if(e3){
			if((s3[i] & 1) == (s3[i - 1] & 1)){
				s3[i] = s3[i - 1] & 1 ? '0' : '1';
			}
		}
	}
	if(e2)printf("%s ", s2);
	if(e3)printf("%s ", s3);
	puts("");
}