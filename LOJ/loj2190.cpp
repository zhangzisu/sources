#include<cstdio>
#include<cmath>
#include<algorithm>
const double PI = 3.14159265358979323846, EPS = 1e-4;
struct point{
	double x, y;
	inline point(double x = 0, double y = 0):x(x), y(y){}
}p[50010];
inline point RectToPola(point rect){return point(sqrt(rect.x * rect.x + rect.y * rect.y), atan2(rect.y, rect.x));}
inline point PolaToRect(point pola){return point(pola.x * cos(pola.y), pola.x * sin(pola.y));}
inline point CircumCenter(point a, point b, point c){
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2;
	double d = a1 * b2 - a2 * b1;
	return point(a.x + (c1 * b2 - c2 * b1) / d, a.y + (a1 * c2 - a2 * c1) / d);
}
inline point MidPoint(point a, point b){return point((a.x + b.x) / 2, (a.y + b.y) / 2);}
inline double dist(point x, point y){
	return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
}
inline double ATG(double a){return a / 180 * PI;}
int n, a, g;
int main(){
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)scanf("%lf%lf", &p[i].x, &p[i].y);
	scanf("%d%d", &a, &g);
	for(int i = 1;i <= n;i++){
		p[i] = RectToPola(p[i]);
		p[i].y -= ATG(a);
		p[i] = PolaToRect(p[i]);
		p[i].x /= g;
	}
	//for(int i = 1;i <= n;i++)printf("POINT:%.3f %.3f\n", p[i].x, p[i].y);
	std::random_shuffle(p + 1, p + n + 1);
	point c = p[1];
	double r = 0;
	for(int i = 2;i <= n;i++){
		if(dist(p[i], c) > r + EPS){
			c = p[i], r = 0;
			for(int j = 1;j < i;j++){
				if(dist(p[j], c) > r + EPS){
					c = MidPoint(p[i], p[j]);r = dist(p[j], c);
					for(int k = 1;k < j;k++){
						if(dist(p[k], c) > r + EPS){
							c = CircumCenter(p[i], p[j], p[k]);
							r = dist(p[k], c);
						}
					}
				}
			}
		}
	}
	printf("%.3f\n", r);
	return 0;
}
