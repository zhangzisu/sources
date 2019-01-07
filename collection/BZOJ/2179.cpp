#include<cstdio>
#include<cstdlib>
#include<complex>
#include<vector>
#include<algorithm>
typedef std::complex<double> number;
int n, m;
std::vector<number> a, b;
std::vector<int> ans;
const double PI = acos(-1.);

void FFT(std::vector<number> &v, int e){
    const int n = v.size();
    if(n <= 1)return;
    std::vector<number> v0, v1;
    for(int i = 0;i < n;i += 2)v0.push_back(v[i]), v1.push_back(v[i + 1]);
    FFT(v0, e); FFT(v1, e);
    number w(cos(2 * PI / n), sin(e * 2 * PI / n)), t(1, 0);
    for(int i = 0;(i << 1) < n;i++, t *= w)v[i] = v0[i] + t * v1[i], v[i + (n >> 1)] = v0[i] - t * v1[i];
}

int main(){
    scanf("%d", &m); n = m; m <<= 1;
    
    for(int i = 0, x;i < n;i++){ scanf("%1d", &x); a.push_back(number(x)); }
    for(int i = 0, x;i < n;i++){ scanf("%1d", &x); b.push_back(number(x)); }
    std::reverse(a.begin(), a.end()); std::reverse(b.begin(), b.end());
    n = 1 << (int)ceil(log(2. * n) / log(2.));
    while((int)a.size() < n)a.push_back(number());
    while((int)b.size() < n)b.push_back(number());
    
    FFT(a, 1); FFT(b, 1);
    for(int i = 0;i < n;i++)a[i] *= b[i];
    FFT(a, -1);

    int last = 0;
    for(int i = 0;i < n;i++){
        last = int(a[i].real() / n + 0.5) + last;
        ans.push_back(last % 10);
        last /= 10;
    }
    while(last)ans.push_back(last % 10), last /= 10;
    
    int i = ans.size() - 1;
    while(~i && !ans[i])i--;
    while(~i)printf("%d", ans[i--]);
    puts("");
    
    return 0;
}