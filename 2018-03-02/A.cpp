#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

int main(){
    for(int i = 1;i <= 1000;i++){
        for(int j = 1;j <= 1000;j++){
            if(fabs((1. * i / j) - 0.56169) < 1e-5)printf("%5d %5d %f\n", i, j, 1. * i / j);
        }
    }
}