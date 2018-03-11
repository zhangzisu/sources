#include <bits/stdc++.h>
#define gc getchar()
#define ll long long
#define mod 1000000007
#define N 59
#define M 10
#define pii pair<int,int>
#define x first
#define y second
#define add(x,y) (x=(x+y>=mod?x+y-mod:x+y))
using namespace std;
int n,m,k,pd[N][M],Ans=0,dp[2][5][300009],bit[10];
int read()
{
	int x=1;
	char ch;
	while (ch=gc,ch<'0'||ch>'9') if (ch=='-') x=-1;
	int s=ch-'0';
	while (ch=gc,ch>='0'&&ch<='9') s=s*10+ch-'0';
	return s*x;
}
int main()
{
//	freopen("tetris.in","r",stdin);
	//freopen("tetris.out","w",stdout);
	n=read(),m=read(),k=read();
	bit[0]=1;
	for (int i=1;i<10;i++) bit[i]=bit[i-1]*6;
	for (int i=1;i<=k;i++)
	{
		int X=read()+1,Y=read()+1;
		pd[X][Y]=1;
	}
	int ttt=clock();
	int (*now)[300009]=dp[1],(*last)[300009]=dp[0];
	now[0][0]=1;
	int t=0;
	for (int i=1;i<=n;++i)
	{
		swap(now,last);
		memset(now,0,sizeof(dp[1]));
		for (int k=0;k<bit[m];++k)
			add(now[0][k],last[0][k]);
		for (int j=1;j<=m;++j)
		{
			swap(now,last);
			memset(now,0,sizeof(dp[1]));
			for (int k=0;k<bit[m];++k)
				for (int l=0;l<5;++l)
					if (last[l][k])
						if (pd[i][j])
						{
							if (l) continue;
							if (k%bit[j]/bit[j-1]) continue;
							add(now[l][k],last[l][k]);
						}
						else
						{
							register int Last=last[l][k];
							register int pos=k%bit[j]/bit[j-1];
							register int K=k-pos*bit[j-1];
							if (!pos&&!l)
							{
								add(now[3][K],Last);
								add(now[0][K+bit[j-1]*3],Last);
								add(now[1][K+bit[j-1]*5],Last);
								add(now[2][K+bit[j-1]*1],Last);
							}
							else if (pos==1&&!l)
								add(now[0][K],Last);
							else if ((pos==2||pos==4)&&!l)
							{
								add(now[0][K+bit[j-1]],Last);
								add(now[1][K],Last);
							}
							else if (pos==3&&!l)
							{
								add(now[0][K+2*bit[j-1]],Last);
								add(now[4][K],Last);
								add(now[1][K+bit[j-1]],Last);
							}
							else if (pos==5&&!l)
								add(now[0][K+bit[j-1]],Last);
							else if (!pos&&l==1)
								add(now[0][K],Last);
							else if (!pos&&l==2)
							{
								add(now[0][K+bit[j-1]],Last);
								add(now[1][K],Last);
							}
							else if (pos==3&&l==2)
								add(now[0][K],Last);
							else if (!pos&&l==3)
							{
								add(now[0][K+4*bit[j-1]],Last);
								add(now[2][K],Last);
								add(now[1][K+bit[j-1]],Last);
							}
							else if (pos==2&&l==3)
								add(now[0][K],Last);
							else if (pos==3&&l==3)
							{
								add(now[0][K+bit[j-1]],Last);
								add(now[1][K],Last);
							}
							else if (pos==5&&l==3)
								add(now[0][K],Last);
							else if (!pos&&l==4)
							{
								add(now[0][K+bit[j-1]],Last);
								add(now[1][K],Last);
							}
						}
		}
	}
	Ans=now[0][0];
	printf("%d\n",Ans);
	return 0;
}
